#ifndef QUEUE_H
#define QUEUE_H

#include "Vect.h"
#include "SmartPointer.h"
#include "CustomException.h"
#include <initializer_list>
#include <stdexcept>
#include <string>

template<typename T>
class Queue {
public:
    Queue();
    Queue(std::initializer_list<T> initList);
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;
    ~Queue(); 

    void enqueue(T value);
    T dequeue();
    bool isEmpty() const;
    T getFront() const;
    T getBack() const;
    size_t getSize() const;

private:
    Vect<T> vect;
    size_t size;
};

template<typename T>
Queue<T>::Queue() : size(0) {}

template<typename T>
Queue<T>::Queue(std::initializer_list<T> initList) : Queue() {
    for (const auto& item : initList) {
        enqueue(item);
    }
}

template<typename T>
Queue<T>::Queue(const Queue& other) : vect(other.vect), size(other.size) {}

template<typename T>
Queue<T>::Queue(Queue&& other) noexcept : vect(std::move(other.vect)), size(other.size) {
    other.size = 0;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        vect = other.vect;
        size = other.size;
    }
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
    if (this != &other) {
        vect = std::move(other.vect);
        size = other.size;
        other.size = 0;
    }
    return *this;
}

template<typename T>
Queue<T>::~Queue() {}

template<typename T>
void Queue<T>::enqueue(T value) {
    vect.add(value);
    ++size;
}

template<typename T>
T Queue<T>::dequeue() {
    if (size == 0) {
        throw CustomException("Очередь пуста!");
    }
    T value = vect[0];
    for (size_t i = 1; i < size; ++i) {
        vect[i - 1] = vect[i];
    }
    --size;
    return value;
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
T Queue<T>::getFront() const {
    if (size == 0) {
        throw CustomException("Очередь пуста!");
    }
    return vect[0];
}

template<typename T>
T Queue<T>::getBack() const {
    if (size == 0) {
        throw CustomException("!");
    }
    return vect[size - 1];
}

template<typename T>
size_t Queue<T>::getSize() const {
    return size;
}

#endif
