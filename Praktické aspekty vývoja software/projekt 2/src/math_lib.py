##
# @file math_lib.py
# @brief mathematical library
# @author Magdaléna Bellayová
# @date April 2022
##

# Imports
import math

# Global Constants
## value of Pi
pi = math.pi
## value of e
e = math.e


# Functions
##
# @brief Function for addition of 2 numbers
# @param x augend
# @param y addend
# @return sum
def add(x, y):
    return round(x + y, 5)


##
# @brief Function for subtraction of 2 numbers
# @param x minuend
# @param y subtrahend
# @return difference
def sub(x, y):
    return round(x - y, 5)


##
# @brief Function for multiplication of 2 numbers
# @param x multiplier
# @param y multiplicand
# @return product
def mul(x, y):
    return round(x * y, 5)


##
# @brief Function for division of 2 numbers
# @param x dividend
# @param y divisor
# @return ratio
def div(x, y):
    if y == 0:
        raise ZeroDivisionError
    return round(x / y, 5)


##
# @brief Function for modulo
# @param x dividend
# @param y divisor
# @return remainder
def mod(x, y):
    if y == 0:
        raise ZeroDivisionError
    if isinstance(x, float):
        raise ValueError
    if isinstance(y, float):
        raise ValueError
    if x >= 0 and y > 0:
        return round(x % y, 5)
    if x <= 0 and y < 0:
        return round(x % y, 5)
    if x < 0:
        return -(round((-x) % y, 5))
    if y < 0:
        return round(x % (-y), 5)


##
# @brief Function for exponentiation of 2 numbers
# @param x base
# @param y exponent
# @return power
def pow(x, y):
    if y < 0:
        raise ValueError
    if isinstance(y, float):
        raise ValueError
    return round(x**y, 5)


##
# @brief Function for root of 2 numbers
# @param x radicand
# @param y degree
# @return root
def root(x, y):
    if x < 0 and y % 2 == 0:
        raise ValueError
    if y < 0:
        raise ValueError
    if isinstance(y, float):
        raise ValueError
    if x < 0 and y % 2 != 0:
        return -round((-x) ** (1 / y), 5)
    return round(x**(1/y), 5)


##
# @brief Function for goniometric function sinus
# @param x angle in radians
# @return sinus
def sin(x):
    return round(math.sin(x), 5)


##
# @brief Function for goniometric function cosinus
# @param x angle in radians
# @return cosinus
def cos(x):
    return round(math.cos(x), 5)


##
# @brief Function for goniometric function tangens
# @param x angle in radians
# @return tangens
def tan(x):
    not_defined = 2*x/math.pi
    if not_defined.is_integer() and not_defined % 2 != 0:
        raise ValueError
    return round(math.tan(x),5)


##
# @brief Function for logarithm with base 10
# @param x antilogarithm
# @return logarithm
def log(x):
    if x <= 0:
        raise ValueError
    return round(math.log10(x), 5)


##
# @brief Function for factorial
# @param x input of factorial
# @return factorial
def factorial(x):
    if x < 0:
        raise ValueError
    if isinstance(x, float):
        raise ValueError
    return round(math.factorial(x), 5)
