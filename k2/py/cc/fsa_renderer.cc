// k2/py/cc/fsa_renderer.cc

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)

// See ../../../LICENSE for clarification regarding multiple authors

#include "k2/py/cc/fsa_renderer.h"

#include "k2/cc/fsa_renderer.h"

void PybindFsaRenderer(py::module &m) {
  using kk::Fsa;
  using kk::FsaRenderer;

  py::class_<FsaRenderer>(m, "FsaRenderer")
      .def(py::init<const Fsa &>(), py::arg("fsa"))
      .def("render", &FsaRenderer::Render);
}
