# Эмпирический анализ временной сложности алгоритмов
Бахал И.А.
ИУ10-38

## Задания

### Задание 1.1: Доступ к элементу по индексу

```cpp
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;
using namespace std::chrono;

vector<double> generate_random_vector(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 10.0);
    
    vector<double> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = dis(gen);
    }
    return v;
}

double access_element(const vector<double>& v) {
    return v[rand() % v.size()];
}

double measure_time(function<void()> func, int runs = 5) {
    double total_time = 0.0;
    for (int i = 0; i < runs; i++) {
        auto start = high_resolution_clock::now();
        func();
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        total_time += elapsed.count();
    }
    return total_time / runs;
}

int main() {
    int student_number = 16;
    int N = 20 - student_number;
    
    cout << "Задание 1.1..." << endl;
    ofstream file1_1("task_1_1.csv");
    file1_1 << "n,time\n";
    
    for (int n = 100; n <= 100000 * N; n += 50000) {
        vector<double> v = generate_random_vector(n);
        double time = measure_time([&]() {
            for (int i = 0; i < 100; i++) access_element(v);
        });
        file1_1 << n << "," << time << "\n";
        cout << "n=" << n << ", time=" << time << " сек" << endl;
    }
    file1_1.close();
    return 0;
}
```
![png](Lab_01_files/task_1_1.png)


### Задание 1.4: Вычисление полинома методом Горнера

```cpp
double horner_method(const vector<double>& v, double x = 2.0) {
    double result = 0.0;
    for (int i = v.size() - 1; i >= 0; i--) {
        result = result * x + v[i];
    }
    return result;
}

// В main():
cout << "\nЗадание 1.4..." << endl;
ofstream file1_4("task_1_4.csv");
file1_4 << "n,time\n";

for (int n = 100; n <= 100000 * N; n += 50000) {
    vector<double> v = generate_random_vector(n);
    double time = measure_time([&]() { horner_method(v); });
    file1_4 << n << "," << time << "\n";
    cout << "n=" << n << ", time=" << time << " сек" << endl;
}
file1_4.close();
```
![png](Lab_01_files/task_1_4.png)


### Задание 1.5: Поиск максимума простым перебором
```cpp
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;
using namespace std::chrono;

double find_max(const vector<double>& v) {
    double max_val = v[0];
    for (double val : v) {
        if (val > max_val) {
            max_val = val;
        }
    }
    return max_val;
}

// В main():
cout << "\nЗадание 1.5..." << endl;
ofstream file1_5("task_1_5.csv");
file1_5 << "n,time\n";

for (int n = 100; n <= 100000 * N; n += 50000) {
    vector<double> v = generate_random_vector(n);
    double time = measure_time([&]() { find_max(v); });
    file1_5 << n << "," << time << "\n";
    cout << "n=" << n << ", time=" << time << " сек" << endl;
}
file1_5.close();
```
![png](Lab_01_files/task_1_5.png)


### Задание 1.7: Среднее арифметическое
```cpp
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;
using namespace std::chrono;

double arithmetic_mean(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

// В main():
cout << "\nЗадание 1.7..." << endl;
ofstream file1_7("task_1_7.csv");
file1_7 << "n,time\n";

for (int n = 100; n <= 100000 * N; n += 50000) {
    vector<double> v = generate_random_vector(n);
    double time = measure_time([&]() { arithmetic_mean(v); });
    file1_7 << n << "," << time << "\n";
    cout << "n=" << n << ", time=" << time << " сек" << endl;
}
file1_7.close();
```
![png](Lab_01_files/task_1_7.png)


### Задание 2: Матричное умножение
```cpp
vector<vector<double>> generate_random_matrix(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 10.0);
    
    vector<vector<double>> matrix(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

vector<vector<double>> matrix_multiply(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0.0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// В main():
cout << "\nЗадание 2..." << endl;
ofstream file2("task_2.csv");
file2 << "n,time\n";

for (int n = 10; n <= 100 * N; n += 100) {
    vector<vector<double>> A = generate_random_matrix(n);
    vector<vector<double>> B = generate_random_matrix(n);
    double time = measure_time([&]() { matrix_multiply(A, B); });
    file2 << n << "," << time << "\n";
    cout << "n=" << n << ", time=" << time << " сек" << endl;
}
file2.close();
```
![png](Lab_01_files/task_2.png)


```
```
#### Вывод:
В ходе лабораторной работы был проведен эмпирический анализ временной сложности различных алгоритмов. Экспериментальные исследования подтвердили теоретические оценки временной сложности:

Задание 1.1: Доступ к элементу по индексу - продемонстрировал постоянное время выполнения O(1), что характерно для операций произвольного доступа в массивах и векторах.

Задание 1.4: Метод Горнера - показал линейную зависимость времени выполнения от размера входных данных O(n), что соответствует алгоритму последовательного вычисления полинома.

Задание 1.5: Поиск максимума - также подтвердил линейную сложность O(n), так как алгоритм требует полного прохода по всем элементам вектора.

Задание 1.7: Среднее арифметическое - продемонстрировал линейную сложность O(n), поскольку необходимо просуммировать все элементы вектора.

Задание 2: Матричное умножение - выявило кубическую сложность O(n³), что объясняется тремя вложенными циклами для перемножения матриц размером n×n.

Полученные экспериментальные данные полностью соответствуют теоретическим ожиданиям, что подтверждает корректность реализации алгоритмов и методики измерения времени выполнения. Результаты работы наглядно демонстрируют важность анализа временной сложности алгоритмов для прогнозирования их производительности на больших объемах данных.