import random
import time
import matplotlib.pyplot as plt

# ---------------- Быстрая сортировка ----------------
def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

# ------------- Сортировка перемешиванием -------------
def cocktail_sort(arr):
    n = len(arr)
    swapped = True
    start = 0
    end = n - 1
    while swapped:
        swapped = False
        for i in range(start, end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True
        if not swapped:
            break
        swapped = False
        end -= 1
        for i in range(end - 1, start - 1, -1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True
        start += 1
    return arr

# ---------------- Тестирование ----------------
def test_sorts(sizes):
    results = {"quick": [], "cocktail": []}
    for n in sizes:
        arr = [random.randint(0, 100000) for _ in range(n)]
        arr_sorted = sorted(arr)
        arr_rev = sorted(arr, reverse=True)

        for name, func in [("quick", quick_sort), ("cocktail", cocktail_sort)]:
            for dataset in [arr, arr_sorted, arr_rev]:
                data_copy = dataset.copy()
                start = time.perf_counter()
                func(data_copy)
                duration = time.perf_counter() - start
                results[name].append(duration)
                print(f"{name:8} | n={n:<6} | {duration:.5f} сек")
        print("-" * 50)
    return results

# ---------------- Запуск тестов ----------------
sizes = [1000, 5000, 10000, 100000]
results = test_sorts(sizes)

# ---------------- График ----------------
plt.figure(figsize=(8,5))
plt.plot(sizes * 3, results["quick"], label="Быстрая сортировка (Хоара)")
plt.plot(sizes * 3, results["cocktail"], label="Сортировка перемешиванием")
plt.xlabel("Размер массива n")
plt.ylabel("Время, сек")
plt.legend()
plt.grid()
plt.title("Сравнение производительности алгоритмов сортировки (вариант 4)")
plt.show()

quick    | n=1000   | 0.00391 сек
quick    | n=1000   | 0.00229 сек
quick    | n=1000   | 0.00264 сек
cocktail | n=1000   | 0.09708 сек
cocktail | n=1000   | 0.00011 сек
cocktail | n=1000   | 0.15545 сек
--------------------------------------------------
quick    | n=5000   | 0.02080 сек
quick    | n=5000   | 0.01865 сек
quick    | n=5000   | 0.01491 сек
cocktail | n=5000   | 2.59846 сек
cocktail | n=5000   | 0.00059 сек
cocktail | n=5000   | 4.56226 сек
--------------------------------------------------
quick    | n=10000  | 0.04239 сек
quick    | n=10000  | 0.03017 сек
quick    | n=10000  | 0.03383 сек
cocktail | n=10000  | 11.00180 сек
cocktail | n=10000  | 0.00201 сек
cocktail | n=10000  | 16.36703 сек
--------------------------------------------------
quick    | n=100000 | 0.64004 сек
quick    | n=100000 | 0.49779 сек
quick    | n=100000 | 0.49416 сек
