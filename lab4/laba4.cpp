#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <cmath>
#include <cassert>
#include <chrono>
#include <fstream>

/*

Кластеризация массива посредством полного перебора всех комбинаций значений этого массива
Количество кластеров - 5
Алгоритмическая сложность не должна быть меньше чем O(2^N) (подразумевает перебор всех возможных наборов кластеров) 
Максимальное кол-во элементов - до 25
Алгоритм не должен работать больше часа

*/


using namespace std;

// Функция для рассчёта среднего значения подмассива
double calculateMean(const vector<double>& arr) {
    double sum = accumulate(arr.begin(), arr.end(), 0.0);
    return sum / arr.size();
}

// Функция для рассчеёа метрики (суммы абсолютных отклонений от среднего)
double calculateMetric(const vector<double>& arr) {
    double mean = calculateMean(arr);
    double metric = 0.0;
    // O(N) - сложность цикла; N - размер arr
    for (double val : arr) { 
        // 8 байт - на каждой итерации цикла выделяется память под временную переменную
        metric += abs(val - mean);
    }
    return metric;
}

// Рекурсивная функция для генерации всех комбинаций
void generateCombinations(const vector<double>& arr, int k, int index, vector<vector<double>>& currentClusters, double& bestMetric, vector<vector<double>>& bestClusters) {
    // O(K^N) - сложность рекурсии; N - размер массива arr, K - количество кластеров, т.к. на каждом уровне рекурсии - K ветвлений, а глубина рекурсии N
    // K * N * 8 байт - размер вектора currentClusters (в худшем случае, когда все элементы в одном кластере)
    // K * N * 8 байт - размер вектора bestClusters (в худшем случае, когда все элементы в одном кластере)
    if (index == arr.size()) {
        // O(K) - сложность цикла, где K - количество кластеров
        // K * 8 байт - размер вектора currentClusters
        bool valid = true;
        for (int j = 0; j < k; ++j) {
            if (currentClusters[j].empty()) {
                valid = false;
                break;
            }
        }

        double currentMetric = 0.0;
        // O(K * N) - сложность цикла в худшем случае; K - количество кластеров, N - размер наибольшего кластера
        // K * N * 8 байт - размер вектора currentClusters
        for (const auto& cluster : currentClusters) {
            currentMetric += calculateMetric(cluster);
            // 8 байт - на каждой итерации цикла выделяется память под временную переменную
        }

        if (currentMetric < bestMetric) {
            bestMetric = currentMetric;
            // O(K * N) - сложность копирования; K - количество кластеров, N - размер наибольшего кластера
            // K * N * 8 байт - размер вектора currentClusters
            // K * N * 8 байт - размер вектора bestClusters
            bestClusters = currentClusters;
        }
        return;
    }

    // O(K) - сложность цикла, где K - количество кластеров
    for (int i = 0; i < k; ++i) {
        // K * N * 8 байт - размер вектора currentClusters
        // 8 байт - на каждой итерации цикла выделяется память под временную переменную
        currentClusters[i].push_back(arr[index]);
        // O(K^(N-1)) - сложность рекурсивного вызова, т.к. глубина рекурсии уменьшается на 1
        generateCombinations(arr, k, index + 1, currentClusters, bestMetric, bestClusters);
        currentClusters[i].pop_back();
    }
}

// Функция для кластеризации массива с полным перебором
vector<vector<double>> clusterize(const vector<double>& arr, int k) {
    int n = arr.size();
    double bestMetric = numeric_limits<double>::max();
    // K * N * 8 байт - размер вектора bestClusters (в худшем случае, когда все элементы в одном кластере)
    vector<vector<double>> bestClusters;

    if (n == 0) {
        return {}; 
    }

    // O(K) - сложность инициализации вектора размером K
    // K * N * 8 байт - размер вектора currentClusters (в худшем случае, когда все элементы в одном кластере)
    vector<vector<double>> currentClusters(k);
    // O(K^N) - сложность generateCombinations; N - размер массива, K - количество кластеров
    generateCombinations(arr, k, 0, currentClusters, bestMetric, bestClusters);

    // O(K) - сложность цикла; K - количество кластеров
    for (int i = 0; i < k; ++i) {
        if (bestClusters.size() <= i) {
            bestClusters.push_back({});
            // 8 байт - на каждой итерации цикла выделяется память под временную переменную
        }
    }

    // K * N * 8 байт - размер возвращаемого значения
    return bestClusters;
}

