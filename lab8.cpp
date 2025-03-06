#include <iostream>
#include <stdexcept> // Для обработки исключений-ошибок
#include <algorithm> // Для std::copy

class Vector {
private:
    int* data;   // Указатель на динамический массив (наши данные)
    size_t size;  // Размер вектора (количество элементов)

public:
    // 1. Конструктор (Создание вектора)
    Vector(size_t n) : size(n) {
        // Выделяем память под n элементов типа int
        data = new int[n];

        // Инициализируем элементы нулями 
        for (size_t i = 0; i < n; ++i) {
            data[i] = 0;
        }
        //std::cout << "Constructor called.  Size: " << size << std::endl; 
    }

    // Конструктор копирования (нужен для правильной работы с динамической памятью)
    Vector(const Vector& other) : size(other.size) {
        //std::cout << "Copy constructor called." << std::endl; //Отладочный
        data = new int[size]; // Выделяем память для копии
        std::copy(other.data, other.data + other.size, data); // Копируем данные
    }

    // Оператор присваивания копированием (тоже нужен для правильной работы)
    Vector& operator=(const Vector& other) {
       // std::cout << "Assignment operator called." << std::endl; //Отладочный

        if (this != &other) { // Проверка на самоприсваивание (a = a)
            // 1. Освобождаем старую память, если она была
            delete[] data;

            // 2. Выделяем новую память
            size = other.size;
            data = new int[size];

            // 3. Копируем данные
            std::copy(other.data, other.data + other.size, data);
        }
        return *this; // Возвращаем ссылку на текущий объект (для цепочек присваиваний)
    }


    // 2. Деструктор (Освобождение памяти)
    ~Vector() {
        delete[] data; // Освобождаем память, выделенную под массив
        //std::cout << "Destructor called. Size: " << size << std::endl; // Отладочный вывод
    }

    // Метод для доступа к элементу по индексу (с проверкой границ)
    int& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range"); // Генерируем исключение
        }
        return data[index];
    }

    // Константная версия метода at() (для константных объектов)
    const int& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }


    // 3. Сложение векторов (+)
    Vector operator+(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same size for addition");
        }

        Vector result(size); // Создаём новый вектор для результата
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] + other.data[i]; // Складываем поэлементно
        }
        return result;
    }

    // 4. Вычитание векторов (-)
    Vector operator-(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same size for subtraction");
        }

        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // 5. Умножение векторов (*) (поэлементное)
    Vector operator*(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same size for multiplication");
        }

        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] * other.data[i];
        }
        return result;
    }

    // 6. Деление векторов (/) (поэлементное)
    Vector operator/(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same size for division");
        }

        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            if (other.data[i] == 0) {
                throw std::invalid_argument("Division by zero"); // Проверка деления на ноль
            }
            result.data[i] = data[i] / other.data[i];
        }
        return result;
    }

     // Метод для вывода вектора на экран
    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i];
            if (i < size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    //Дополнительный метод - получение размера
    size_t getSize() const{
        return size;
    }
};

int main() {
    try {
        // Создаём два вектора
        Vector v1(3);
        v1.at(0) = 1;
        v1.at(1) = 2;
        v1.at(2) = 3;

        Vector v2(3);
        v2.at(0) = 4;
        v2.at(1) = 5;
        v2.at(2) = 6;

        // Выводим исходные векторы
        std::cout << "v1: ";
        v1.print();  // [1, 2, 3]
        std::cout << "v2: ";
        v2.print();  // [4, 5, 6]

        // Сложение
        Vector v3 = v1 + v2;
        std::cout << "v1 + v2: ";
        v3.print();  // [5, 7, 9]

        // Вычитание
        Vector v4 = v1 - v2;
        std::cout << "v1 - v2: ";
        v4.print();  // [-3, -3, -3]

        // Умножение
        Vector v5 = v1 * v2;
        std::cout << "v1 * v2: ";
        v5.print();  // [4, 10, 18]

        // Деление
        Vector v6 = v1 / v2;
        std::cout << "v1 / v2: ";
        v6.print();  // [0, 0, 0]  (т.к. целочисленное деление)

        // Проверка деления на ноль
        Vector v7(2);
        v7.at(0) = 1;
        v7.at(1) = 2;

        Vector v8(2);
        v8.at(0) = 0;
        v8.at(1) = 5;

        // Vector v9 = v7 / v8; // Исключение
        // std::cout << "v7 / v8: ";
        // v9.print();

        // Проверка на разную размерность
        Vector v10(2);
        Vector v11(3);
        //Vector v12 = v10 + v11;   // Исключение
        //std::cout << "v10 + v11: ";
        //v12.print();

        //Пример копирования и присваивания
        Vector v13(4);
        v13.at(0)=10; v13.at(1)=20; v13.at(2)=30; v13.at(3)=40;

        Vector v14 = v13; //Копирование
        std::cout << "v14 (copy of v13): ";
        v14.print();

        Vector v15(2);
        v15.at(0) = -1; v15.at(1)=-2;
        v15 = v13; //Присваивание
        std::cout << "v15 (assigned from v13): ";
        v15.print();



    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; // Выводим сообщение об ошибке
    }

    return 0;
}