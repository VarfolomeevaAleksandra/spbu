# -*- coding: cp1251 -*-

import random
import math


def function(x):
    f = math.sin(2*x)
    return f




def table(a, m, val, h):
    k = 0
    while k < m:
        a_1 = a + h * k
        b_1 = a + h * (k + 1)
        x0 = random.uniform(a_1, b_1)
        f = function(x0)
        val[k][0] = x0
        val[k][1] = f
        val[k][2] = 0
        k = k + 1
    return val



def print_table(val):        
    print('%-3s %-12s %-12s' %('№', 'x', 'f(x)'))
    for i in range(len(val)):
        print('%-3d %-12.10f %-12.10f' % (i, val[i][0], val[i][1]))


def swap_x_fx(x, l):
    c = 0
    for i in range(len(l)):
        c = l[i][0]
        l[i][0] = l[i][1]
        l[i][1] = c
        l[i][2] = abs(x - l[i][0])
    return l



    

    
    

def change_x(another_x, l):
    for i in range(len(l)):
        l[i][2] = abs(another_x - l[i][0])

def sort_col(i):
    return i[2]

def sort(array):
    for i in range(len(array)):
        for j in range(0, len(array) - i - 1):
            if array[j][2] > array[j + 1][2]:
                temp = array[j]
                array[j] = array[j+1]
                array[j+1] = temp
    



def f_1(n, val):
    ak = []
    w = 1
    a = 0
    ak.append(val[0][1])
    for k in range(1, n + 1):
        for i in range(k + 1):
            for j in range(k + 1):
                if i != j:
                    w = w * (val[i][0] - val[j][0])
            a = a + val[i][1] / w
            w = 1
        ak.append(a)
        a = 0
    return ak

def mul(k, x, val):
    mul = 1
    for i in range(k):
        mul = mul * (x - val[i][0])
    return mul



def newton_interpolation(coefficient, x, n, val):
    p = coefficient[0]
    for k in range(1, n):
        p = p + coefficient[k] * mul(k, x, val)
    return p




#ОПРЕДЕЛЕНИЕ ПРОМЕЖУТКОВ МОНОТОННОСТИ


def check_monotone(a, b):
    if a >= b: 
        return 1
    else:
        return 0


def monotone(type_of_return, n_1, val, d, m, b):
    i1 = 0
    i2 = n_1 + 1
    val1 = [0.0] * len(val)
    for j in range(len(val1)):
        val1[j] = [0.0] * len(val[j])
    for i in range(len(val)):
        val1[i] = list(val[i])
    intervals = []
    values = []
    s1 = val[i1][0]
    s2 = 0
    new_coefficient = []
    s = 0
    h = abs(val[0][0] - val[-1][0]) / (d)
    x0 = val[i1][0] + h
    new_coefficient.extend(f_1(n_1, val1))
    values.append(newton_interpolation(new_coefficient, s1, n_1, val1))
    flag1 = check_monotone(newton_interpolation(new_coefficient,x0 - h,n_1, val1), newton_interpolation(new_coefficient, x0, n_1, val1))
    while s < m - n_1 - 2:
        flag2 = check_monotone(newton_interpolation(new_coefficient,x0,n_1, val1), newton_interpolation(new_coefficient,x0 + h,n_1, val1))
        if abs(val[i1][0] - x0) < abs(x0 - val[i2 + 1][0]):
            if  flag1 != flag2:                       
                s2 = x0
                intervals.append(s1)
                intervals.append(s2)
                values.append(newton_interpolation(new_coefficient, s2, n_1, val1))
                values.append(values[-1])
                s1 = s2
                s2 = 0
        else: 
            if  flag1 != flag2:                       
                s2 = x0
                intervals.append(s1)
                intervals.append(s2)
                values.append(newton_interpolation(new_coefficient, s2, n_1, val1))
                values.append(values[-1])
                s1 = s2
                s2 = 0
            s = s + 1
            change_x(x0, val1)
            sort(val1)
            new_coefficient.clear()
            new_coefficient.extend(f_1(n_1, val1))
            i1 = i1 + 1
            i2 = i2 + 1
        x0 = x0 + h
        flag1 = flag2
    while s >= m - n_1 - 2 and x0 + h < b:
        flag2 = check_monotone(newton_interpolation(new_coefficient,x0,n_1, val1), newton_interpolation(new_coefficient,x0 + h,n_1, val1))
        if  flag1 != flag2:     
            s2 = x0
            intervals.append(s1)
            intervals.append(s2)
            values.append(newton_interpolation(new_coefficient, s2, n_1, val1))
            values.append(values[-1])
            s1 = s2
            s2 = 0
        s = s + 1
        x0 = x0 + h
        flag1 = flag2 
    if (len(intervals)) == 0:
        intervals.append(val[0][0])
        intervals.append(x0)
        values.append(newton_interpolation(new_coefficient,x0,n_1, val1))
    else:
        values.append(newton_interpolation(new_coefficient,x0,n_1, val1))
        intervals.append(intervals[-1])
        intervals.append(x0)
    if type_of_return == 0:
        return intervals
    if type_of_return == 1:
        return values
    
            

