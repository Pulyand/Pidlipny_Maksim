#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

class CustomException {
private:
    string message;
    double value;
    int errorCode;

public:
    CustomException(const string& msg, double val, int code)
        : message(msg), value(val), errorCode(code) {}

    const char* what() const noexcept {
        return message.c_str();
    }

    double getValue() const noexcept {
        return value;
    }

    int getErrorCode() const noexcept {
        return errorCode;
    }
};

double calculateZ1(double x) {
    if (x == -2) {
        throw CustomException("Деление на ноль при вычислении Z1", x, 1);
    }
    if (x * x - 4 < 0) {
        throw CustomException("Недопустимое значение под корнем при вычислении Z1", x, 1);
    }

    double numerator = sqrt(2 * sqrt(x * x - 4) + 2 * x);
    double denominator = x + sqrt(x * x - 4) + 2;

    return numerator / denominator;
}

double calculateZ2(double x) {
    if (x < 2) {
        throw CustomException("Недопустимое значение под корнем при вычислении Z2", x, 2);
    }

    return 1 / sqrt(x + 2);
}

int main() {
    setlocale(0, "ru");

    try {
        double x;
        cout << "Введите значение x: ";
        cin >> x;

        double z1 = calculateZ1(x);
        double z2 = calculateZ2(x);

        cout << "Z1 = " << z1 << "\n";
        cout << "Z2 = " << z2 << "\n";

        if (abs(z1 - z2) < 1e-5) {
            cout << "Значения Z1 и Z2 приблизительно равны.\n";
        } else {
            cout << "Значения Z1 и Z2 различаются.\n";
        }

        cout << "Разница между Z1 и Z2: " << abs(z1 - z2) << "\n";
    } catch (const CustomException& e) {
        cerr << "Ошибка: " << e.what() << "\n";
        cerr << "Значение: " << e.getValue() << "\n";
        cerr << "Код ошибки: " << e.getErrorCode() << "\n";
    } catch (...) {
        cerr << "Неизвестная ошибка\n";
    }

    return 0;
}
