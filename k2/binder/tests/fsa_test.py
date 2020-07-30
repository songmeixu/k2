#!/usr/bin/env python3
#
# Copyright (c)  2020  Fangjun Kuang (csukuangfj@gmail.com)
#                      Meixu Sing (Xiaomi Corporation songmeixu@outlook.com )
#
# See ../../../LICENSE for clarification regarding multiple authors

# To run this single test, use
#
#  pytest fsa_test.py
#

import sys

import cppyy
import pytest
from cppyy.gbl import kk

import k2

# def test_k2_widget():
#     w = kk.k2Widget(-3)
#     assert w.get() == -3
#
#
# @pytest.mark.parametrize(
#     "member_t, member_val", [(int, 1), (float, 3.1), (bool, False)]
# )
# def test_k2_gadget(member_t, member_val):
#     g = k2.k2Gadget[member_t](member_val)
#     assert g.get() == pytest.approx(member_val)

SKIP_DLPACK = False


class TestFsa:
    def test_arc(self):
        arc = kk.Arc(1, 2, 3)
        assert arc.src_state == 1
        assert arc.dest_state == 2
        assert arc.label == 3

    def test_fsa(self):
        s = r"""
        0 1 1
        0 2 2
        1 3 3
        2 3 3
        3 4 -1
        4
        """

        fsa = kk.str_to_fsa(s)
        assert fsa.num_states() == 5
        assert fsa.final_state() == 4
        assert fsa.empty()
        assert isinstance(fsa, kk.Fsa)
        assert isinstance(fsa.data(0), kk.Arc)
        assert fsa.data(0).src_state == 0
        assert fsa.data(0).dest_state == 1
        assert fsa.data(0).label == 1
