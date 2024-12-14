#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

void prepareAndProcessFiles(const string& inputFile, const string& outputFile) {
	ofstream inFile(inputFile);

	if (inFile.is_open()) {
		srand(time(0));

		for (int i = 0; i < 100; ++i) {
			int num = -50 + rand() % 101;
			inFile << num << "\n";
		}

		inFile.close();
		cout << "Входной файл " << inputFile <<" успешно создан.\n";
	}
	else {
		cerr << "Ошибка при открытии файла" << inputFile << "\n";
	}

	ifstream infile(inputFile);
	ofstream outfile(outputFile);

	if (infile.is_open() && outfile.is_open()) {
		int num;
		int firstNegative = 0;

		while (infile >> num) {
			if (firstNegative == 0 && num < 0) {
				firstNegative = num;
			}
		}

		infile.clear();
		infile.seekg(0);

		while (infile >> num) {
			if (num % 2 == 0 && firstNegative != 0) {
				outfile << num * firstNegative << "\n";
			} else {
				outfile << num << "\n";
			}

		}

		cout << "Выходной файл " << outputFile << " успешно создан.\n";
	} else { 
		cerr << "Ошибка при открытии файла" << outputFile << "\n";
	}

	inFile.close();
	outfile.close();
}

int main() {
	setlocale(LC_ALL, "RU");
	prepareAndProcessFiles("input.txt", "output.txt");
	
	return 0;
}
