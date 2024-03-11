##
# @file math_lib_test.py
# @brief TDD tests for math_lib.py
# @author Magdaléna Bellayová
# @date April 2022
##

import pytest
import math_lib


# testing addition
def test_addition_positive_positive():
    assert math_lib.add(0, 0) == 0
    assert math_lib.add(1, 5) == 6
    assert math_lib.add(5, 12) == 17
    assert math_lib.add(15, 23) == 38
    assert math_lib.add(35, 106) == 141
    assert math_lib.add(157, 189) == 346
    assert math_lib.add(399, 1899) == 2298
    assert math_lib.add(1782, 5968) == 7750
    assert math_lib.add(213874, 4873428) == 5087302
    assert math_lib.add(0.1, 0.1) == 0.2
    assert math_lib.add(0.08872, 5.3479) == 5.43662
    assert math_lib.add(0.111111, 0.222222) == 0.33333
    assert math_lib.add(0.444444, 0.333333) == 0.77778


def test_addition_negative_negative():
    assert math_lib.add(-1, -5) == -6
    assert math_lib.add(-5, -12) == -17
    assert math_lib.add(-15, -23) == -38
    assert math_lib.add(-35, -106) == -141
    assert math_lib.add(-157, -189) == -346
    assert math_lib.add(-399, -1899) == -2298
    assert math_lib.add(-1782, -5968) == -7750
    assert math_lib.add(-213874, -4873428) == -5087302
    assert math_lib.add(-0.1, -0.1) == -0.2
    assert math_lib.add(-0.08872, -5.3479) == -5.43662
    assert math_lib.add(-0.111111, -0.222222) == -0.33333
    assert math_lib.add(-0.444444, -0.333333) == -0.77778


def test_addition_positive_negative():
    assert math_lib.add(0, -1) == -1
    assert math_lib.add(12, -12) == 0
    assert math_lib.add(23, -26) == -3
    assert math_lib.add(158, -232) == -74
    assert math_lib.add(5743, -8793) == -3050
    assert math_lib.add(7342874, -824432) == 6518442
    assert math_lib.add(0.1, -0.1) == 0
    assert math_lib.add(5.346, -3.433) == 1.913
    assert math_lib.add(0.18713, -6.34839) == -6.16126
    assert math_lib.add(0.111111, -0.11109) == 0.00002
    assert math_lib.add(0.222226, -0.222224) == 0
    assert math_lib.add(0.333339, -0.333332) == 0.00001


def test_addition_negative_positive():
    assert math_lib.add(-1, 0) == -1
    assert math_lib.add(-12, 12) == 0
    assert math_lib.add(-26, 23) == -3
    assert math_lib.add(-232, 158) == -74
    assert math_lib.add(-8793, 5743) == -3050
    assert math_lib.add(-824432, 7342874) == 6518442
    assert math_lib.add(-0.1, 0.1) == 0
    assert math_lib.add(-3.433, 5.346) == 1.913
    assert math_lib.add(-6.34839, 0.18713) == -6.16126
    assert math_lib.add(-0.11109, 0.111111) == 0.00002
    assert math_lib.add(-0.222224, 0.222226) == 0
    assert math_lib.add(-0.333332, 0.333339) == 0.00001


# testing subtraction
def test_subtraction_positive_positive():
    assert math_lib.sub(0, 1) == -1
    assert math_lib.sub(12, 12) == 0
    assert math_lib.sub(23, 26) == -3
    assert math_lib.sub(158, 232) == -74
    assert math_lib.sub(5743, 8793) == -3050
    assert math_lib.sub(7342874, 824432) == 6518442
    assert math_lib.sub(0.1, 0.1) == 0
    assert math_lib.sub(5.346, 3.433) == 1.913
    assert math_lib.sub(0.18713, 6.34839) == -6.16126
    assert math_lib.sub(0.111111, 0.11109) == 0.00002
    assert math_lib.sub(0.222226, 0.222224) == 0
    assert math_lib.sub(0.333339, 0.333332) == 0.00001

    assert math_lib.sub(1, 0) == 1
    assert math_lib.sub(12, 12) == 0
    assert math_lib.sub(26, 23) == 3
    assert math_lib.sub(232, 158) == 74
    assert math_lib.sub(8793, 5743) == 3050
    assert math_lib.sub(824432, 7342874) == -6518442
    assert math_lib.sub(0.1, 0.1) == 0
    assert math_lib.sub(3.433, 5.346) == -1.913
    assert math_lib.sub(6.34839, 0.18713) == 6.16126
    assert math_lib.sub(0.11109, 0.111111) == -0.00002
    assert math_lib.sub(0.222224, 0.222226) == 0
    assert math_lib.sub(0.333332, 0.333339) == -0.00001


