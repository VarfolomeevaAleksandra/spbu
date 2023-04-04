# -*- coding: cp1251 -*-

import random
import math

print('Задача алгебраического интерполирования')
print('Вариант 1')

def function(x):
    f = math.sin(x) - x**2/2
    return f

print('Введите количество значений')
m = int(input())
        
print ('Введите границы интервала')
a = float(input())
b = float(input())

h = abs(b - a) / (m)

val = [0.0] * m
for i in range(m):
    val[i] = [0.0] * 3

def table():
    k = 0
    while k < m:
        a_1 = a + h * k
        b_1 = a + h * (k + 1)
        x = random.uniform(a_1, b_1)
        f = function(x)
        val[k][0] = x
        val[k][1] = f
        k = k + 1
    return val

val = table()


def print_table(t):        
    for i in range(t):
        print('%-3d %-10.5f %-15.15f' % (i, val[i][0], val[i][1]))

print_table(len(val))

while True:

    print('Введите точку интерполяции')

    x = float(input())

    print('Введите степень многочлена не выше', m)

    def check_degree():
        n = int(input())
        if n > m:
            while True:
                print('Недопустимая степень, введите заново')
                n = int(input())
                if n <= m:
                    break
        return n
 
    n = check_degree()


    def sort_col(i):
        return i[2]

    def sort():
        i = 0
        while i < m:
            val[i][2] = abs(val[i][0] - x)
            i = i + 1
        val.sort(key = sort_col)
    
    sort()    
    print_table(n)  

    def lagrange_coefficients(val):
        coefficients = []
        for i in range(n):
           xi = val[i][0]
           yi = val[i][1]
           li = 1
           for j in range(n):
                if i == j:
                    continue
                xj = val[j][0]
                yj = val[j][1]
                li *= (x - xj) / (xi - xj)
           coefficients.append(li)
        return coefficients

    coefficients = lagrange_coefficients(val)


    def lagrange_interpolate(x, val, coefficients):
        lx = 0
        for i in range(n):
            xi, yi = val[i][0], val[i][1]
            li = coefficients[i]
            lx += li * yi
        return lx

    lx = lagrange_interpolate(x, val, coefficients)

    print('%-22s %-15.15f' % ('Значение в точке', function(x)))
    print('%-22s %-15.15f' % ('Интерполяция Лагранж', lx))
    print('%-22s %-15.15f' % ('Погрешность Лагранж', abs(function(x) - lx)))


    def f(i, j):
        if abs(i - j) != 1:
            fij = (f(i + 1, j) - f(i, j - 1)) / (val[j][0] - val[i][0])
        else:
            fij = (val[j][1] - val[i][1]) / (val[j][0] - val[i][0])
        return fij

    def mul(k):
        mul = 1
        for i in range(k):
            mul = mul * (x - val[i][0])
        return mul

    def newton_interpolation():
        p = val[0][1]
        for k in range(1, n):
            p = p + f(0,k) * mul(k)
        return p

    p = newton_interpolation()

    print('%-22s %-15.15f' %('Интерполяция Ньютон', p))
    print('%-22s %-15.15f' % ('Погрешность Ньютон', abs(function(x) - p)))

    print('Если хотите продолжить, введите 1, если хотите завершить программу, введите 0')

    flag = int(input())

    if flag == 0:
        break