# Copyright (c)  2020  Haowen Qiu (Xiaomi Corporation)
#                      Meixu Song (Xiaomi Corporation)
#
# See ../../../LICENSE for clarification regarding multiple authors

import torch
from torch.utils.dlpack import to_dlpack

from kk import DLPackFsa


class Fsa(DLPackFsa):

    # TODO(haowen): add methods to construct object with Array2Size
    def __init__(self, indexes: torch.Tensor, data: torch.Tensor):
        super().__init__(to_dlpack(indexes), to_dlpack(data))
