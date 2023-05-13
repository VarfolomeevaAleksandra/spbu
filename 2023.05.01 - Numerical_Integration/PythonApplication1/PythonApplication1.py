# -*- coding: cp1251 -*-

import math
import random
from numpy import absolute, matmul
from scipy import integrate
from sympy import Interval, Symbol, maximum, sin, cos, exp, log, sqrt

coefficient =4 * [0]
random.seed(version=2)
while coefficient[0] == 0 or coefficient[1] == 0 or coefficient[2] == 0 or coefficient[3] == 0:
    coefficient[0] = random.randint(-20, 20)
    coefficient[1] = random.randint(-20, 20)
    coefficient[2] = random.randint(-20, 20)
    coefficient[3] = random.randint(-20, 20)

def zero_degree(x):
    return coefficient[0] * x**0

def first_degree(x):
    return x * coefficient[1] + coefficient[0]

def second_degree(x):
    return x**2 * coefficient[2] + x * coefficient[1] + coefficient[0]

def third_degree(x):
    return x**3 * coefficient[3] + x**2 * coefficient[2] + x * coefficient[1] + coefficient[0]

def choice(x, f):
    match f:
        case 1:
            return math.sin(x)
        case 2: 
            return math.cos(x)
        case 3:
            return math.log(x)
        case 4:
            return math.exp(x)
        case 5:
            return zero_degree(x)
        case 6:
            return first_degree(x)
        case 7:
            return second_degree(x)
        case 8:
            return third_degree(x)

    return 0

def real_integral(f, a, b):
    match f:
        case 1:
            v, err = integrate.quad(math.sin, a, b)
            return v
        case 2:
            v, err = integrate.quad(math.cos, a, b)
            return v
        case 3:
            v, err = integrate.quad(math.log, a, b)
            return v
        case 4:
            v, err = integrate.quad(math.exp, a, b)
            return v
        case 5:
            v, err = integrate.quad(zero_degree, a, b)
            return v
        case 6:
            v, err = integrate.quad(first_degree, a, b)
            return v
        case 7:
            v, err = integrate.quad(second_degree, a, b)
            return v
        case 8:
            v, err = integrate.quad(third_degree, a, b)
            return v

    return 0

def find_max(a, b, f, n):
    x = Symbol('x')
    I = Interval(a, b)
    match f:
        case 1:
            if n == 1:
                return sqrt(maximum((cos(x))**2, x, I))
            if n == 2:
                return sqrt(maximum((-sin(x))**2, x, I))
            if n == 4:
                return sqrt(maximum((sin(x))**2, x, I))
        case 2:
            if n == 1:
                return sqrt(maximum((-sin(x))**2, x, I))
            if n == 2:
                return sqrt(maximum((-cos(x))**2, x, I))
            if n == 4:
                return sqrt(maximum((cos(x))**2, x, I))
        case 3:
            if n == 1:
                return abs(1/a)
            if n == 2:
                return 1/(b**2)
            if n == 4:
                return -6/(b**4)
        case 4:
            return math.exp(b)
        case 5:
            return 0
        case 6:
            if n == 1:
                return abs(coefficient[1])
            else:
                return 0
        case 7:
            if n == 1:
                return max(abs(2*a*coefficient[2] + coefficient[1]), abs(2*b*coefficient[2] + coefficient[1]))
            if n == 2:
                return 2*abs(coefficient[2])
            if n == 4:
                return 0
        case 8:
            if n == 1:
                return sqrt(maximum((3*x**2*coefficient[3] + 2*x*coefficient[2] + coefficient[1])**2, x, I))
            if n == 2:
                return max(abs(6*a*coefficient[3] + 2*coefficient[2]), abs(6*b*coefficient[3] + 2*coefficient[2]))
            if n == 4:
                return 0
    return 0




def h1(a, b, f, m):
    s = 0
    h = (b - a) / m
    for i in range(1, m):
        s = s + choice(a + i*h, f)
    return s

def h2(a, b, f, m):
    s = 0
    h = (b - a)/ m
    a = a + h/2
    for i in range(m):
        s = s + choice(a + i*h, f)
    return s


