##
# @file profiling.py
# @brief skript for profiling measures
# @author Matúš Vráblik
# @date April 2022
##

# Imports
from sys import stderr
import math_lib as ml
import cProfile


##
# @brief function using all functions from math_lib
# @param FILE file filled with values for math_lib functions
def deviation(FILE):
    sum = 0
    squaresum = 0
    N = 0
    for line in FILE:
        sum = ml.add(float(line),sum)
        squaresum = ml.add(ml.pow(float(line),2),squaresum)
        N += 1
    mean = ml.div(sum,N)
    meanSquared = ml.pow(mean,2)
    NmeanSquared = ml.mul(N,meanSquared)
    dev = ml.root(ml.mul(ml.div(1,ml.sub(N,1)),NmeanSquared),2)
    return dev

if __name__ == '__main__' :
    print("#Test 1 - test 10 values",end='\n\n')
    FILE = open('../profiling/10.txt')
    cProfile.run('deviation(FILE)')
    print("########################################################################\n")
    print("#Test 2 - test 100 values",end='\n\n')
    FILE = open('../profiling/100.txt')
    cProfile.run('deviation(FILE)')
    print("########################################################################\n")
    print("#Test 3 - test 1 000 values",end='\n\n')
    FILE = open('../profiling/1_000.txt')
    cProfile.run('deviation(FILE)')
    print("########################################################################\n")
    print("#Test 4 - test 10 000 values",end='\n\n')
    FILE = open('../profiling/10_000.txt')
    cProfile.run('deviation(FILE)')
    print("########################################################################\n")
    print("#Test 5 - test 100 000 values",end='\n\n')
    FILE = open('../profiling/100_000.txt')
    cProfile.run('deviation(FILE)')
    print("########################################################################\n")
    print("#Test 5 - test 1 000 000 values",end='\n\n')
    FILE = open('../profiling/1_000_000.txt')
    cProfile.run('deviation(FILE)')