import glob
import os
import sys

from distutils.util import get_platform
from setuptools_cpp import CMakeExtension, ExtensionBuilder, Pybind11Extension
from typing import Any, Dict

pybind11_csrc = glob.glob("k2/python/csrc/*.cc")
postfix = f"{get_platform()}-{sys.version_info.major}.{sys.version_info.minor}"
lib_dir = os.path.join("build", f"lib.{postfix}", "k2")

ext_modules = [
    # CMake build libraries (as libfsa.so)
    CMakeExtension("k2.fsa", sourcedir="."),
    # call c++ with pybind11 headers and libs
    # to build a python pybind11 library (pybind11_extension)
    Pybind11Extension(
        "k2._k2",
        sources=pybind11_csrc,
        include_dirs=["csrc"],
        library_dirs=[lib_dir],
        libraries=["fsa"],
        runtime_library_dirs=["$ORIGIN", "."],
    ),
]


def build(setup_kwargs: Dict[str, Any]) -> None:
    setup_kwargs.update(
        {
            "ext_modules": ext_modules,
            "cmdclass": dict(build_ext=ExtensionBuilder),
            "zip_safe": False,
        }
    )