def definition(intervals_of_monotonicity, monotonicity, values_monotonicity, values):
    j = 0
    for i in range(0, len(intervals_of_monotonicity), 2):
        monotonicity[j][0] = intervals_of_monotonicity[i]
        monotonicity[j][1] = intervals_of_monotonicity[i + 1]
        values_monotonicity[j][0] = values[i]
        values_monotonicity[j][1] = values[i + 1]
        j = j + 1




    #-----------------------------------------------

#ОБРАТНОЕ ИНТЕРПОЛИРОВАНИЕ, ЗАДАНИЕ 3.1, 1 СПОСОБ



def check_interval_of_monotonicity(j, values_monotonicity, f):
    if (f <= values_monotonicity[j][0] and f >= values_monotonicity[j][1]) or (f >= values_monotonicity[j][0] and f <= values_monotonicity[j][1]):
        return 1
    else:
        return 0

def list_monotonicity(i, l, monotonicity):
    l0 = []
    for j in range(len(l)):
        if l[j][0] < monotonicity[i][1] and l[j][0] > monotonicity[i][0]:
            l0.append(list(l[j]))

    return l0

def degree(count, n_1):
    if n_1 > count - 1:
        return count - 1
    else:
        return n_1

def interpolation_with_monotonicity(monotonicity, val, f, n_1, values_monotonicity):
    list_monoton = []
    coeff = []
    list_answer = []
    for i in range(len(monotonicity)):
        if check_interval_of_monotonicity(i, values_monotonicity, f) == 1:
            list_monoton = list_monotonicity(i, val, monotonicity)
            list_monoton = swap_x_fx(f, list_monoton)
            sort(list_monoton)
            n0 = degree(len(list_monoton), n_1)
            coeff.extend(f_1(n0, list_monoton))
            p = newton_interpolation(coeff, f, n0, list_monoton)
            list_answer.append(p)
            coeff.clear()
            list_monoton.clear()
    return list_answer




    #-------------------------------------------------------
    
#ОБРАТНОЕ ИНТЕРПОЛИРОВАНИЕ, ЗАДАНИЕ 3.1, 2 СПОСОБ

def minimum(l, n):
    x = 0
    x = l[0][0]
    for i in range(n + 1):
        x = min(x, l[i][0])
    return x

def copy_list(l):
    l_copy = []
    for i in range(len(l)):
        l_copy.append(list(l[i]))
    return l_copy


