import random
from math import floor
from math import gcd
from math import lcm
from fractions import Fraction
def get_fractions(line):
    line = line.split()
    i1 = int(line[0])
    i2 = int(line[1])
    i3 = int(line[2])
    i4 = int(line[3])
    num1 = Fraction(i1, i2)
    num2 = Fraction(i3, i4)
    return num1, num2

def get_nums(line):
    line = line.split()
    num1 = int(line[0])
    num2 = int(line[1])
    return num1, num2
    
def gen_test_cases():
    f = open("tests/test_cases.txt" ,"w")
    for i in range(100):
        l = 100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
        l = l ** 10;
        num1 = random.randrange(-1 * l, l)
        num2 = random.randrange(-100, 100)
        if num2 != 0:
            f.write(str(num1))
            f.write(" ")
            f.write(str(num2))
            f.write("\n")
    f.close()

def solve_additions():
    lines = open("tests/test_cases.txt", "r").readlines()
    f = open("tests/addition.txt", "w")
    for line in lines:
        num1, num2 = get_nums(line)
        num3 = num1 + num2
        f.write(str(num3) + "\n")
    
    f.close()
    

def solve_subtractions():
    lines = open("tests/test_cases.txt", "r").readlines()
    f = open("tests/subtraction.txt", "w")
    for line in lines:
        num1,num2 = get_nums(line)
        num3 = num1 - num2
        f.write(str(num3) + "\n")
    
    f.close()


def solve_multiplications():
    lines = open("tests/test_cases.txt", "r").readlines()
    f = open("tests/mul.txt", "w")
    for line in lines:
        num1,num2 = get_nums(line)
        num3 = num1 * num2
        f.write(str(num3) + "\n")
    
    f.close()

def solve_divisions():
    lines = open("tests/test_cases.txt", "r").readlines()
    f = open("tests/div.txt", "w")
    for line in lines:
        num1,num2 = get_nums(line)
        quotient = num1 // num2
        f.write(str(quotient) + "\n")

def solve_modulos():
    lines = open("tests/test_cases.txt", "r").readlines()
    f = open("tests/mod.txt", "w")
    for line in lines:
        num1,num2 = get_nums(line)
        remainder = (num1 % num2)
        f.write(str(remainder) + "\n")

def solve_gcds():
    lines = open("tests/test_cases.txt", "r").readlines()
    f = open("tests/gcd.txt", "w")
    for line in lines:
        num1,num2 = get_nums(line)
        g = gcd(num1, num2)
        f.write(str(g) + "\n")
def solve_rationals():
    lines = open("tests/test_cases.txt", "r").readlines()
    f = open("tests/rational.txt", "w")
    for line in lines:
        num1,num2 = get_nums(line)
        g = gcd(num1, num2)
        num1 = num1//g
        num2 = num2//g
        f.write(str(num1) + "/" + str(num2) + "\n")
    
def gen_rational_test_cases():
    f = open("tests/rational_test_cases.txt" ,"w")
    for i in range(100):
        l = 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
        num1 = random.randrange(-1 * l, l)
        num2 = random.randrange(-l, l)
        num3 = random.randrange(-1 * l, l)
        num4 = random.randrange(-l, l)
        if num2 != 0 and num4 != 0:
            f.write(str(num1))
            f.write(" ")
            f.write(str(num2))
            f.write(" ")
            f.write(str(num3))
            f.write(" ")
            f.write(str(num4))
            f.write("\n")
    f.close()

def solve_rational_additions():
    lines = open("tests/rational_test_cases.txt", "r").readlines()
    f = open("tests/addition_rational.txt", "w")
    for line in lines:
        num1, num2 = get_fractions(line)
        num3 = num1 + num2
        f.write(str(num3) + "\n")
    
    f.close()
    

def solve_rational_subtractions():
    lines = open("tests/rational_test_cases.txt", "r").readlines()
    f = open("tests/subtraction_rational.txt", "w")
    for line in lines:
        num1, num2 = get_fractions(line)
        num3 = num1 - num2
        f.write(str(num3) + "\n")

    f.close()


def solve_rational_multiplications():
    lines = open("tests/rational_test_cases.txt", "r").readlines()
    f = open("tests/mul_rational.txt", "w")
    for line in lines:
        num1, num2 = get_fractions(line)
        num3 = num1 * num2
        f.write(str(num3) + "\n")
    
    f.close()

def solve_rational_divisions():
    lines = open("tests/rational_test_cases.txt", "r").readlines()
    f = open("tests/div_rational.txt", "w")
    for line in lines:
        num1, num2 = get_fractions(line)
        num3 = num1 * num2
        num3 = num1 / num2
        f.write(str(num3) + "\n")
    
    f.close()

def gen_bst_test_cases():
    f = open("tests/bst_test_cases.txt" ,"w")
    n = 10000;
    l = 1000000000000000000000000000000000000000000000000;
    f.write(str(n) + "\n")
    s = set()
    for i in range(n):
        num = str(random.randrange(l))
        if num not in s:
            f.write(num + "\n")
            s.add(num)
    f.close()
    
gen_test_cases()
solve_additions()
solve_subtractions()
solve_multiplications()
solve_divisions()
solve_modulos()
solve_gcds()
solve_rationals()
gen_rational_test_cases()
solve_rational_additions()
solve_rational_subtractions()
solve_rational_multiplications()
solve_rational_divisions()
gen_bst_test_cases()