def left_rectangle(a, b, f, m, h_1):
    if m == 1:
        g = (b - a) * choice(a, f)
    if m > 1:
        g = (b - a) * (choice(a, f) + h_1) / m
    return g
def right_rectangle(a, b, f, m, h_1):
    if m == 1:
        g = (b - a) * choice(b, f)
    if m > 1:
       g = (b - a) * (choice(b, f) + h_1) / m
    return g
def middle_rectangle(a, b, f, m, h_2):
    if m ==1:
        g = (b - a) * choice((a+b)/2, f)
    if m > 1:
        g = (b - a) * h_2 / m
    return g
def trapezoid(a, b, f, m, h_1):
    if m ==1:
        g = (b - a)/2 *(choice(a, f) + choice(b, f))
    if m > 1:
        g = (b - a) * (choice(a, f) + choice(b, f) + 2*h_1)/2/m
    return g
def simpson(a, b, f, m, h_1, h_2):
    if m == 1:
        g = (b - a) * (choice(a, f) + 4*choice((a+b)/2, f) + choice(b, f)) / 6
    if m > 1:
        g = (b - a) * (choice(a,f) + choice(b, f) + 2 * h_1 + 4 * h_2) / 6 / m
    return g
def three_eight(a, b, f):
    h = (b - a) / 3
    g = (b - a) * (1/8 * choice(a, f) + 3/8 * choice(a + h, f) + 3/8 * choice(a + 2*h, f) + 1/8 * choice(b, f))
    return g

    

def functions():
    print('Выберите функцию:')
    print('1. sin(x)')
    print('2. cos(x)')
    print('3. ln(x)')
    print('4. exp(x)')
    print('5.',coefficient[0])
    print('6.', coefficient[1], '* x + ', coefficient[0])
    print('7.', coefficient[2], '* x^2 +', coefficient[1], '* x +', coefficient[0])
    print('8.', coefficient[3], '* x^3 +', coefficient[2], '* x^2 +', coefficient[1], '* x +', coefficient[0])
    f = int(input())
    return f

def print_f(k):
    match k:
        case 1:
            print('f(x) = sin(x)')
        case 2:
            print('f(x) = cos(x)')
        case 3:
            print('f(x) = ln(x)')
        case 4:
            print('f(x) = exp(x)')
        case 5:
            print('f(x) =', coefficient[0])
        case 6:
            print('f(x) =', coefficient[1], '* x + ', coefficient[0])
        case 7:
            print('f(x) =', coefficient[2], '* x^2 +', coefficient[1], '* x +', coefficient[0])
        case 8:
            print('f(x) =', coefficient[3], '* x^3 +', coefficient[2], '* x^2 +', coefficient[1], '* x +', coefficient[0])

def menu():
    print()
    print('0. Вывод меню')
    print('1. Ввести границы интервала')
    print('2. Выбрать функцию')
    print('3. Приближённое вычисление интеграла по квадратурным формулам')
    print('4. Приближённое вычисление интеграла по составным квадратурным формулам')
    print('5. Выход из программы')
    
    print()
    