def bisection(a, b, small_list, n, e, f):
    c = (a + b) / 2
    coeff = []
    k = 0 
    n0 = 0
    if len(small_list) == n:
        coeff.extend(f_1(n - 1, small_list))
        while b - a > 2 * e:
            c = (a + b) / 2
            if (newton_interpolation(coeff, a, n - 1, small_list) - f) * (newton_interpolation(coeff, c, n - 1, small_list) - f) <= 0:
                b = c
            else:
                a = c
            k = k + 1
    else:
        small_list_a = []
        small_list_a = copy_list(small_list)
        change_x(a, small_list_a)
        sort(small_list_a)

        small_list_c = []
        small_list_c = copy_list(small_list)
        change_x(c, small_list_c)
        sort(small_list_c)

        n0 = degree(len(small_list), n)

        while  minimum(small_list_a, n0) != minimum(small_list_c, n0) and (b - a) / 2 > 2 * e:
            
            c = (a + b) / 2
            if (newton_interpolation(f_1(n0, small_list_a), a, n0 - 1, small_list_a) - f) * (newton_interpolation(f_1(n0, small_list_c), c, n0 - 1, small_list_c) - f) <= 0:
                b = c
            else:
                a = c
            change_x(a, small_list_a)
            sort(small_list_a)
            change_x(c, small_list_c)
            sort(small_list_c)
            k = k + 1
        coeff = f_1(n0, small_list_a)
        while b - a > 2 * e:
            c = (a + b) / 2
            if (newton_interpolation(coeff, a, n0, small_list_a) - f) * (newton_interpolation(coeff, c, n0, small_list_a) - f) <= 0:
                b = c
            else:
                a = c
            k = k + 1
    c = (a + b) / 2
    return c



def solution_of_ecuation(monotonicity, val, n, values_monotonicity, f, e):
    list_bisection = []
    list_answer = []
    for i in range(len(monotonicity)):
        if check_interval_of_monotonicity(i, values_monotonicity, f) == 1:
            list_bisection = list_monotonicity(i, val, monotonicity)
            p = bisection(list_bisection[0][0], list_bisection[-1][0], list_bisection, n, e, f)
            list_answer.append(p)
            list_bisection.clear()
            
    return list_answer


    #--------------------------------------------------------------


#ЧИСЛЕННОЕ ДИФФЕРЕНЦИРОВАНИЕ, ЗАДАНИЕ 3.2

def function2(x):
    f = math.exp(3 * x)
    return f

def table_evenly(m2, a, h, val):
    k = 0
    while k < m2:
        a_1 = a + h * k
        x0 = a_1
        f = function2(x0)
        val[k][0] = x0
        val[k][1] = f
        k = k + 1
    return val

def first_diff_left(val, h):
    d = ((-3) * val[0][1] + 4 * val[1][1] - val[2][1]) / (2 * h)
    return d

def first_diff_middle(val, h, i):
    d = (val[i + 1][1] - val[i - 1][1]) / (2 * h)
    return d

def first_diff_right(val, h):
    d = (3 * val[-1][1] - 4 * val[-2][1] + val[-3][1]) / (2 * h)
    return d

def second_diff_left(val, h):
    d = (2 * val[0][1] - 5 * val[1][1] + 4 * val[2][1] - val[3][1]) / (h**2)
    return d

def second_diff_middle(val, h, i):
    d = (val[i + 1][1] - 2 * val[i][1] + val[i - 1][1]) / (h**2)
    return d

def second_diff_right(val, h):
    d = (2 * val[-1][1] - 5 * val[-2][1] + 4 * val[-3][1] - val[-4][1]) / (h**2)
    return d

def check_first_diff(i, val):
    d = 3 * math.exp(3 * val[i][0])
    return d

def check_second_diff(i, val):
    d = 9 * math.exp(3 * val[i][0])
    return d


