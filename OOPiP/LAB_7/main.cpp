#include <iostream>
#include "Queue.h"
#include "Iterators.h"
#include <string>

using namespace std;

void testQueue() {
    Queue<int> intQueue = { -1, -2, 3, -4, 5 };
    Queue<double> doubleQueue = { 1.1, -2.2, 3.3, -4.4, -5.5 };
    Queue<string> stringQueue = { "one", "two", "three", "four", "five" };

    try {
        cout << "Первый элемент очереди int: " << intQueue.getFront() << endl;
        cout << "Последний элемент очереди int: " << intQueue.getBack() << endl;
        cout << "Первый элемент очереди double: " << doubleQueue.getFront() << endl;
        cout << "Последний элемент очереди double: " << doubleQueue.getBack() << endl;
        cout << "Первый элемент очереди string: " << stringQueue.getFront() << endl;
        cout << "Последний элемент очереди string: " << stringQueue.getBack() << endl;

        cout << "Удален из очереди int: " << intQueue.dequeue() << endl;
        cout << "Удален из очереди double: " << doubleQueue.dequeue() << endl;
        cout << "Удален из очереди string: " << stringQueue.dequeue() << endl;
    }
    catch (const CustomException& e) {
        cout << "Исключение при удалении элемента: " << e.what() << endl;
    }
  
    try {
        PositiveIterator<int> posIter(intQueue);
        NegativeIterator<int> negIter(intQueue);

        int positiveInts[10];
        int negativeInts[10];
        int posIndex = 0;
        int negIndex = 0;

        while (posIter.hasNext()) {
            positiveInts[posIndex++] = posIter.next();
        }

        while (negIter.hasNext()) {
            negativeInts[negIndex++] = negIter.next();
        }

        cout << "Положительные элементы очереди int: ";
        for (int i = 0; i < posIndex; ++i) {
            cout << positiveInts[i] << " ";
        }
        cout << endl;

        cout << "Отрицательные элементы очереди int: ";
        for (int i = 0; i < negIndex; ++i) {
            cout << negativeInts[i] << " ";
        }
        cout << endl;
    }
    catch (const CustomException& e) {
        cout << "Исключение при итерации: " << e.what() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    testQueue();

    Queue<double> myQueue;
    myQueue.enqueue(3.14);
    myQueue.enqueue(2.71);
    myQueue.enqueue(2.42);
    myQueue.enqueue(-1.23);
    myQueue.enqueue(-4.56);

    try {
        cout << "Первый в очереди: " << myQueue.getFront() << endl;
        cout << "Последний в очереди: " << myQueue.getBack() << endl;

        cout << "Удален из очереди double: " << myQueue.dequeue() << endl;

        PositiveIterator<double> posDoubleIter(myQueue);
        NegativeIterator<double> negDoubleIter(myQueue);

        double positiveDoubles[10];
        double negativeDoubles[10];
        int posDoubleIndex = 0;
        int negDoubleIndex = 0;

        while (posDoubleIter.hasNext()) {
            positiveDoubles[posDoubleIndex++] = posDoubleIter.next();
        }

        while (negDoubleIter.hasNext()) {
            negativeDoubles[negDoubleIndex++] = negDoubleIter.next();
        }

        cout << "Положительные элементы очереди double: ";
        for (int i = 0; i < posDoubleIndex; ++i) {
            cout << positiveDoubles[i] << " ";
        }
        cout << endl;

        cout << "Отрицательные элементы очереди double: ";
        for (int i = 0; i < negDoubleIndex; ++i) {
            cout << negativeDoubles[i] << " ";
        }
        cout << endl;
    }
    catch (const CustomException& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    return 0;
}
