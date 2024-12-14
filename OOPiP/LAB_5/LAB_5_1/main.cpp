#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class CustomString {
private:
	string str;

public:
	friend istream& operator>>(istream& is, CustomString& cs) {
		getline(is, cs.str);
		return is;
	}

	friend ostream& operator<< (ostream& os, const CustomString& cs) {
		string processed = cs.str;
		transform(processed.begin(), processed.end(), processed.begin(), [](unsigned char c) {
			return tolower(c);
		});

		for (char c : processed) {
			if (!isdigit(c)) {
				os << c;
			}
		}
		return os;
	}
};

int main() {
	setlocale(LC_ALL,"Ru");

	CustomString customStr;
	cout << "Введите строку: ";
	cin >> customStr;
	cout << "Обработанная строка: " << customStr << endl;
	return 0;
}
