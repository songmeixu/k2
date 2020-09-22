# Require python3, and find program poetry.
# If found, use `poetry install` to setup a py virtualenvs
# Otherwise, use python that detected by cmake.

find_program(POETRY poetry)
if(NOT POETRY)
  message(STATUS "Cannot find `poetry` in PATH, cannot use virtual py env,
    use python detected by cmake")
else()
  message(STATUS "Found poetry, use it to creat a py virtualenvs: .venv")
  add_custom_command(
    OUTPUT .venv/stamp  # As a dep of later target to aware cmake update or not.
    DEPENDS .venv pyproject.toml
    COMMAND poetry config --local virtualenvs.in-project true
    COMMAND POETRY install
    COMMAND POETRY shell
  )
  set(Python3_ROOT_DIR ${CMAKE_SOURCE_DIR}/.venv)
  set(Python3_FIND_VIRTUALENV ONLY)
  find_package(Python3 COMPONENTS Interpreter Development)
  if (NOT Python3_FOUND)
    message(FATAL_ERROR "Error happend for poetry venv setup, please check it.")
  endif()
  # please check doc to get result variables of find_python3
  # https://cmake.org/cmake/help/latest/module/FindPython3
  # .html?highlight=findpython#module:FindPython3
  set(PYTHON_EXECUTABLE Python3_EXECUTABLE)
#  set(PYBIND11_PYTHON_VERSION 3.8.5)
endif()
