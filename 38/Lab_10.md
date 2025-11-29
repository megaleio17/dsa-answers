# Лабораторная работа: Динамическое программирование
# Бахал И.А., ИУ10-38

"""
Цель работы:
Получение практических навыков применения методов динамического программирования.

Формулировка задач:
1. Числа Фибоначчи: вычислить первые n чисел последовательности Фибоначчи.
2. Задача о рюкзаке: выбрать предметы с максимальной ценностью при ограничении по весу.
3. Наибольшая возрастающая подпоследовательность (LIS): найти максимальную возрастающую подпоследовательность.
4. Наибольшая общая подпоследовательность (LCS): найти максимальную последовательность символов, общую для двух строк.
5. Минимальное расстояние Левенштейна: найти минимальное число операций для превращения одной строки в другую.
6. Минимальная сумма пути в матрице: найти путь с минимальной суммой чисел от верхнего левого до нижнего правого угла.
"""

# =============================
# Числа Фибоначчи
# =============================

def fib_recursive(n):
    if n <= 1:
        return n
    return fib_recursive(n-1) + fib_recursive(n-2)

def fib_memo(n, memo={}):
    if n in memo:
        return memo[n]
    if n <= 1:
        memo[n] = n
    else:
        memo[n] = fib_memo(n-1, memo) + fib_memo(n-2, memo)
    return memo[n]

def fib_iterative(n):
    if n == 0: return [0]
    seq = [0, 1]
    for i in range(2, n+1):
        seq.append(seq[-1] + seq[-2])
    return seq

n = 10
fib_rec = [fib_recursive(i) for i in range(n+1)]
fib_mem = [fib_memo(i) for i in range(n+1)]
fib_it = fib_iterative(n)

# =============================
# Задача о рюкзаке
# =============================

def knapsack(values, weights, W):
    n = len(values)
    dp = [[0]*(W+1) for _ in range(n+1)]
    for i in range(1, n+1):
        for w in range(W+1):
            if weights[i-1] <= w:
                dp[i][w] = max(dp[i-1][w], values[i-1] + dp[i-1][w - weights[i-1]])
            else:
                dp[i][w] = dp[i-1][w]
    w = W
    items = []
    for i in range(n, 0, -1):
        if dp[i][w] != dp[i-1][w]:
            items.append(i-1)
            w -= weights[i-1]
    items.reverse()
    return dp[n][W], items

values = [3, 4, 2]
weights = [2, 3, 1]
W = 5
max_val, chosen_items = knapsack(values, weights, W)

# =============================
# Наибольшая возрастающая подпоследовательность (LIS)
# =============================

def lis(arr):
    n = len(arr)
    dp = [1]*n
    prev = [-1]*n
    for i in range(n):
        for j in range(i):
            if arr[j] < arr[i] and dp[j]+1 > dp[i]:
                dp[i] = dp[j]+1
                prev[i] = j
    idx = dp.index(max(dp))
    seq = []
    while idx != -1:
        seq.append(arr[idx])
        idx = prev[idx]
    seq.reverse()
    return max(dp), seq

arr_lis = [10, 22, 9, 33, 21, 50, 41, 60]
lis_len, lis_seq = lis(arr_lis)

# =============================
# Наибольшая общая подпоследовательность (LCS)
# =============================

def lcs(X, Y):
    m, n = len(X), len(Y)
    dp = [[0]*(n+1) for _ in range(m+1)]
    for i in range(m):
        for j in range(n):
            if X[i] == Y[j]:
                dp[i+1][j+1] = dp[i][j]+1
            else:
                dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j])
    i, j = m, n
    seq = []
    while i > 0 and j > 0:
        if X[i-1] == Y[j-1]:
            seq.append(X[i-1])
            i -= 1
            j -= 1
        elif dp[i-1][j] >= dp[i][j-1]:
            i -= 1
        else:
            j -= 1
    seq.reverse()
    return dp[m][n], seq

X = "GTAB"
Y = "GXTXAYB"
lcs_len, lcs_seq = lcs(X, Y)

# =============================
# Минимальное расстояние Левенштейна
# =============================

def levenshtein(s1, s2):
    m, n = len(s1), len(s2)
    dp = [[0]*(n+1) for _ in range(m+1)]
    for i in range(m+1):
        dp[i][0] = i
    for j in range(n+1):
        dp[0][j] = j
    for i in range(1,m+1):
        for j in range(1,n+1):
            cost = 0 if s1[i-1]==s2[j-1] else 1
            dp[i][j] = min(dp[i-1][j]+1,
                           dp[i][j-1]+1,
                           dp[i-1][j-1]+cost)
    return dp[m][n]

s1 = "kitten"
s2 = "sitting"
lev_dist = levenshtein(s1, s2)

# =============================
# Минимальная сумма пути в матрице
# =============================

def min_path_sum(matrix):
    m, n = len(matrix), len(matrix[0])
    dp = [[0]*n for _ in range(m)]
    dp[0][0] = matrix[0][0]
    for i in range(1, m):
        dp[i][0] = dp[i-1][0] + matrix[i][0]
    for j in range(1, n):
        dp[0][j] = dp[0][j-1] + matrix[0][j]
    for i in range(1, m):
        for j in range(1, n):
            dp[i][j] = matrix[i][j] + min(dp[i-1][j], dp[i][j-1])
    return dp[m-1][n-1]

matrix = [
    [1, 3, 1],
    [1, 5, 1],
    [4, 2, 1]
]
min_sum = min_path_sum(matrix)

# =============================
# Демонстрация результатов
# =============================

print("=== Числа Фибоначчи ===")
print("Рекурсивно:", fib_rec)
print("С мемоизацией:", fib_mem)
print("Итеративно:", fib_it)

print("\n=== Задача о рюкзаке ===")
print("Максимальная стоимость:", max_val)
print("Выбранные предметы (индексы):", chosen_items)

print("\n=== Наибольшая возрастающая подпоследовательность ===")
print("Длина НВП:", lis_len)
print("LIS:", lis_seq)

print("\n=== Наибольшая общая подпоследовательность ===")
print("Длина LCS:", lcs_len)
print("LCS:", lcs_seq)

print("\n=== Минимальное расстояние Левенштейна ===")
print("Расстояние:", lev_dist)

print("\n=== Минимальная сумма пути в матрице ===")
print("Минимальная сумма для прохода:", min_sum)

