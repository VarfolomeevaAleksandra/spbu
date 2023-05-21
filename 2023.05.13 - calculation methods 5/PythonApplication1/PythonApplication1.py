# -*- coding: cp1251 -*-

import random
import numpy as np
import math
from scipy.integrate import quad
from sympy import sin, sqrt, exp, cos
from scipy.linalg import solve


def function_1(x, i, p, k, t):
    r = p*sin(x) + k * x**i*sqrt(x) + t*sin(x)*sqrt(x)
    return r

def integral_1(a, b):
    integral, e = quad(function_1, a, b, args = (0, 0, 0, 1))
    return integral

def function_gauss(x, p, k, t):
    r = p*sin(x)/x + k*1 + t*sin(x)/x
    return r

def integral_gauss(a, b):
    integral, e = quad(function_gauss, a, b, args = (0, 0, 1))
    return integral

def function_meler(x, p, k, t):
    r = p* cos(x) +k * 1/(sqrt(1 - x**2)) + t* 1/(sqrt(1 - x**2)) * cos(x)
    return r

def integral_meler(a,b):
    integral, e = quad(function_meler, a, b, args = (0, 0, 1))
    return integral

def coefficient(N):
    random.seed(version=2) 
    coef = [0]*N
    c = 0
    for i in range(N):
        while c == 0:
           c = random.randint(-100, 100)
        coef[i] = c
        c = 0
    return coef

def function_polynom(x, N, coef, k, t, p, h):
    return t * sum(coef[i] * x**i for i in range(len(coef))) + p * sqrt(x) * x**k + h * sum(coef[i] * x**(i) for i in range(len(coef))) * sqrt(x)

def integral_polynom(a, b, N, coef):
    integral, e = quad(function_polynom, a, b, args = (N, coef, 0, 0, 0, 1))
    return integral

def function_monomial(x, N, c, k, t, p, h):
    return t * c * x**N + p * sqrt(x) * x**k + h * c * x**N * sqrt(x)

def integral_monomial(a, b, N, c, f):
    if f == 1:
        integral, e = quad(function_monomial, a, b, args = (N, c, 0, 0, 0, 1))
    if f == 2:
        integral, e = quad(function_monomial, a, b, args = (N, c, 0, 1, 0, 0))
    return integral

def full_nodes(a, b, N):
    nodes = []
    print('Для ввода случайных узлов нажмите 1, для ввода узлов с клавиатуры нажмите 0')
    flag = int(input())
    if flag == 1:
        random.seed(version=2)
        h = abs(b-a) / N
        for i in range(N):
            nodes.append(random.uniform(a + i * h, a + (i + 1) * h))
    if flag == 0:
        for i in range(N):
            nodes.append(float(input()))
    return nodes

def calculation_moments(a, b, N):
    moments = []
    for i in range(2*N):
        g,e = quad(function_1, a, b, args = (i, 0, 1, 0))
        moments.append(g)
    return moments

def calculation_moments_polynom(a, b, N, c, function):
    moments = []
    for i in range(2*N):
        g,e = quad(function, a, b, args = (N, c, i, 0, 1, 0))
        moments.append(g)
    return moments

def solve_system_1(N, nodes, moments):
    L = np.empty((N, N))
    for i in range(N):
        for j in range(N):
            L[i][j] = nodes[j]**i
    cut_moments = []
    for i in range(N):
        cut_moments.append(moments[i])
    R = np.array(cut_moments)
    A = solve(L, R)
    return A

def solve_system_2(N, moments):
    L = np.empty((N, N))
    for i in range(N):
        for j in range(N):
            L[i][j] = float(moments[i+j])
    R = np.empty((N, 1))
    for i in range(N):
        R[i] = -float(moments[N+i])
    a = solve(L, R)
    return a

def solve_equation(N, moments):
    a = solve_system_2(N, moments)
    print('Коэффициенты ортогонального многочлена:')
    for i in range(len(a)):
        print('x^',i, ":", a[i])
    a_r = np.empty((N + 1))
    a_r[0] = 1
    for i in range(N):
        a_r[N - i] = a[i][0]
    roots = np.roots(a_r)
    return roots

def P_N(N, x):
    P = 0
    if N==1: return x
    if N==0: return 1
    if N!= 0 and N!= 1:
        P = ((2*N - 1) * P_N(N-1, x) * x - (N-1) * P_N(N-2, x))/N
    return P

def check_sign(N, a, b):
    if P_N(N, a) * P_N(N, b) < 0: return True
    else: return False

