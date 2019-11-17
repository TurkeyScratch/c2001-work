# Student: James Jefferson LUU
# ID: 30632749
# FIT1045, Assignment 2, Task 2 - Calculator
from math import pow


def tokenization(expr):
    """
    :param expr: "a string representing a mathematical expression [with]
     non-negative numbers [, operators, parentheses and] potentially spaces".
    :return: "a list of tokens (str or natural float) corresponding to the
     given expression."
    """
    return tokenization_a(list(expr.replace(" ", "")))


def tokenization_a(expr):
    # empty expression base case
    if len(expr) == 0:
        return []
    token = expr.pop(0)
    # float case loop, otherwise treated as string for operators and brackets
    if float_conditions(token):
        while len(expr) > 0 and float_conditions(expr[0]):
            token += expr.pop(0)
        token = float(token)
    return [token] + tokenization_a(expr)


def float_conditions(token):
    return token.isdigit() or token == "."


def has_precedence(op1, op2):
    """
    :param op1: first operator token
    :param op2: second operator token
    :return: True if op1 takes precedence over op2, else False.
    "+" with "-", and "*" with "/" are the same precedence and return False.
    """
    precedence = {"+": 0, "-": 0, "*": 1, "/": 1, "^": 2}
    return precedence[op1] > precedence[op2]


def simple_evaluation(tokens):
    """
    :param tokens: a list of tokens (excluding parentheses)
    :return: "single floating point number corresponding to the result
    of the tokenized arithmetic expression."
    """
    return simple_evaluation_a(tokens[:])


def simple_evaluation_a(tokens):
    while len(tokens) > 1:
        i = max_precedence(tokens) if len(tokens) >= 5 else 1
        # replace operator and surrounding tokens with result of tokens
        y, op, x = tokens.pop(i + 1), tokens.pop(i), tokens.pop(i - 1)
        result = x + y if op == '+' else x - y if op == '-' else \
                 x * y if op == '*' else x / y if op == '/' \
                 else pow(x, y)
        tokens.insert(i - 1, result)
    return float(tokens[0])


def max_precedence(tokens, op1=1, op2=3):
    """
    :param tokens: a list of tokens (excluding parentheses)
    :param op1: default to first operator
    :param op2: default to second operator
    :return: index of the highest precedence in tokens
    assume no parentheses in tokens, and left to right precedence
    """
    token1, token2 = tokens[op1], tokens[op2]
    last_op = (op2 == len(tokens) - 2)
    # greater or same precedence case
    if has_precedence(token1, token2) or token1 == token2 \
            or {token1, token2} in [{'+', '-'}, {'*', '/'}]:
        if last_op:
            return op1
        return max_precedence(tokens, op1, op2 + 2)
    # lesser precedence case
    if last_op:
        return op2
    return max_precedence(tokens, op2, op2 + 2)


def complex_evaluation(tokens):
    """
    :param tokens: a list of tokens (with parentheses)
    :return: "single floating point number corresponding to the result of the
     tokenized arithmetic expression."
    """
    return complex_evaluation_a(tokens[:])


def complex_evaluation_a(tokens):
    while "(" in tokens:
        lo, hi = tokens.index("("), tokens.index(")")
        result, lo, hi = parenthesis_eval(tokens, lo, hi)
        tokens[lo:hi+1] = [result]
    return simple_evaluation_a(tokens)


def parenthesis_eval(tokens, lo, hi):
    if "(" not in tokens[lo+1:hi]:
        return simple_evaluation_a(tokens[lo+1:hi]), lo, hi
    return parenthesis_eval(tokens, tokens[lo+1:hi].index("(") + lo + 1, hi)


def evaluation(string):
    return complex_evaluation_a(tokenization(string))


# 27.1
print(evaluation("(3.1 + 6*(2^2)) * (2 - 1)"))
# -320
print(evaluation("(2-7) * 4^(2+1)"))
# -45
print(evaluation('10-5*4^2+100/4'))
# 45
print(evaluation('((10-5)*4^2+100)/4'))
# 4096
print(evaluation('2^3^4'))
# 2.66...
print(evaluation('2/3*4'))
# -33
print(evaluation('((1+2)*(3-4)*(5+6))'))
# 36
print(evaluation('(((2*(1+1))+2)^2)'))
