import pytest
from EX01.is_replicant_2v import can_be_replicant_by_indicators, is_replicant

def test_can_be_replicant_by_indicators_valid():
    assert can_be_replicant_by_indicators([12, 60, 2, 4]) is True
    assert can_be_replicant_by_indicators([10, 50, 4, 6]) is False

def test_can_be_replicant_by_indicators_invalid_length():
    with pytest.raises(ValueError):
        can_be_replicant_by_indicators([12, 60, 2])  # Only 3 elements

def test_is_replicant_valid():
    ans_inds = (
        [1, 2, 3, 1],  # Sample answers
        [[12, 60, 2, 4], [10, 50, 3, 6], [18, 120, 1, 2], [16, 61, 5, 7]]
    )
    assert is_replicant(ans_inds) is True

def test_is_replicant_not_replicant():
    ans_inds = (
        [3, 2, 1, 3],  # Sample answers
        [[10, 50, 4, 6], [11, 59, 3, 5], [12, 60, 3, 5], [15, 60, 3, 5]]
    )
    assert is_replicant(ans_inds) is False
