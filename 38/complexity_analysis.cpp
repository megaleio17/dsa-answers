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

double access_element(const vector<double>& v) {
    return v[rand() % v.size()];
}

double horner_method(const vector<double>& v, double x = 2.0) {
    double result = 0.0;
    for (int i = v.size() - 1; i >= 0; i--) {
        result = result * x + v[i];
    }
    return result;
}

double find_max(const vector<double>& v) {
    double max_val = v[0];
    for (double val : v) {
        if (val > max_val) {
            max_val = val;
        }
    }
    return max_val;
}

double arithmetic_mean(const vector<double>& v) {
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
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
    
    cout << "Начало эксперимента..." << endl;
    
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
    
    cout << "\nЭксперимент завершен!" << endl;
    return 0;
}