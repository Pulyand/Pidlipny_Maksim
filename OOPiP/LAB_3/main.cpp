#include <iostream>
#include <string>

template<typename T>
class ScPtrArr {
private:
    T* ptr;

public:
    explicit ScPtrArr(T* p = nullptr) : ptr(p) {}
    ~ScPtrArr() { delete[] ptr; }

    void reset(T* p = nullptr) {
        delete[] ptr;
        ptr = p;
    }

    void swap(ScPtrArr& other) {
        T* temp = ptr;
        ptr = other.ptr;
        other.ptr = temp;
    }

    T* get() const {
        return ptr;
    }

    T& operator[](size_t index) {
        return ptr[index];
    }

    const T& operator[](size_t index) const {
        return ptr[index];
    }

    ScPtrArr(const ScPtrArr&) = delete;
    ScPtrArr& operator=(const ScPtrArr&) = delete;
};

void showMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Создать массив int\n";
    std::cout << "2. Создать массив double\n";
    std::cout << "3. Создать массив std::string\n";
    std::cout << "4. Обнулить указатель\n";
    std::cout << "5. Обменять указатели\n";
    std::cout << "6. Показать элемент по индексу\n";
    std::cout << "0. Выход\n";
}

int main() {
    ScPtrArr<int> intArr;
    ScPtrArr<double> doubleArr;
    ScPtrArr<std::string> stringArr;

    int choice;
    while (true) {
        showMenu();
        std::cout << "Выберите пункт: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            intArr.reset(new int[3]{1, 2, 3});
            std::cout << "Массив int создан.\n";
            break;
        }
        case 2: {
            doubleArr.reset(new double[3]{1.1, 2.2, 3.3});
            std::cout << "Массив double создан.\n";
            break;
        }
        case 3: {
            stringArr.reset(new std::string[3]{"Hello", "World", "C++"});
            std::cout << "Массив std::string создан.\n";
            break;
        }
        case 4: {
            intArr.reset();
            std::cout << "Указатель обнулен.\n";
            break;
        }
        case 5: {
            ScPtrArr<int> otherIntArr(new int[3]{4, 5, 6});
            intArr.swap(otherIntArr);
            std::cout << "Указатели обменяны.\n";
            break;
        }
        case 6: {
            size_t index;
            std::cout << "Введите индекс: ";
            std::cin >> index;
            if (intArr.get() != nullptr) {
                std::cout << "Элемент массива int: " << intArr[index] << "\n";
            } else {
                std::cout << "Массив пустой.\n";
            }
            break;
        }
        case 0:
            return 0;
        default:
            std::cout << "Неверный выбор. Повторите попытку.\n";
        }
    }
}
