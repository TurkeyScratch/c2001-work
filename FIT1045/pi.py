"""
:author:     James Jefferson Luu
:id:         30632749
:assignment: FIT1045 Assignment 1, Task 1 (Semester 1 2019)
:purpose:    Performs and compares algorithms that approximate pi.
:created:    2019-11-13 (remade within two hours)
:updated:    2019-11-17 (documentation)

This assignment task has since been replaced as of 2019-11-17.
"""
from math import pi, sqrt    # relevant modules to compare pi and get square root


def incomplete(x, precision):
    # sub-function that confirms if difference of pi and x is under precision
    assert type(precision) == float
    return abs(pi - x) >= precision


def odd(x):
    # sub-function that calculates the xth odd number (for x > 0)
    assert x > 0
    return 2 * (x-1) + 1
    
    
def basel(precision: int):
    """
    This function calculates an approximation of pi using the basel solution.
    pi**2 = 1/(n**2) for n terms
    
    :param precision: represents how far the final result should be from pi
    :returns:         tuple (x, n) where x is the approximation of pi and n is
                      the computations made to get to x.
    :pre-condition:   precision must be an float
    :raises:          AssertionError, when the pre-condition is not met
    """
    # initialise return integers
    x = 0
    n = 0
    sub_x = 0
    # calculates x = sqrt(6 * (Σ i ** -2)) for i = 1 to n
    # stops when difference between actual pi and x is under precision
    while incomplete(x, precision):
        n += 1
        sub_x += (n ** -2)
        x = sqrt(6 * sub_x)
    return x, n
    

def taylor(precision: int):
    """
    This function calculates an approximation of pi using the taylor expansion
    of 1 / (1+x).
    pi / 4 = 1/1 - 1/3 + 1/5 - 1/7 + ...
    
    :param precision: represents how far the final result should be from pi
    :returns:         tuple (x, n) where x is the approximation of pi and n is
                      the computations made to get to x.
    :pre-condition:   precision must be an float
    :raises:          AssertionError, when the pre-condition is not met
    """
    # initialise return integers
    x = 0
    n = 0
    # calculates ith odd number N for x = 4 * Σ ([-1 ** (n-1)] * [N ** -1]) 
    # from i = 1 to n
    # stops when difference between actual pi and x is under precision
    while incomplete(x, precision):
        n += 1
        taylor_poly = odd(n) ** -1
        taylor_poly *= (-1) ** (n-1)
        x += 4 * taylor_poly
    return x, n
    
    
def wallis(precision: int):
    """
    This function calculates an approximation of pi using the wallis algorithm.
    L represents nth even number, M and N are nth and n+1 odd numbers
    pi / 2 = ∏(L**2/M*N)
    
    :param precision: represents how far the final result should be from pi
    :returns:         tuple (x, n) where x is the approximation of pi and n is
                      the computations made to get to x.
    :pre-condition:   precision must be an float
    :raises:          AssertionError, when the pre-condition is not met
    """
    # initialise return integers
    x = 0
    n = 0
    # twice of (nth even number squared divided by nth * n+1 odd number)
    # stops when difference between actual pi and x is under precision
    while incomplete(x, precision):
        if x == 0:
            x = 2
        n += 1
        numerator = (n * 2) ** 2
        denominator = odd(n) * odd(n+1)
        x *= (numerator / denominator)
    return x, n    
    
    
def spigot(precision: int):
    """
    This function calculates an approximation of pi using the spigot algorithm.   
    N is i+1 odd number
    pi / 2 = 1 + Σ(∏(i / N) for i = 1 to n) for 1 to n
    
    :param precision: represents how far the final result should be from pi
    :returns:         tuple (x, n) where x is the approximation of pi and n is
                      the computations made to get to x.
    :pre-condition:   precision must be an float
    :raises:          AssertionError, when the pre-condition is not met
    """
    # initialise return integers
    x = 0
    n = 0
    # initialise stored product of nth term
    product = 0
    # last product * (n-1 / N) N = nth odd number 
    # stops when difference between actual pi and x is under precision
    while incomplete(x, precision):
        n += 1
        # if initial value, set x to 2 and last product to 1
        if x == 0:
            x = 2
            product = 1 
        else:
            product *= ((n - 1) / odd(n))
            x += 2 * product
    return x, n


def race(precision, algorithms):
    """
    This function takes the algorithms and compares them in terms of 
    approximating pi by number of terms required.
    
    :param precision:  represents how far the final result should be from pi
    :param algorithms: List of algorithm functions to approximate pi
    :returns:          List [(i0, n0), (i1, n1) ...] where n represents 
                       the number of steps the ith algorithm took. Sorted by n
    :pre-condition:    precision must be an float
    :pre-condition:    functions of algorithms must be in namespace of program
    :raises:           AssertionError, when first pre-condition is not met
    :raises:           NameError, when second pre-condition is not met
    """
    results = []
    for i, func in enumerate(algorithms, start=1):
        n = func(precision)[1]
        results.append((i, n))
    return sorted(results, key = lambda x : x[1])
    

def print_results(results):
    """
    This function takes the results from the previous function, race()
    and prints them in a human readable format.
    
    :param results:    Output from race()
    :returns:          None, prints out based on parameter.
    :pre-condition:    must be a list of tuples (should be output of race())
    :raises:           TypeError/IndexError, when pre-condition is not met
    """
    for tuple in results:
        print("Algorithm {0[0]} finished in {0[1]} steps".format(tuple))
    
    
if __name__=="__main__":
    assert basel(0.1)[1] == 10
    assert taylor(0.2)[1] == 5
    assert wallis(0.2)[1] == 4
    assert spigot(0.1)[1] == 4
    assert race(0.01, [taylor, wallis, basel]) == [(2, 78), (3, 96), (1, 100)]
    print_results([(2, 78), (3, 96), (1, 100)])
    print("No errors. All assert test cases were successful.")