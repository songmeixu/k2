#!/usr/bin/env bash


# @brief
# This is the main script to make a cross-platform build of k2, 
# with the help of `poetry` and `conan`:
#  - poetry: maintain python dependencies
#  - conan: maintain c++ dependencies
# 
# @copyright
# Copyright (c)  2020  Xiaomi Corporation (authors: Meixu Song)
# 
# @copyright
# See LICENSE for clarification


stage=1
build_type=Debug  # build type of cmake [Debug|Release]
libcxx=libstdc++  # c++ abi versions [libstdc++|libstdc++11], macOS may only
                  # work with `libstdc++11`

. ./scripts/parse_options.sh

set -e

# Install deps.
if [ $stage -le 1 ]; then
  # pyenv is good at effective python version control.
  {
    if ! [ -x "$(command -v pyenv)" ]; then
      echo 'Warn [pyenv]: pyenv is not installed. Installing it ...' >&2
      
      curl https://pyenv.run | bash
      exec $SHELL
    if

    echo 'Info [pyenv]: Try to install py-3.8 by pyenv ...'
    pyenv update
    pyenv install 3.8.6

    echo 'Info [pyenv]: Set py-3.8 as the default python for this project'
    pyenv local 3.8.6
  }

  # poetry is good at maintain python dependencies.
  {
    if ! [ -x "$(command -v poetry)" ]; then
      echo 'Warn [poetry]: poetry is not installed. Installing it ...' >&2
      curl -sSL "https://raw.githubusercontent.com/python-poetry/poetry/master \
          get-poetry.py" | python
    fi

    echo 'Info [poetry]: Installing python pkgs into a local virtual env \
        created by poetry ...'
    poetry config --local virtualenvs.in-project true
    poetry install --no-root
  }

  # conan is good at maintain c++ deps
  {
    if ! [ -x "$(command -v conan)" ]; then
      echo 'Error [poetry]: Conan is not installed by poetry as expected' >&2
      exit 1;
    fi

    echo 'Info [conan]: add remotes to conan ...'
    conan config install cfg/remotes.txt
  }
fi

  
fi

# c++ build
if [ $stage -le 2 ]; then
  if [ -d "build" ]; then rm -rf build; fi
  mkdir build && cd build

  # conan install pkgs in ~/.conan, thus below command only generates
  # cmake modules after the first call.
  echo 'Info [conan]: conan install c++ deps, refer to conanfile.py'
  conan install -s build_type=${build_type} -s compiler.libcxx=${libcxx} ..
  
  # call build by conan
  {
    conan build
  }

  # or by cmake:
  {
    # cmake -DCMAKE_BUILD_TYPE=${build_type} ..
    # make -j 4
  }

  cd ..
fi

# python pkg build
if [ $stage -le 3 ]; then
  poetry build
  exit 0;
fi

# Publish k2 python pkg to pypi.org, requires k2-fsa/k2 admin passwd
# Before this, the version ID string within `pyproject.toml` requires update.
if [ $stage -le 4 ]; then
  poetry publish --build
fi

exit 0;
