#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;

    cout << "Размер массива: ";
    cin >> n;

    int arr[n]; //Массив заданного размера

    cout << "Элементы массива: "; // Вводим элементы массива
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int odd_count = 0; // Счётчик нечётных чисел

    // Проходим по массиву и считаем нечётные числа
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 1) { // Проверяем, является ли число нечётным
            count++; // Увеличиваем счётчик
        }
    }

    // Выводим результат
    cout << "Количество нечётных чисел в массиве: " << count << endl;

    return 0;
}