def test_subtraction_negative_negative():
    assert math_lib.sub(-12, -12) == 0
    assert math_lib.sub(-26, -23) == -3
    assert math_lib.sub(-232, -158) == -74
    assert math_lib.sub(-8793, -5743) == -3050
    assert math_lib.sub(-824432, -7342874) == 6518442
    assert math_lib.sub(-0.1, -0.1) == 0
    assert math_lib.sub(-3.433, -5.346) == 1.913
    assert math_lib.sub(-6.34839, -0.18713) == -6.16126
    assert math_lib.sub(-0.11109, -0.111111) == 0.00002
    assert math_lib.sub(-0.222224, -0.222226) == 0
    assert math_lib.sub(-0.333332, -0.333339) == 0.00001


def test_subtraction_positive_negative():
    assert math_lib.sub(1, -5) == 6
    assert math_lib.sub(5, -12) == 17
    assert math_lib.sub(15, -23) == 38
    assert math_lib.sub(35, -106) == 141
    assert math_lib.sub(157, -189) == 346
    assert math_lib.sub(399, -1899) == 2298
    assert math_lib.sub(1782, -5968) == 7750
    assert math_lib.sub(213874, -4873428) == 5087302
    assert math_lib.sub(0.1, -0.1) == 0.2
    assert math_lib.sub(0.08872, -5.3479) == 5.43662
    assert math_lib.sub(0.111111, -0.222222) == 0.33333
    assert math_lib.sub(0.444444, -0.333333) == 0.77778


def test_subtraction_negative_positive():
    assert math_lib.sub(-1, 5) == -6
    assert math_lib.sub(-5, 12) == -17
    assert math_lib.sub(-15, 23) == -38
    assert math_lib.sub(-35, 106) == -141
    assert math_lib.sub(-157, 189) == -346
    assert math_lib.sub(-399, 1899) == -2298
    assert math_lib.sub(-1782, 5968) == -7750
    assert math_lib.sub(-213874, 4873428) == -5087302
    assert math_lib.sub(-0.1, 0.1) == -0.2
    assert math_lib.sub(-0.08872, 5.3479) == -5.43662
    assert math_lib.sub(-0.111111, 0.222222) == -0.33333
    assert math_lib.sub(-0.444444, 0.333333) == -0.77778


# testing multiplication
def test_multiplication_positive_positive():
    assert math_lib.mul(0, 0) == 0
    assert math_lib.mul(0, 5) == 0
    assert math_lib.mul(1, 7) == 7
    assert math_lib.mul(7, 21) == 147
    assert math_lib.mul(63, 11) == 693
    assert math_lib.mul(129, 328) == 42312
    assert math_lib.mul(2.13, 7.39) == 15.7407
    assert math_lib.mul(0.67, 1.78) == 1.1926
    assert math_lib.mul(0.20, 2.23) == 0.446
    assert math_lib.mul(0.843, 0.567) == 0.47798
    assert math_lib.mul(2.396, 13.158) == 31.52657


def test_multiplication_negative_negative():
    assert math_lib.mul(-1, -7) == 7
    assert math_lib.mul(-7, -21) == 147
    assert math_lib.mul(-63, -11) == 693
    assert math_lib.mul(-129, -328) == 42312
    assert math_lib.mul(-2.13, -7.39) == 15.7407
    assert math_lib.mul(-0.67, -1.78) == 1.1926
    assert math_lib.mul(-0.20, -2.23) == 0.446
    assert math_lib.mul(-0.843, -0.567) == 0.47798
    assert math_lib.mul(-2.396, -13.158) == 31.52657