void testEdgeCases() {
    
    // 1) Пустой массив:
    vector<double> emptyArr;
    vector<vector<double>> emptyResult = clusterize(emptyArr, 5);
    cout << "Пустой массив: ";
    cout << "[";
    for (size_t i = 0; i < emptyResult.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < emptyResult[i].size(); ++j) {
            cout << emptyResult[i][j];
            if (j < emptyResult[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << "]";
        if (i < emptyResult.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    assert(emptyResult.empty());

    // 2) Массив с одним элементом:
    vector<double> singleElementArr = {1.0};
    vector<vector<double>> singleElementResult = clusterize(singleElementArr, 5);
    cout << "Массив с одним элементом: ";
    cout << "[";
    for (size_t i = 0; i < singleElementResult.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < singleElementResult[i].size(); ++j) {
            cout << singleElementResult[i][j];
            if (j < singleElementResult[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << "]";
        if (i < singleElementResult.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    assert(singleElementResult.size() == 5 && singleElementResult[0].size() == 1 && singleElementResult[0][0] == 1.0);

    // 3) Массив, в котором количество кластеров больше, чем количество элементов:
    vector<double> moreClustersArr = {1.0, 2.0};
    vector<vector<double>> moreClustersResult = clusterize(moreClustersArr, 5);
    cout << "Массив, в котором количество кластеров больше, чем количество элементов: ";
    cout << "[";
    for (size_t i = 0; i < moreClustersResult.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < moreClustersResult[i].size(); ++j) {
            cout << moreClustersResult[i][j];
            if (j < moreClustersResult[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << "]";
        if (i < moreClustersResult.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    assert(moreClustersResult.size() == 5 && moreClustersResult[0].size() == 1 && moreClustersResult[0][0] == 1.0 && moreClustersResult[1].size() == 1 && moreClustersResult[1][0] == 2.0);
}

int main() {
    testEdgeCases();

    // Датасет массива
    vector<double> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 5; // Количество кластеров по заданию

    // N * (4 + 8) = N * 12 байт - размер вектора timeData (в худшем случае, когда N - размер массива arr)
    vector<pair<int, double>> timeData;

    // O(N) - сложность цикла; N - размер массива arr
    for (int n = 1; n <= (int)arr.size(); ++n) {
        // N * 8 байт - размер вектора sub_arr (в худшем случае, когда N - размер массива arr)
        vector<double> sub_arr(arr.begin(), arr.begin() + n);
        auto start = chrono::high_resolution_clock::now();
        // O(K^N) - сложность clusterize; N - размер подмассива, K - количество кластеров
        clusterize(sub_arr, k);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        // O(1) - сложность добавления элемента в вектор
        timeData.push_back({n, duration.count()});
        // 12 байт - на каждой итерации цикла выделяется память под временную переменную
    }

    ofstream outfile("time_data.txt");
    // O(N) - сложность цикла; N - размер вектора timeData
    for (const auto& data : timeData) {
        outfile << data.first << "\t" << data.second << endl;
        // (4 + 8) байт - на каждой итерации цикла выделяется память под временную переменную
    }
    outfile.close();

    // Вывод результатов кластеризации для исходного массива
    // O(K^N) - сложность clusterize; N - размер массива, K - количество кластеров
    // K * N * 8 байт - размер вектора result (в худшем случае, когда все элементы в одном кластере)
    
    vector<vector<double>> result = clusterize(arr, k);
    cout << "Результат кластеризации для массива: ";
    cout << "[";
    // O(K) - сложность цикла; K - количество кластеров
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "[";
        // O(N) - сложность цикла; N - размер кластера
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j < result[i].size() - 1) {
                cout << ", ";
            }
        }
        cout << "]";
        if (i < result.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}