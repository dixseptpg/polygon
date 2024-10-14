// #include <iostream>
// #include <vector>
// #include <string>

// using namespace std;
// //Найти количество нечётных чисел в массиве

// //def Get_len_odd;
// /*a variable -- 
// Type name;
// Type name1, name2, name3;

// */

// int main()
// {
//     int n;
//     int a[n];
//     a = input("Введите массив: "); //thats an array
//     for (int i = 0; i < n; ++i)
//     {
//         a[i] = i + 1;
//     }

//     for i in a
//         if n % 2 == 0


//     std::vector 
//     std::array
//     int number;

//     a = input(array)


//     return 0;
// }




#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Размер массива: ";
    cin >> n;

    int arr[n]; //Массив заданного размера

    // Вводим элементы массива
    cout << "Элементы массива: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int count = 0; // Счётчик нечётных чисел

    // Проходим по массиву и считаем нечётные числа
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 = 1) { // Проверяем, является ли число нечётным
            count++; // Увеличиваем счётчик
        }
    }

    // Выводим результат
    cout << "Количество нечётных чисел в массиве: " << count << endl;

    return 0;
}