def test_multiplication_positive_negative():
    assert math_lib.mul(0, -5) == 0
    assert math_lib.mul(1, -7) == -7
    assert math_lib.mul(7, -21) == -147
    assert math_lib.mul(63, -11) == -693
    assert math_lib.mul(129, -328) == -42312
    assert math_lib.mul(2.13, -7.39) == -15.7407
    assert math_lib.mul(0.67, -1.78) == -1.1926
    assert math_lib.mul(0.20, -2.23) == -0.446
    assert math_lib.mul(0.843, -0.567) == -0.47798
    assert math_lib.mul(2.396, -13.158) == -31.52657


def test_multiplication_negative_positive():
    assert math_lib.mul(-5, 0) == 0
    assert math_lib.mul(-1, 7) == -7
    assert math_lib.mul(-7, 21) == -147
    assert math_lib.mul(-63, 11) == -693
    assert math_lib.mul(-129, 328) == -42312
    assert math_lib.mul(-2.13, 7.39) == -15.7407
    assert math_lib.mul(-0.67, 1.78) == -1.1926
    assert math_lib.mul(-0.20, 2.23) == -0.446
    assert math_lib.mul(-0.843, 0.567) == -0.47798
    assert math_lib.mul(-2.396, 13.158) == -31.52657


# testing division
def test_division_error():
    with pytest.raises(ZeroDivisionError):
        assert math_lib.div(-12, 0)
    with pytest.raises(ZeroDivisionError):
        assert math_lib.div(134, 0)
    with pytest.raises(ZeroDivisionError):
        assert math_lib.div(-0.344, 0)
    with pytest.raises(ZeroDivisionError):
        assert math_lib.div(0.8786, 0)


def test_division_positive_positive():
    assert math_lib.div(0, 1) == 0
    assert math_lib.div(5, 1) == 5
    assert math_lib.div(21, 3) == 7
    assert math_lib.div(256, 16) == 16
    assert math_lib.div(31488, 123) == 256
    assert math_lib.div(3, 1.5) == 2
    assert math_lib.div(1.5, 3) == 0.5
    assert math_lib.div(0.55, 11) == 0.05
    assert math_lib.div(21, 0.07) == 300
    assert math_lib.div(0.48, 0.8) == 0.6
    assert math_lib.div(10, 3) == 3.33333
    assert math_lib.div(19, 6) == 3.16667


def test_division_negative_negative():
    assert math_lib.div(-5, -1) == 5
    assert math_lib.div(-21, -3) == 7
    assert math_lib.div(-256, -16) == 16
    assert math_lib.div(-31488, -123) == 256
    assert math_lib.div(-3, -1.5) == 2
    assert math_lib.div(-1.5, -3) == 0.5
    assert math_lib.div(-0.55, -11) == 0.05
    assert math_lib.div(-21, -0.07) == 300
    assert math_lib.div(-0.48, -0.8) == 0.6
    assert math_lib.div(-10, -3) == 3.33333
    assert math_lib.div(-19, -6) == 3.16667


def test_division_positive_negative():
    assert math_lib.div(0, -1) == 0
    assert math_lib.div(5, -1) == -5
    assert math_lib.div(21, -3) == -7
    assert math_lib.div(256, -16) == -16
    assert math_lib.div(31488, -123) == -256
    assert math_lib.div(3, -1.5) == -2
    assert math_lib.div(1.5, -3) == -0.5
    assert math_lib.div(0.55, -11) == -0.05
    assert math_lib.div(21, -0.07) == -300
    assert math_lib.div(0.48, -0.8) == -0.6
    assert math_lib.div(10, -3) == -3.33333
    assert math_lib.div(19, -6) == -3.16667


def test_division_negative_positive():
    assert math_lib.div(-5, 1) == -5
    assert math_lib.div(-21, 3) == -7
    assert math_lib.div(-256, 16) == -16
    assert math_lib.div(-31488, 123) == -256
    assert math_lib.div(-3, 1.5) == -2
    assert math_lib.div(-1.5, 3) == -0.5
    assert math_lib.div(-0.55, 11) == -0.05
    assert math_lib.div(-21, 0.07) == -300
    assert math_lib.div(-0.48, 0.8) == -0.6
    assert math_lib.div(-10, 3) == -3.33333
    assert math_lib.div(-19, 6) == -3.16667


