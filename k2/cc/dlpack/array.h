// dlpack/array.h

// Copyright (c)  2020  Xiaomi Corporation (author: Haowen Qiu
//                                                  Meixu Song)
//

// See ../../../LICENSE for clarification regarding multiple authors

#ifndef K2_CC_DLPACK_ARRAY_H_
#define K2_CC_DLPACK_ARRAY_H_

#include <memory>
#include <utility>

#include "fsa/fsa.h"
#include "dlpack/array.h"
#include "dlpack/tensor.h"

namespace kk {
/*
   DLPackArray2 initializes Array2 with `cap_indexes` and `cap_data` which are
   DLManagedTensors.

   `cap_indexes` is usually a one dimensional contiguous array, i.e.,
   `cap_indexes.ndim == 1 && cap_indexes.strides[0] == 1`.

   `cap_data` may have different shapes depending on `ValueType`:
       1. if `ValueType` is a primitive type (e.g. `int32_t`), it will be
          a one dimensional contiguous array, i.e.,
          `cap_data.ndim == 1 && cap_data.strides[0] == 1`.
       2. if `ValueType` is a complex type (e.g. Arc), it will be a two
          dimension array, i.e., it meets the following requirements:
          a) cap_data.ndim == 2.
          b) cap_data.shape[0] == num-elements it stores; note the
             element's type is `ValueType`, which means we view each row of
             `cap_data.data` as one element with type `ValueType`.
          c) cap_data.shape[1] == num-primitive-values in `ValueType`,
             which means we require that `ValueType` can be viewed as a tensor,
             this is true for Arc as it only holds primitive values with same
             type (i.e. `int32_t`), but may need type cast in other cases
             (e.g. ValueType contains both `int32_t` and `float`).
          d) cap_data.strides[0] == num-primitive-values in `ValueType`.
          e) cap_data.strides[1] == 1.

    Note if `data` in Array2 has stride > 1 (i.e. `data`'s type is
    StridedPtr<ValueType>), the requirement of `cap_data` is nearly same with
    case 2 above except cap_data.strides[0] will be greater than
    num-primitive-values in `ValueType`.

*/
template <typename ValueType, bool IsPrimitive, typename I>
class DLPackArray2;

template <typename ValueType, typename I>
class DLPackArray2<ValueType *, true, I> : public Array2<ValueType *, I> {
 public:
  DLPackArray2(py::capsule cap_indexes, py::capsule cap_data)
      : indexes_tensor_(new Tensor(cap_indexes)),
        data_tensor_(new Tensor(cap_data)) {
    CHECK_EQ(indexes_tensor_->NumDim(), 1);
    CHECK_GE(indexes_tensor_->Shape(0), 1);  // must have one element at least
    CHECK_EQ(indexes_tensor_->Stride(0), 1);

    CHECK_EQ(data_tensor_->NumDim(), 1);
    CHECK_GE(data_tensor_->Shape(0), 0);  // num-elements
    CHECK_EQ(data_tensor_->Stride(0), 1);

    int32_t size1 = indexes_tensor_->Shape(0) - 1;
    int32_t size2 = data_tensor_->Shape(0);
    this->Init(size1, size2, indexes_tensor_->Data<I>(),
               data_tensor_->Data<ValueType>());
  }

 private:
  std::unique_ptr<Tensor> indexes_tensor_;
  std::unique_ptr<Tensor> data_tensor_;
};

template <typename ValueType, typename I>
class DLPackArray2<ValueType *, false, I> : public Array2<ValueType *, I> {
 public:
  DLPackArray2(py::capsule cap_indexes, py::capsule cap_data)
      : indexes_tensor_(new Tensor(cap_indexes)),
        data_tensor_(new Tensor(cap_data)) {
    CHECK_EQ(indexes_tensor_->NumDim(), 1);
    CHECK_GE(indexes_tensor_->Shape(0), 1);  // must have one element at least
    CHECK_EQ(indexes_tensor_->Stride(0), 1);

    CHECK_EQ(data_tensor_->NumDim(), 2);
    CHECK_GE(data_tensor_->Shape(0), 0);  // num-elements
    CHECK_EQ(data_tensor_->Shape(1) * data_tensor_->BytesPerElement(),
             sizeof(ValueType));
    CHECK_EQ(data_tensor_->Stride(0) * data_tensor_->BytesPerElement(),
             sizeof(ValueType));
    CHECK_EQ(data_tensor_->Stride(1), 1);

    int32_t size1 = indexes_tensor_->Shape(0) - 1;
    int32_t size2 = data_tensor_->Shape(0);
    this->Init(size1, size2, indexes_tensor_->Data<I>(),
               data_tensor_->Data<ValueType>());
  }

 private:
  std::unique_ptr<Tensor> indexes_tensor_;
  std::unique_ptr<Tensor> data_tensor_;
};

// Note: we can specialized for `StridedPtr` later if we need it.

}  // namespace kk

#endif  // K2_CC_DLPACK_ARRAY_H_