def main():
    print('Введите количество узлов')
    m = int(input())
        
    print ('Введите границы интервала')
    a = float(input())
    b = float(input())
    
    h = abs(b - a) / (m)
    
    val = [0.0] * m
    for i in range(m):
        val[i] = [0.0] * 3

    val = table(a, m, val, h)
    print_table(val)

    

    while True:
        print('Введите степень многочлена для определения промежутков монотонности')
        n_1 = int(input())
        if n_1 > m - 1:
            print('Недопустимая степень')
        else:
            break

    
    print('Введите количество отрезков для определения промежутков мнотонности')
    d = int(input())

    intervals_of_monotonicity = []
    intervals_of_monotonicity = monotone(0, n_1, val, d, m, b)
    
    values = []
    values = monotone(1, n_1, val, d, m, b)
    
    
    count = 0
    for i in range(len(intervals_of_monotonicity) - 1): 
        if intervals_of_monotonicity[i] != intervals_of_monotonicity[i + 1]:
            print('%-2s %-10.8f %-2s %-10.8f %-2s' % ('[', intervals_of_monotonicity[i],',', intervals_of_monotonicity[i + 1], ']'))
            count = count + 1
    print('Количество промежутков монотонности - ', count)
    
    
    
    monotonicity = [0.0] * count
    for i in range(count):
        monotonicity[i] = [0.0] * 2
    values_monotonicity = [0.0] * count
    for i in range(count):
        values_monotonicity[i] = [0.0] * 2

    definition(intervals_of_monotonicity, monotonicity, values_monotonicity, values)

    while True:
        print()
        print('Введите значение F')
        
        f = float(input())
        
        print('Введите точность е')
        
        e = float(input())

        print('Введите степень многочлена')
        print('Если степень многочлена превышает количество узлов в промежутке монотонности, то будет построен многочлен максимально возможной степени')

        n = int(input())

        answer_1 = []
        answer_1 = interpolation_with_monotonicity(monotonicity, val, f, n, values_monotonicity)
        print('Задание 3.1, способ 1')
        print('Найдено', len(answer_1), 'значений х')
        for i in range(len(answer_1)):
            print(i + 1,'X =' ,answer_1[i], '|f(X) - F| =', abs(function(answer_1[i]) - f))

        print()
        print('Задание 3.1, способ 2')
        answer_2 = []
        answer_2 = solution_of_ecuation(monotonicity, val, n, values_monotonicity, f, e)
        print('Найдено', len(answer_2), 'значений х')
        for i in range(len(answer_2)):
            print(i + 1,'X =', answer_2[i], '|f(X) - F| =', abs(function(answer_2[i]) - f))

        print('Для ввода других параметров F, n и e введите 1, для перехода к заданию 2 введите 0')
        flag = int(input())
        if flag == 0:
            break

    while True:
        print('Введите начало отрезка а')
        a2 = float(input())
        print('Введите h')
        h2 = float(input())
        print('Введите количество точек m + 1')
        m2 = int(input())

        val2 = [0.0] * m2
        for i in range(m2):
            val2[i] = [0.0] * 6

        val2 = table_evenly(m2, a2, h2, val2)
        print_table(val2)

        for i in range(len(val2)):
            if i == 0:
                val2[i][2] = first_diff_left(val2, h2)
                val2[i][3] = abs(check_first_diff(i, val2) - first_diff_left(val2, h2))
                val2[i][4] = second_diff_left(val2, h2)
                val2[i][5] = abs(check_second_diff(i, val2) - second_diff_left(val2, h2))
            if i == len(val2) - 1:
                val2[i][2] = first_diff_right(val2, h2)
                val2[i][3] = abs(check_first_diff(i, val2) - first_diff_right(val2, h2))
                val2[i][4] = second_diff_right(val2, h2)
                val2[i][5] = abs(check_second_diff(i, val2) - second_diff_right(val2, h2))
            if i != 0 and i != len(val2) - 1:
                val2[i][2] = first_diff_middle(val2, h2, i)
                val2[i][3] = abs(check_first_diff(i, val2) - first_diff_middle(val2, h2, i))
                val2[i][4] = second_diff_middle(val2, h2, i)
                val2[i][5] = abs(check_second_diff(i, val2) - second_diff_middle(val2, h2, i))

        print('%-3s %-20s %-20s %-20s %-26s %-20s %-20s' % ("№",'x_i','f(x_i)',"f'(x_i)чд","|f'(x_i)чд - f'(x_i)т|","f''(x_i)чд","|f''(x_i)чд - f''(x_i)т|"))
        for i in range(len(val2)):
            print('%-3d %-20.16f %-20.16f %-20.16f %-26.16f %-20.16f %-20.16f' % (i, val2[i][0], val2[i][1], val2[i][2], val2[i][3], val2[i][4], val2[i][5]))

        print('Для ввода новых параметров введите 1, для выхода из программы введите 0')
        flag2 = int(input())
        if flag2 == 0:
            break


main()