# testing modulo
def test_modulo_error():
    with pytest.raises(ZeroDivisionError):
        assert math_lib.mod(-12, 0)
    with pytest.raises(ZeroDivisionError):
        assert math_lib.mod(134, 0)
    with pytest.raises(ValueError):
        assert math_lib.mod(11, 1.231)
    with pytest.raises(ValueError):
        assert math_lib.mod(11.213, 31)
    with pytest.raises(ValueError):
        assert math_lib.mod(0.213, 0.231)
    with pytest.raises(ValueError):
        assert math_lib.mod(11, -1.231)
    with pytest.raises(ValueError):
        assert math_lib.mod(-11.213, 31)
    with pytest.raises(ValueError):
        assert math_lib.mod(-0.213, -0.231)


def test_modulo_positive_positive():
    assert math_lib.mod(0, 1) == 0
    assert math_lib.mod(5, 2) == 1
    assert math_lib.mod(26, 3) == 2
    assert math_lib.mod(270, 16) == 14
    assert math_lib.mod(31589, 123) == 101


def test_modulo_negative_negative():
    assert math_lib.mod(-5, -2) == -1
    assert math_lib.mod(-26, -3) == -2
    assert math_lib.mod(-270, -16) == -14
    assert math_lib.mod(-31589, -123) == -101


def test_modulo_positive_negative():
    assert math_lib.mod(0, -1) == 0
    assert math_lib.mod(5, -2) == 1
    assert math_lib.mod(26, -3) == 2
    assert math_lib.mod(270, -16) == 14
    assert math_lib.mod(31589, -123) == 101


def test_modulo_negative_positive():
    assert math_lib.mod(-5, 2) == -1
    assert math_lib.mod(-26, 3) == -2
    assert math_lib.mod(-270, 16) == -14
    assert math_lib.mod(-31589, 123) == -101


# testing power
def test_power_error():
    with pytest.raises(ValueError):
        assert math_lib.pow(10, -3)
    with pytest.raises(ValueError):
        assert math_lib.pow(-10, -3)
    with pytest.raises(ValueError):
        assert math_lib.pow(5, 0.1)
    with pytest.raises(ValueError):
        assert math_lib.pow(-5, 1.2)
    with pytest.raises(ValueError):
        assert math_lib.pow(5, -0.1)
    with pytest.raises(ValueError):
        assert math_lib.pow(-5, -1.2)


def test_power():
    assert math_lib.pow(2, 0) == 1
    assert math_lib.pow(-2, 0) == 1
    assert math_lib.pow(13, 1) == 13
    assert math_lib.pow(-13, 1) == -13
    assert math_lib.pow(5, 2) == 25
    assert math_lib.pow(-5, 2) == 25
    assert math_lib.pow(112, 2) == 12544
    assert math_lib.pow(-112, 2) == 12544
    assert math_lib.pow(7, 3) == 343
    assert math_lib.pow(-7, 3) == -343
    assert math_lib.pow(12, 4) == 20736
    assert math_lib.pow(-12, 4) == 20736
    assert math_lib.pow(9, 5) == 59049
    assert math_lib.pow(-9, 5) == -59049
    assert math_lib.pow(3, 11) == 177147
    assert math_lib.pow(-3, 11) == -177147
    assert math_lib.pow(0.4, 2) == 0.16
    assert math_lib.pow(-0.4, 2) == 0.16
    assert math_lib.pow(7.89, 4) == 3875.32395
    assert math_lib.pow(-7.89, 4) == 3875.32395
    assert math_lib.pow(5.67, 7) == 188400.22289
    assert math_lib.pow(-5.67, 7) == -188400.22289


# testing root
def test_root_error():
    with pytest.raises(ValueError):
        assert math_lib.root(-10, 2)
    with pytest.raises(ValueError):
        assert math_lib.root(10, -3)
    with pytest.raises(ValueError):
        assert math_lib.root(-10, -3)
    with pytest.raises(ValueError):
        assert math_lib.root(5, 0.1)
    with pytest.raises(ValueError):
        assert math_lib.root(-5, 1.2)
    with pytest.raises(ValueError):
        assert math_lib.root(5, -0.1)
    with pytest.raises(ValueError):
        assert math_lib.root(-5, -1.2)


