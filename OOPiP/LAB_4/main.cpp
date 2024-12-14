#include <iostream>
#include "Queue.h"
#include <string>

using namespace std;

void testQueue() {
	Queue<int> intQueue = { 1, 2, 3, 4, 5 };
	Queue<double> doubleQueue = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	Queue<string> stringQueue = { "one", "two", "three", "four", "five" };

	cout << "Первый элемент очереди int: " << intQueue.getFront() << endl;
	cout << "Последний элемент очереди int: " << intQueue.getBack() << endl;
	cout << "Первый элемент очереди double: " << doubleQueue.getFront() << endl;
	cout << "Последний элемент очереди double: " << doubleQueue.getBack() << endl;
	cout << "Первый элемент очереди string: " << stringQueue.getFront() << endl;
	cout << "Последний элемент очереди string: " << stringQueue.getBack() << endl;

	try {
		while (!intQueue.isEmpty()) {
			cout << "Удалена из очереди int: " << intQueue.dequeue() << endl;
		}
	}
	catch (const CustomException& e) {
		cout << "Исключение: " << e.what() << endl;
	}

	try {
		cout << "Попытка вывода из пустой очереди..." << endl;
		intQueue.dequeue();
	}
	catch (const CustomException& e) {
		cout << "Исключение: " << e.what() << endl;
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	testQueue();

	Queue<double> myQueue;
	myQueue.enqueue(3.14);
	myQueue.enqueue(2.71);
	myQueue.enqueue(2.42);
	cout << "Первый в очереди: " << myQueue.getFront() << endl;
	cout << "Последний в очереди: " << myQueue.getBack() << endl;

	try {
		cout << "Удаление из очереди: " << myQueue.dequeue() << endl;
		cout << "Удаление из очереди: " << myQueue.dequeue() << endl;
		cout << "Попытка вывода из пустой очереди..." << endl;
		cout << myQueue.dequeue() << endl;
	}
	catch (const CustomException& e) {
		cout << "Перехваченное исключение: " << e.what() << endl;
	}

	return 0;
}
