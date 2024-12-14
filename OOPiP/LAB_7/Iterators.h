#ifndef ITERATORS_H
#define ITERATORS_H

#include "Queue.h"
#include "CustomException.h"

template<typename T>
class PositiveIterator {
public:
    PositiveIterator(const Queue<T>& queue) : queue(queue), index(0) {
        findNextPositive();
    }

    bool hasNext() const {
        return index < queue.getSize();
    }

    T next() {
        if (!hasNext()) {
            throw CustomException("Нет больше положительных элементов!");
        }
        T value = queue[index];
        ++index;
        findNextPositive();
        return value;
    }

private:
    const Queue<T>& queue;
    size_t index;

    void findNextPositive() {
        while (index < queue.getSize() && queue[index] <= 0) {
            ++index;
        }
    }
};

template<typename T>
class NegativeIterator {
public:
    NegativeIterator(const Queue<T>& queue) : queue(queue), index(0) {
        findNextNegative();
    }

    bool hasNext() const {
        return index < queue.getSize();
    }

    T next() {
        if (!hasNext()) {
            throw CustomException("Нет больше отрицательных элементов!");
        }
        T value = queue[index];
        ++index;
        findNextNegative();
        return value;
    }

private:
    const Queue<T>& queue;
    size_t index;

    void findNextNegative() {
        while (index < queue.getSize() && queue[index] >= 0) {
            ++index;
        }
    }
};

#endif