def test_root():
    assert math_lib.root(16, 2) == 4
    assert math_lib.root(16, 2) == 4
    assert math_lib.root(27, 3) == 3
    assert math_lib.root(-27, 3) == -3
    assert math_lib.root(2401, 4) == 7
    assert math_lib.root(161051, 5) == 11
    assert math_lib.root(-161051, 5) == -11
    assert math_lib.root(0.0625, 4) == 0.5
    assert math_lib.root(3.2, 3) == 1.47361
    assert math_lib.root(-3.2, 3) == -1.47361


# testing sinus
def test_sinus_positive():
    assert math_lib.sin(0) == 0
    assert math_lib.sin(math_lib.pi / 6) == 0.5
    assert math_lib.sin(math_lib.pi / 4) == 0.70711
    assert math_lib.sin(math_lib.pi / 3) == 0.86603
    assert math_lib.sin(math_lib.pi / 2) == 1
    assert math_lib.sin(2 * math_lib.pi / 3) == 0.86603
    assert math_lib.sin(3 * math_lib.pi / 4) == 0.70711
    assert math_lib.sin(5 * math_lib.pi / 6) == 0.5
    assert math_lib.sin(math_lib.pi) == 0
    assert math_lib.sin(7 * math_lib.pi / 6) == -0.5
    assert math_lib.sin(5 * math_lib.pi / 4) == -0.70711
    assert math_lib.sin(4 * math_lib.pi / 3) == -0.86603
    assert math_lib.sin(3 * math_lib.pi / 2) == -1
    assert math_lib.sin(5 * math_lib.pi / 3) == -0.86603
    assert math_lib.sin(7 * math_lib.pi / 4) == -0.70711
    assert math_lib.sin(11 * math_lib.pi / 6) == -0.5
    assert math_lib.sin(2 * math_lib.pi) == 0


def test_sinus_negative():
    assert math_lib.sin(-math_lib.pi / 6) == -0.5
    assert math_lib.sin(-math_lib.pi / 4) == -0.70711
    assert math_lib.sin(-math_lib.pi / 3) == -0.86603
    assert math_lib.sin(-math_lib.pi / 2) == -1
    assert math_lib.sin(-2 * math_lib.pi / 3) == -0.86603
    assert math_lib.sin(-3 * math_lib.pi / 4) == -0.70711
    assert math_lib.sin(-5 * math_lib.pi / 6) == -0.5
    assert math_lib.sin(- math_lib.pi) == 0
    assert math_lib.sin(-7 * math_lib.pi / 6) == 0.5
    assert math_lib.sin(-5 * math_lib.pi / 4) == 0.70711
    assert math_lib.sin(-4 * math_lib.pi / 3) == 0.86603
    assert math_lib.sin(-3 * math_lib.pi / 2) == 1
    assert math_lib.sin(-5 * math_lib.pi / 3) == 0.86603
    assert math_lib.sin(-7 * math_lib.pi / 4) == 0.70711
    assert math_lib.sin(-11 * math_lib.pi / 6) == 0.5
    assert math_lib.sin(-2 * math_lib.pi) == 0


# testing cosine
def test_cosine_positive():
    assert math_lib.cos(0) == 1
    assert math_lib.cos(math_lib.pi / 6) == 0.86603
    assert math_lib.cos(math_lib.pi / 4) == 0.70711
    assert math_lib.cos(math_lib.pi / 3) == 0.5
    assert math_lib.cos(math_lib.pi / 2) == 0
    assert math_lib.cos(2 * math_lib.pi / 3) == -0.5
    assert math_lib.cos(3 * math_lib.pi / 4) == -0.70711
    assert math_lib.cos(5 * math_lib.pi / 6) == -0.86603
    assert math_lib.cos(math_lib.pi) == -1
    assert math_lib.cos(7 * math_lib.pi / 6) == -0.86603
    assert math_lib.cos(5 * math_lib.pi / 4) == -0.70711
    assert math_lib.cos(4 * math_lib.pi / 3) == -0.5
    assert math_lib.cos(3 * math_lib.pi / 2) == 0
    assert math_lib.cos(5 * math_lib.pi / 3) == 0.5
    assert math_lib.cos(7 * math_lib.pi / 4) == 0.70711
    assert math_lib.cos(11 * math_lib.pi / 6) == 0.86603
    assert math_lib.cos(2 * math_lib.pi) == 1


