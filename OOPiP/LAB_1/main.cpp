#include <iostream>
#include <stdexcept>
#include <string>

namespace containers {

    template<typename T>
    class DRList {
    private:
        struct Node {
            T value;
            Node* next;
            Node* prev;

            Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
        };

        Node* head_;
        size_t size_;

    public:
        DRList() : head_(nullptr), size_(0) {}

        ~DRList() {
            clear();
        }

        DRList(const DRList& other) : head_(nullptr), size_(other.size_) {
            if (other.head_) {
                Node* current = other.head_;
                do {
                    push_back(current->value);
                    current = current->next;
                } while (current != other.head_);
            }
        }

        DRList& operator=(const DRList& other) {
            if (this != &other) {
                clear();
                if (other.head_) {
                    head_ = new Node(other.head_->value);
                    Node* current = other.head_;
                    do {
                        push_back(current->value);
                        current = current->next;
                    } while (current != other.head_);
                }
            }
            return *this;
        }

        DRList(DRList&& other) noexcept : head_(other.head_), size_(other.size_) {
            other.head_ = nullptr;
            other.size_ = 0;
        }

        DRList& operator=(DRList&& other) noexcept {
            if (this != &other) {
                clear();
                head_ = other.head_;
                size_ = other.size_;
                other.head_ = nullptr;
                other.size_ = 0;
            }
            return *this;
        }

        T& operator[](size_t index) {
            if (index >= size_) throw std::out_of_range("Index out of range");

            Node* current = head_;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        void push_back(const T& value) {
            Node* newNode = new Node(value);

            if (!head_) {
                head_ = newNode;
                newNode->next = newNode;
                newNode->prev = newNode;
            }
            else {
                newNode->next = head_;
                newNode->prev = head_->prev;
                head_->prev->next = newNode;
                head_->prev = newNode;
            }

            size_++;
        }

        void pop_back() {
            if (!head_) return;

            if (size_ == 1) {
                delete head_;
                head_ = nullptr;
            }
            else {
                Node* temp = head_->prev;
                temp->prev->next = head_;
                head_->prev = temp->prev;
                delete temp;
            }

            size_--;
        }

        void printForward() const {
            if (!head_) return;

            Node* current = head_;
            do {
                std::cout << current->value << " ";
                current = current->next;
            } while (current != head_);
            std::cout << std::endl;
        }

        void printBackward() const {
            if (!head_) return;

            Node* current = head_->prev;
            do {
                std::cout << current->value << " ";
                current = current->prev;
            } while (current != head_->prev);
            std::cout << std::endl;
        }

        void clear() {
            while (head_) {
                Node* temp = head_;
                head_ = head_->next;
                delete temp;
            }
            size_ = 0;
        }

        size_t size() const {
            return size_;
        }

        void moveBackward(size_t steps) {
            if (!head_ || steps >= size_) return;

            Node* current = head_;
            for (size_t i = 0; i < steps % size_; ++i) {
                current = current->prev;
            }

            head_ = current;
        }

        void printCurrentPosition() const {
            if (!head_) {
                std::cout << "Список пустой." << std::endl;
                return;
            }

            std::cout << "Текущая позиция: " << head_->value << std::endl;
        }
    };

} // namespace containers

template<typename T>
void demonstrateDRList(const std::string& typeName) {
    using namespace containers;

    DRList<T> list;

    std::cout << "\nДемонстрация DRList<" << typeName << ">:" << std::endl;

    int choice;
    do {
        std::cout << "1. Показ элементов" << std::endl;
        std::cout << "2. Печать вперед" << std::endl;
        std::cout << "3. Печать назад" << std::endl;
        std::cout << "4. Просмотр назад" << std::endl;
        std::cout << "5. Очистка списка" << std::endl;
        std::cout << "6. Проверка на пустоту списка" << std::endl;
        std::cout << "7. Выход" << std::endl;
        std::cout << "Введите ваш выбоо: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if constexpr (std::is_same_v<T, int>) {
                    list.push_back(10);
                    list.push_back(20);
                    list.push_back(30);
                }
                else if constexpr (std::is_same_v<T, double>) {
                    list.push_back(10.5);
                    list.push_back(20.7);
                    list.push_back(30.9);
                }
                else if constexpr (std::is_same_v<T, std::string>) {
                    list.push_back("Hello");
                    list.push_back("World");
                    list.push_back("C++");
                }
                break;
            case 2:
                list.printForward();
                break;
            case 3:
                list.printBackward();
                break;
            case 4:
                list.moveBackward(1);
                break;
            case 5:
                list.clear();
                break;
            case 6:
                std::cout << "Список пустой? " << (list.size() == 0 ? "Да" : "Нет") << std::endl;
                break;
            default:
                std::cout << "Неправильный выбор. Пожалуйста, повторите заново" << std::endl;
        }

        list.printCurrentPosition();

    } while (choice != 7);

    return 0;
}

int main() {
    using namespace containers;

    int choice;
    do {
        std::cout << "\nМеню:" << std::endl;
        std::cout << "1. Демонстрация DRList<int>" << std::endl;
        std::cout << "2. Демонстрация DRList<double>" << std::endl;
        std::cout << "3. Демонстрация DRList<std::string>" << std::endl;
        std::cout << "4. Выход" << std::endl;
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                demonstrateDRList<int>("int");
                break;
            case 2:
                demonstrateDRList<double>("double");
                break;
            case 3:
                demonstrateDRList<std::string>("std::string");
                break;
            case 4:
                std::cout << "Выход..." << std::endl;
                return 0; // Выход из программы
            default:
                std::cout << "Неправильный выбор. Пожалуйста, повторите заново." << std::endl;
        }

    } while (choice != 4);

    return 0;
}