def main():
    k = -1
    f = 0
    a = 0
    b = 0
    menu()
    while True:
        k = int(input())

        if k == 3 or k == 4:
            if (f == 0) or (a == 0 and b == 0):
                print('Вы ввели не все необходимые данные')
                continue
        
        if k == 0:
            menu()
            
        if k == 1:
            print('Введите границы интервала')
            print('A:')
            a = float(input())
            print('B:')
            b = float(input())
        if k == 2:
            f = functions()
        if k == 3:
            print('Задание 4.1.Приближённое вычисление интеграла по квадратурным формулам')
            print()
            print('A =', a, 'B =', b)
            print_f(f)
            print('Точное значение интеграла:', "{:.10e}".format(real_integral(f, a, b)))
            print()
            print('Вычисленные значения:')
            print('Левый треугольник:', "{:.10e}".format(left_rectangle(a, b, f, 1, 0)))
            print('Правый треугольник:', "{:.10e}".format(right_rectangle(a, b, f, 1, 0)))
            print('Средний треугольник:', "{:.10e}".format(middle_rectangle(a, b, f, 1, 0)))           
            print('Формула трапеции:', "{:.10e}".format(trapezoid(a, b, f, 1, 0)))
            print('Формула Симпсона:', "{:.10e}".format(simpson(a, b, f, 1, 0, 0)))
            print('Формула 3/8:', "{:.10e}".format(three_eight(a, b, f)))
            print()
            print('Абсолютная фактическая погрешность |J - J(h)|:')
            print('Левый треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - left_rectangle(a, b, f, 1, 0))))
            print('Правый треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - right_rectangle(a, b, f, 1, 0))))
            print('Средний треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - middle_rectangle(a, b, f, 1, 0))))
            print('Формула трапеции:', "{:.10e}".format(abs(real_integral(f, a, b) - trapezoid(a, b, f, 1, 0))))
            print('Формула Симпсона:', "{:.10e}".format(abs(real_integral(f, a, b) - simpson(a, b, f, 1, 0, 0))))
            print('Формула 3/8:', "{:.10e}".format(abs(real_integral(f, a, b) - three_eight(a, b, f))))
            print()
        if k == 4:
            print('Выберите число m промежутков деления [A, B]')
            m = int(input())
            print()
            print('Задание 4.2.Приближённое вычисление интеграла по составным квадратурным формулам')
            print()
            print('A =', a, 'B =', b, 'm =', m)
            print_f(f)
            h_1 = h1(a, b, f, m)
            h_2 = h2(a, b, f, m)
            mean = [0] * 10
            mean[0] = left_rectangle(a, b, f, m, h_1)
            mean[1] = right_rectangle(a, b, f, m, h_1)
            mean[2] = middle_rectangle(a, b, f, m, h_2)
            mean[3] = trapezoid(a, b, f, m, h_1)
            mean[4] = simpson(a, b, f, m, h_1, h_2)
            print()
            print('Точное значение интеграла:', "{:.10e}".format(real_integral(f, a, b)))
            print()
            print('Вычисленные значения:')
            print('Левый треугольник:', "{:.10e}".format(mean[0]))
            print('Правый треугольник:', "{:.10e}".format(mean[1]))
            print('Средний треугольник:', "{:.10e}".format(mean[2]))            
            print('Формула трапеции:', "{:.10e}".format(mean[3]))
            print('Формула Симпсона:', "{:.10e}".format(mean[4]))
            print()
            print('Абсолютная фактическая погрешность |J - J(h)|:')
            print('Левый треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[0])))
            print('Правый треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[1])))
            print('Средний треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[2])))
            print('Формула трапеции:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[3])))
            print('Формула Симпсона:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[4])))
            print()
            print('Теоритическая погрешность:')
            print('Левый треугольник:', "{:.10e}".format((b - a)**2/(2*m) * find_max(a, b, f, 1)))
            print('Правый треугольник:', "{:.10e}".format((b - a)**2/(2*m) * find_max(a, b, f, 1)))
            print('Средний треугольник:', "{:.10e}".format((b - a)**3/(24*m**2) * find_max(a, b, f, 2)))
            print('Формула трапеции:', "{:.10e}".format((b - a)**3/(12*m**2) * find_max(a, b, f, 2)))
            print('Формула Симпсона:', "{:.10e}".format((b - a)**5/(2880*m**4) * find_max(a, b, f, 4)))
            print()
            print('Для увеличения узлов в l раз введите 1, для продолжения введите 0')
            p = int(input())
            if p == 1:
                while True:
                    print()
                    print('Введите l')
                    l = int(input())
                    print()
                    print('A =', a, 'B =', b, 'm =', m, 'l =', l, 'h =', (b - a)/(m*l))
                    print_f(f)
                    h_1 = h1(a, b, f, m*l)
                    h_2 = h2(a, b, f, m*l)
                    mean[5] = left_rectangle(a, b, f, m*l, h_1)
                    mean[6] = right_rectangle(a, b, f, m*l, h_1)
                    mean[7] = middle_rectangle(a, b, f, m*l, h_2)
                    mean[8] = trapezoid(a, b, f, m*l, h_1)
                    mean[9] = simpson(a, b, f, m*l, h_1, h_2)
                    print()
                    
                    print('НЕУТОЧНЕННЫЕ ВЫЧИСЛЕНИЯ ДЛЯ ЧИСЛА РАЗБИЕНИЯ m*l')
                    print()
                    print('Точное значение интеграла:', "{:.10e}".format(real_integral(f, a, b)))
                    print()
                    print('Вычисленные значения:')
                    print('Левый треугольник:', "{:.10e}".format(mean[5]))
                    print('Правый треугольник:', "{:.10e}".format(mean[6]))
                    print('Средний треугольник:', "{:.10e}".format(mean[7]))            
                    print('Формула трапеции:', "{:.10e}".format(mean[8]))
                    print('Формула Симпсона:', "{:.10e}".format(mean[9]))
                    print()
                    print('Абсолютная фактическая погрешность |J - J(h)|:')
                    print('Левый треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[5])))
                    print('Правый треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[6])))
                    print('Средний треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[7])))
                    print('Формула трапеции:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[8])))
                    print('Формула Симпсона:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[9])))
                    print()
                    print('Теоритическая погрешность:')
                    print('Левый треугольник:', "{:.10e}".format((b - a)**2 / (2 * m) * find_max(a, b, f, 1)))
                    print('Правый треугольник:', "{:.10e}".format((b - a)**2 / (2 * m) * find_max(a, b, f, 1)))
                    print('Средний треугольник:', "{:.10e}".format((b - a)**3 / (24 * m**2) * find_max(a, b, f, 2)))
                    print('Формула трапеции:', "{:.10e}".format((b - a)**3 / (12 * m**2) * find_max(a, b, f, 2)))
                    print('Формула Симпсона:', "{:.10e}".format((b - a)**5 / (2880 * m**4) * find_max(a, b, f, 4)))

                    mean[0] = (l * mean[5] - mean[0]) / (l - 1)
                    mean[1] = (l * mean[6] - mean[1]) / (l - 1)
                    mean[2] = (l**2 * mean[7] - mean[2]) / (l**2 - 1)
                    mean[3] = (l**2 * mean[8] - mean[3]) / (l**2 - 1)
                    mean[4] = (l**4 * mean[9] - mean[4]) / (l**4 - 1)

                    print()
                    print('УТОЧНЕННЫЕ ВЫЧИСЛЕНИЯ ДЛЯ ЧИСЛА РАЗБИЕНИЯ m*l')
                    print()
                    print('Точное значение интеграла:', "{:.10e}".format(real_integral(f, a, b)))
                    print()
                    print('Вычисленные значения:')
                    print('Левый треугольник:', "{:.10e}".format(mean[0]))
                    print('Правый треугольник:', "{:.10e}".format(mean[1]))
                    print('Средний треугольник:', "{:.10e}".format(mean[2]))            
                    print('Формула трапеции:', "{:.10e}".format(mean[3]))
                    print('Формула Симпсона:', "{:.10e}".format(mean[4]))
                    print()
                    print('Абсолютная фактическая погрешность |J - J(h)|:')
                    print('Левый треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[0])))
                    print('Правый треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[1])))
                    print('Средний треугольник:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[2])))
                    print('Формула трапеции:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[3])))
                    print('Формула Симпсона:', "{:.10e}".format(abs(real_integral(f, a, b) - mean[4])))
                    print()
                    print('Теоритическая погрешность:')
                    print('Левый треугольник:', "{:.10e}".format((b - a)**2 / (2 * m * l) * find_max(a, b, f, 1)))
                    print('Правый треугольник:', "{:.10e}".format((b - a)**2 / (2 * m * l) * find_max(a, b, f, 1)))
                    print('Средний треугольник:', "{:.10e}".format((b - a)**3 / (24 * (m*l)**2) * find_max(a, b, f, 2)))
                    print('Формула трапеции:', "{:.10e}".format((b - a)**3 / (12 * (m*l)**2) * find_max(a, b, f, 2)))
                    print('Формула Симпсона:', "{:.10e}".format((b - a)**5 / (2880 * (m*l)**4) * find_max(a, b, f, 4)))
                    print()
                    print('Если хотите ввести новое значение l, введите 1')
                    print('Для возврата к вычислению по простым и составным квадратурным формулам введите 0')
                    p = int(input())
                    if p == 0:
                        break
        if k == 5:
            break
        
                
                

main()