def root(N):
    a = -1
    b = 1
    roots = []
    pair = []
    h = abs(b - a) / 1000
    j = a
    while j<= b:
        if check_sign(N, j, j+h):
            pair.append(j)
            pair.append(j + h)
        j = j + h
    for i in range(len(pair) // 2):
        roots.append(bisection(N, pair[2 * i], pair[2*i + 1]))
    return roots

def bisection(N, a, b):
    a_i = a
    b_i = b
    c_i = 0
    k = 0
    e = 0.000000000001
    while b_i - a_i > 2 * e:
        c_i = (a_i + b_i) / 2
        if (P_N(N, a_i)) * (P_N(N, c_i)) <= 0:
            b_i = c_i
        else:
            a_i = c_i
        k = k + 1
    root = (a_i + b_i)/2
    return root

def C_K(N, roots):
    C = []
    for i in range(len(roots)):
        C.append(2*(1 - roots[i]**2)/(N**2 * P_N(N-1, roots[i])**2))
    return C

def A_K(a, b, C):
    A = []
    for i in range(len(C)):
        A.append(((b-a)/2) * C[i])
    return A

def x_K(a,b,roots):
    x = []
    for i in range(len(roots)):
        x.append(((b - a)/2 )* roots[i] + (b+a)/2)
    return x

def nodes_Meller(N):
    nodes = []
    for i in range(N):
        nodes.append(cos(3.14*(2*i - 1)/(2*N)))
    return nodes

def coef_Meller(N):
    coef = []
    for i in range(N):
        coef.append(3.14/N)
    return coef
   

def main():
    a = 0
    b = 0
    N = 0
    
    
    k = 0
    #5.1------------------------------------------
    while True:
        print()
        print('ВЫЧИСЛЕНИЕ ИНТЕГРАЛА С ПОМОЩЬЮ ИКФ')
        moments = []
        print()
        print('Введите границы интервала:')
        print()
        print('a:')
        a = float(input())
        print()
        print('b:')
        b = float(input())
        print()
        print('Введите количество узлов N:')
        N = int(input())
        nodes = []
        nodes.extend(list(full_nodes(a, b, N)))
        print()
        print('Узлы:')
        print()
        for j in range(N):
            print(j, nodes[j])
        print()
        print('Первые N моментов:')
        moments.extend(list(calculation_moments(a, b, N)))
        print()
        for j in range(N):
            print(j, moments[j])
        A = solve_system_1(N, nodes, moments)
        print()
        print('Найденные коэффициенты:')
        print()
        for i in range(len(A)):
            print(i, A[i])
        solve = 0
        for i in range(N):
            solve = solve + A[i] * function_1(nodes[i],0,1,0,0)
            print()
        print('Приближенное значение J_икф =', solve)
        print('Точное значение J =', integral_1(a, b))
        print('|J - J_икф| =', abs(solve - integral_1(a, b)))
        moments.clear()
        v = 0
        print('Если вы хотите провести проверку на многочлене, нажмите 1. Если нет, нажмите 0')
        v = int(input())
        if v == 1:
            coef = []
            coef.extend(list(coefficient(N)))

            print()
            print('Проверка проводится для следующего многочлена:')
            for i in range(N - 1):
                print(coef[i], '*', 'x^', N - 1 - i, '+', end = ' ')
            print(coef[N - 1])

            print()
            print('Узлы:')
            print()
            for j in range(N):
                print(j, nodes[j])
            print('Первые N моментов:')
            moments.extend(list(calculation_moments_polynom(a, b, N, coef, function_polynom)))
            print()
            for j in range(N):
                print(j, moments[j])
            A = solve_system_1(N, nodes, moments)
            print()
            print('Найденные коэффициенты:')
            print()
            for i in range(len(A)):
                print(i, A[i])
            solve = 0
            for i in range(N):
                solve = solve + A[i] * function_polynom(nodes[i], N, coef,0,1,0,0)
                print()
            print('Приближенное значение J_икф =', solve)
            print('Точное значение J =', integral_polynom(a, b, N, coef))
            print('|J - J_икф| =', abs(solve - integral_polynom(a, b, N, coef)))
            moments.clear()
        nodes.clear()
        print('Если вы хотите ввести другие интервал интегрирования и количество узлов нажмите 1, если нет, нажмите 0')
        k = int(input())
        if k == 0:
            break
    while True:
        print('ВЫЧИСЛЕНИЕ ИНТЕГРАЛА С ПОМОЩЬЮ КФНАСТ:')
        print()
        print('Введите границы интервала:')
        print()
        print('a:')
        a = float(input())
        print()
        print('b:')
        b = float(input())
        print('Введите количество узлов N:')
        N = int(input())
        print()
        print('Первые 2N - 1 моментов:')
        moments.extend(list(calculation_moments(a, b, N)))
        print()
        for j in range(2*N):
            print(j, moments[j])
        #РЕШЕНИЕ 2 СИСТЕМЫ
        x = solve_equation(N, moments)
        print()
        print('Найденные узлы:')
        print()
        for i in range(len(x)):
            print(i, x[i])
        A2 = solve_system_1(N, x, moments)
        print()
        print('Найденные коэффициенты:')
        print()
        for i in range(len(A2)):
            print(i, A2[i])
        solve = 0
        for i in range(N):
            solve = solve + A2[i] * function_1(x[i],0,1,0,0)
        print()
        print('Приближенное значение J_кфнаст =', solve)
        print('Точное значение J = ', integral_1(a, b))
        print('|J - J_кфнаст| =', abs(solve - integral_1(a, b)))
        moments.clear()
        v = 0
        print('Если вы хотите провести проверку на одночлене, нажмите 1. Если нет, нажмите 0')
        v = int(input())
        if v == 1:
            random.seed(version=2)
            c = random.randint(-100, 100)

            print('Проверка проводится для одночлена:')
            print(c, '*', 'x^', 2*N - 1)
            print()
            print('Первые 2N - 1 моментов:')
            moments.extend(list(calculation_moments_polynom(a, b, 2*N, c, function_monomial)))
            print()
            for j in range(2*N):
                print(j, moments[j])
            #РЕШЕНИЕ 2 СИСТЕМЫ
            x = solve_equation(N, moments)
            print()
            print('Найденные узлы:')
            print()
            for i in range(len(x)):
                print(i, x[i])
            A2 = solve_system_1(N, x, moments)
            print()
            print('Найденные коэффициенты:')
            print()
            for i in range(len(A2)):
                print(i, A2[i])
            solve = 0
            for i in range(N):
                solve = solve + A2[i] * function_monomial(x[i], 2*N - 1, c,0,1,0,0)
            print()
            print('Приближенное значение J_кфнаст =', solve)
            print('Точное значение J = ', integral_monomial(a, b, 2*N - 1, c, 1))
            print('|J - J_кфнаст| =', abs(solve - integral_monomial(a, b, 2*N - 1, c, 1)))
            moments.clear()
        print('Если вы хотите ввести другие интервал интегрирования и количество узлов нажмите 1, если нет, нажмите 0')
        k = int(input())
        if k == 0:
            break

    #5.2-----------------------------------------

    roots  = []
    C = []
    A3 = []
    x1 = []
    print()
    print('ВЫЧИСЛЕНИЕ ИНТЕГРАЛА С ПОМОЩЬЮ КФ ГАУССА')
    while True:
        print('Введите границы интервала:')
        print()
        print('a:')
        a = float(input())
        print()
        print('b:')
        b = float(input())
        print('Введите количество узлов N:')
        N = int(input())
        for i in range(2,N + 1):
            print('N =', i)
            roots.clear()
            C.clear()
            A3.clear()
            x1.clear()
            roots.extend(list(root(i)))
            C.extend(list(C_K(i, roots)))
            A3.extend(list(A_K(a, b, C)))
            x1.extend(x_K(a, b, roots))
            print()
            print('%-60s %-60s' % ('Для изначальной КФ Гаусса', 'Для подобной КФ Гаусса'))
            for j in range(len(roots)):
                print('%-5s %-18.16f %-14s %-22.16f %-5s %-18.16f %-14s %-18.16f'%('Узел:', roots[j], 'Коэффициент:', A3[j], 'Узел:', x1[j], 'Коэффициент:', C[j]))
            print()
        print('x1')
        for i in range(len(x1)):
            print(i, x1[i])
        print('A3')
        for i in range(len(A3)):
            print(i, A3[i])
        solve = 0
        for i in range(len(A3)):
            solve = solve + A3[i] * function_gauss(x1[i], 1, 0, 0)
        print('При N =', N)
        print('Приближенное значение J_гаусс =', solve)
        print('Точное значение J = ', integral_gauss(a, b))
        print('|J - J_гаусс| =', abs(solve - integral_gauss(a, b)))
        v = 0
        print('Если вы хотите провести проверку на одночлене, нажмите 1. Если нет, нажмите 0')
        v = int(input())
        if v == 1:
            random.seed(version=2)
            c = random.randint(-100, 100)

            print()
            print('Проверка проводится для одночлена:')
            print(c, '*', 'x^', 2*N - 1)
            for i in range(2,N + 1):
                print('N =', i)
                roots.clear()
                C.clear()
                A3.clear()
                x1.clear()
                roots.extend(list(root(i)))
                C.extend(list(C_K(i, roots)))
                A3.extend(list(A_K(a, b, C)))
                x1.extend(x_K(a, b, roots))
                print()
                print('%-60s %-60s' % ('Для изначальной КФ Гаусса', 'Для подобной КФ Гаусса'))
                for j in range(len(roots)):
                    print('%-5s %-18.16f %-14s %-22.16f %-5s %-18.16f %-14s %-18.16f'%('Узел:', roots[j], 'Коэффициент:', A3[j], 'Узел:', x1[j], 'Коэффициент:', C[j]))
                print()
            solve = 0
            for i in range(len(A3)):
                solve = solve + A3[i] * function_monomial(x1[i],2*N - 1, c, 0, 1,0,0)
            print('При N =', N)
            print('Приближенное значение J_гаусс =', solve)
            print('Точное значение J = ', integral_monomial(a, b, 2*N - 1, c, 2))
            print('|J - J_гаусс| =', abs(solve - integral_monomial(a, b, 2*N - 1, c, 2)))
        print('Если вы хотите ввести другие интервал интегрирования и количество узлов нажмите 1, если нет, нажмите 0')
        k = int(input())
        if k == 0:
            break
    print('ВЫЧИСЛЕНИЕ ИНТЕГРАЛА С ПОМОЩЬЮ КФ МИЛЕРА')
    while True:
        print('Введите границы интервала:')
        print()
        print('a:')
        a = float(input())
        print()
        print('b:')
        b = float(input())
        print('Введите количества узлов N1, N2, N3')
        print('N1:')
        N1 = int(input())
        print('N2:')
        N2 = int(input())
        print('N3:')
        N3 = int(input())
        nodes_M = []
        nodes_M.extend(nodes_Meller(N1))
        A4 = []
        A4.extend(coef_Meller(N1))
        print()
        print('Узлы КФ Меллера при количестве узлов =', N1)
        for i in range(N1):
            print(i, nodes_M[i])
        print()
        print('Коэффициенты КФ Меллера при количестве узлов =', N1)
        for i in range(N1):
            print(i, A4[i])
        solve = 0
        for i in range(len(A4)):
            solve = solve + A4[i] * function_meler(nodes_M[i],1,0,0)
        print('Приближенное значение J_мелер =', solve)
        print('Точное значение J = ', integral_meler(a, b))
        print('|J - J_мелер| =', abs(solve - integral_meler(a, b)))
        nodes_M.clear()
        A4.clear()
        nodes_M.extend(nodes_Meller(N2))
        A4.extend(coef_Meller(N2))
        print()
        print('Узлы КФ Меллера при количестве узлов =', N2)
        for i in range(N2):
            print(i, nodes_M[i])
        print()
        print('Коэффициенты КФ Меллера при количестве узлов =', N2)
        for i in range(N2):
            print(i, A4[i])
        solve = 0
        for i in range(len(A4)):
            solve = solve + A4[i] * function_meler(nodes_M[i],1,0,0)
        print('Приближенное значение J_мелер =', solve)
        print('Точное значение J = ', integral_meler(a, b))
        print('|J - J_мелер| =', abs(solve - integral_meler(a, b)))
        nodes_M.clear()
        A4.clear()
        nodes_M.extend(nodes_Meller(N3))
        A4.extend(coef_Meller(N3))
        print()
        print('Узлы КФ Меллера при количестве узлов =', N3)
        for i in range(N3):
            print(i, nodes_M[i])
        print()
        print('Коэффициенты КФ Меллера при количестве узлов =', N3)
        for i in range(N3):
            print(i, A4[i])
        solve = 0
        for i in range(len(A4)):
            solve = solve + A4[i] * function_meler(nodes_M[i],1,0,0)
        print('Приближенное значение J_мелер =', solve)
        print('Точное значение J = ', integral_meler(a, b))
        print('|J - J_мелер| =', abs(solve - integral_meler(a, b)))
        nodes_M.clear()
        A4.clear()
        print('Если вы хотите ввести другие интервал интегрирования и количество узлов нажмите 1, если нет, нажмите 0')
        k = int(input())
        if k == 0:
            break

    #5.3------------------------------------------------------

    print('ВЫЧИСЛЕНИЕ ИНТЕГРАЛА С ПОМОЩЬЮ СКФ ГАУССА')
    while True:
        print('Введите границы интервала:')
        print()
        print('a:')
        a = float(input())
        print()
        print('b:')
        b = float(input())
        print('Введите количество узлов N')
        Ng = int(input())
        print('Введите число разбиений m')
        m = int(input())
        h = (b - a) / m
        roots  = []
        roots.extend(list(root(Ng)))
        C = []
        C.extend(list(C_K(Ng, roots)))
        solve = 0
        f = 0
        for i in range(Ng):
            for j in  range(m):
                f = f + function_1(h/2 * roots[i] + (a + j*h + a + (j+1)*h)/2, 0, 1, 0, 0)
            solve = solve + f*C[i]
            f = 0
        solve = h/2 * solve
        print('Приближенное значение J_скф_гаусса =', solve)
        print('Точное значение J = ', integral_1(a, b))
        print('|J - J_скф_гаусса| =', abs(solve - integral_1(a, b)))
        print('Если вы хотите ввести другие интервал интегрирования и количество узлов нажмите 1, если нет, нажмите 0')
        k = int(input())
        if k == 0:
            break        
                


main()


