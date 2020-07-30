// dlpack/fsa.h

// Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)
//                      Meixu Song (Xiaomi Corporation)

// See ../../../LICENSE for clarification regarding multiple authors

#ifndef K2_CC_DLPACK_FSA_H_
#define K2_CC_DLPACK_FSA_H_

#include <memory>

#include "fsa/fsa.h"
#include "dlpack/tensor.h"

namespace kk {

// it uses external memory passed from DLPack (e.g., by PyTorch)
// to construct an Fsa.
class DLPackFsa : public Fsa {
 public:
  DLPackFsa(py::capsule cap_indexes, py::capsule cap_data)
      : indexes_tensor_(new Tensor(cap_indexes)),
        data_tensor_(new Tensor(cap_data)) {
    CHECK_EQ(indexes_tensor_->dtype(), kInt32Type);
    CHECK_EQ(indexes_tensor_->NumDim(), 1);
    CHECK_GE(indexes_tensor_->Shape(0), 1);
    CHECK_EQ(indexes_tensor_->Stride(0), 1);

    CHECK_EQ(data_tensor_->dtype(), kInt32Type);
    CHECK_EQ(data_tensor_->NumDim(), 2);
    CHECK_GE(data_tensor_->Shape(0), 0);  // num-elements
    CHECK_EQ(data_tensor_->Shape(1) * data_tensor_->BytesPerElement(),
             sizeof(Arc));
    CHECK_EQ(data_tensor_->Stride(0) * data_tensor_->BytesPerElement(),
             sizeof(Arc));
    CHECK_EQ(data_tensor_->Stride(1), 1);

    int32_t size1 = indexes_tensor_->Shape(0) - 1;
    int32_t size2 = data_tensor_->Shape(0);
    this->Init(size1, size2, indexes_tensor_->Data<int32_t>(),
               data_tensor_->Data<Arc>());
  }

 private:
  std::unique_ptr<Tensor> indexes_tensor_;
  std::unique_ptr<Tensor> data_tensor_;
};

}  // namespace kk

#endif  // K2_CC_DLPACK_FSA_H_