def test_cosine_negative():
    assert math_lib.cos(-math_lib.pi / 6) == 0.86603
    assert math_lib.cos(-math_lib.pi / 4) == 0.70711
    assert math_lib.cos(-math_lib.pi / 3) == 0.5
    assert math_lib.cos(-math_lib.pi / 2) == 0
    assert math_lib.cos(-2 * math_lib.pi / 3) == -0.5
    assert math_lib.cos(-3 * math_lib.pi / 4) == -0.70711
    assert math_lib.cos(-5 * math_lib.pi / 6) == -0.86603
    assert math_lib.cos(-math_lib.pi) == -1
    assert math_lib.cos(-7 * math_lib.pi / 6) == -0.86603
    assert math_lib.cos(-5 * math_lib.pi / 4) == -0.70711
    assert math_lib.cos(-4 * math_lib.pi / 3) == -0.5
    assert math_lib.cos(-3 * math_lib.pi / 2) == 0
    assert math_lib.cos(-5 * math_lib.pi / 3) == 0.5
    assert math_lib.cos(-7 * math_lib.pi / 4) == 0.70711
    assert math_lib.cos(-11 * math_lib.pi / 6) == 0.86603
    assert math_lib.cos(-2 * math_lib.pi) == 1


# testing tangens
def test_tangens_error():
    with pytest.raises(ValueError):
        assert math_lib.tan(math_lib.pi / 2)
    with pytest.raises(ValueError):
        assert math_lib.tan(- math_lib.pi / 2)
    with pytest.raises(ValueError):
        assert math_lib.tan(3 * math_lib.pi / 2)
    with pytest.raises(ValueError):
        assert math_lib.tan(- 3 * math_lib.pi / 2)
    with pytest.raises(ValueError):
        assert math_lib.tan(5 * math_lib.pi / 2)
    with pytest.raises(ValueError):
        assert math_lib.tan(- 5 * math_lib.pi / 2)


def test_tangens_positive():
    assert math_lib.tan(0) == 0
    assert math_lib.tan(math_lib.pi / 6) == 0.57735
    assert math_lib.tan(math_lib.pi / 4) == 1
    assert math_lib.tan(math_lib.pi / 3) == 1.73205
    assert math_lib.tan(2 * math_lib.pi / 3) == -1.73205
    assert math_lib.tan(3 * math_lib.pi / 4) == -1
    assert math_lib.tan(5 * math_lib.pi / 6) == -0.57735
    assert math_lib.tan(math_lib.pi) == 0


def test_tangens_negative():
    assert math_lib.tan(-math_lib.pi / 6) == -0.57735
    assert math_lib.tan(-math_lib.pi / 4) == -1
    assert math_lib.tan(-math_lib.pi / 3) == -1.73205
    assert math_lib.tan(-2 * math_lib.pi / 3) == 1.73205
    assert math_lib.tan(-3 * math_lib.pi / 4) == 1
    assert math_lib.tan(-5 * math_lib.pi / 6) == 0.57735
    assert math_lib.tan(-math_lib.pi) == 0


# testing logarithm
def test_logarithm_error():
    with pytest.raises(ValueError):
        assert math_lib.log(0)
    with pytest.raises(ValueError):
        assert math_lib.log(-1)
    with pytest.raises(ValueError):
        assert math_lib.log(-5.434)


def test_logarithm():
    assert math_lib.log(0.1) == -1
    assert math_lib.log(1) == 0
    assert math_lib.log(10) == 1
    assert math_lib.log(100) == 2
    assert math_lib.log(1000) == 3
    assert math_lib.log(10000) == 4
    assert math_lib.log(100000) == 5
    assert math_lib.log(1000000) == 6
    assert math_lib.log(555) == 2.74429
    assert math_lib.log(56) == 1.74819


# testing factorial
def test_factorial_error():
    with pytest.raises(ValueError):
        assert math_lib.factorial(-5)
    with pytest.raises(ValueError):
        assert math_lib.factorial(-10)
    with pytest.raises(ValueError):
        assert math_lib.factorial(-0.1)
    with pytest.raises(ValueError):
        assert math_lib.factorial(1.2)


def test_factorial():
    assert math_lib.factorial(0) == 1
    assert math_lib.factorial(1) == 1
    assert math_lib.factorial(5) == 120
    assert math_lib.factorial(10) == 3628800