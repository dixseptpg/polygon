#include <iostream>
#include <vector>
#include <limits> // Для numeric_limits
#include <algorithm> // Для std::swap

using namespace std;

// 1. Сортировка выбором 
int findSmallest(const vector<int>& arr) {
    int smallest = arr[0];
    int smallest_index = 0;

    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] < smallest) {
            smallest = arr[i];
            smallest_index = i;
        }
    }
    return smallest_index;
}

vector<int> selectionSort(vector<int> arr) {
    vector<int> newArr;

    while (!arr.empty()) {
        int smallest_index = findSmallest(arr);
        newArr.push_back(arr[smallest_index]);
        arr.erase(arr.begin() + smallest_index);
    }
    return newArr;
}

// 2. Сортировка пузырьком

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            
            }
        }
    }
}

// 3. Гномья сортировка
void gnomeSort(vector<int>& arr) {
    int n = arr.size();
    int index = 0;

    while (index < n) {
        if (index == 0 || arr[index] >= arr[index - 1]) {
            index++;
        } else {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
}

// Вспомогательная функция для вывода вектора 
void printVector(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}
//  функция main, в которой все три сортировки
int main() {
    // 1
    vector<int> arr1 = {2, 3, 6, 2, 10, 1, 8, 5, 9, 4, 7}; // Добавлены еще элементы
    cout << "Selection Sort:" << endl;
    cout << "Unsorted array: ";
    printVector(arr1); // используем вспомогательную функцию
    vector<int> sortedArr1 = selectionSort(arr1); // Копируем, т.к. selection sort возвращает новый вектор
    cout << "Sorted array: ";
    printVector(sortedArr1);
    cout << endl;

    // 2
     vector<int> arr2;
    int n;
    cout << "Bubble Sort:" << endl;
    cout << "Enter the number of elements: ";
    cin >> n;
    arr2.resize(n); // Задаём размер вектора
    cout << "Enter " << n << " elements: " << endl;
    for(int i=0; i<n; ++i){
        cin >> arr2[i];
    }

    cout << "Unsorted array: ";
    printVector(arr2);
    bubbleSort(arr2); // Сортируем "на месте"
    cout << "Sorted array: ";
    printVector(arr2);
    cout << endl;

    // 3
    vector<int> arr3 = {7, 2, 4, 1, 5, 3, 12, 6, 10, 0, 8}; //Другой пример
    cout << "Gnome Sort:" << endl;
    cout << "Unsorted array: ";
    printVector(arr3);
    gnomeSort(arr3); // Сортируем "на месте"
    cout << "Sorted array: ";
    printVector(arr3);
    cout << endl;
    

    return 0;
}