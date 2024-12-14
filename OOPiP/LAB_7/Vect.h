#ifndef VECT_H
#define VECT_H

#include <stdexcept>
#include <cstddef>

template<typename T>
class Vect {
public:
    Vect();
    explicit Vect(std::size_t capacity);
    Vect(const Vect& other);
    Vect(Vect&& other) noexcept;
    Vect& operator=(const Vect& other);
    Vect& operator=(Vect&& other) noexcept;
    ~Vect();

    void add(const T& value);
    T get(std::size_t index) const;
    std::size_t size() const;
    std::size_t capacity() const;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

private:
    T* data;
    std::size_t _size;
    std::size_t _capacity;

    void resize(std::size_t newCapacity);
};

template<typename T>
Vect<T>::Vect() : data(nullptr), _size(0), _capacity(0) {}

template<typename T>
Vect<T>::Vect(std::size_t capacity) : data(new T[capacity]), _size(0), _capacity(capacity) {}

template<typename T>
Vect<T>::Vect(const Vect& other) : data(new T[other._capacity]), _size(other._size), _capacity(other._capacity) {
    for (std::size_t i = 0; i < _size; ++i) {
        data[i] = other.data[i];
    }
}

template<typename T>
Vect<T>::Vect(Vect&& other) noexcept : data(other.data), _size(other._size), _capacity(other._capacity) {
    other.data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template<typename T>
Vect<T>& Vect<T>::operator=(const Vect& other) {
    if (this != &other) {
        delete[] data;
        _size = other._size;
        _capacity = other._capacity;
        data = new T[_capacity];
        for (std::size_t i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
Vect<T>& Vect<T>::operator=(Vect&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        _size = other._size;
        _capacity = other._capacity;
        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

template<typename T>
Vect<T>::~Vect() {
    delete[] data;
}

template<typename T>
void Vect<T>::add(const T& value) {
    if (_size >= _capacity) {
        resize(_capacity == 0 ? 1 : _capacity * 2);
    }
    data[_size++] = value;
}

template<typename T>
T Vect<T>::get(std::size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data[index];
}

template<typename T>
std::size_t Vect<T>::size() const {
    return _size;
}

template<typename T>
std::size_t Vect<T>::capacity() const {
    return _capacity;
}

template<typename T>
void Vect<T>::resize(std::size_t newCapacity) {
    if (newCapacity < _size) {
        newCapacity = _size;
    }
    T* newData = new T[newCapacity];
    for (std::size_t i = 0; i < _size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    _capacity = newCapacity;
}

template<typename T>
T& Vect<T>::operator[](std::size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data[index];
}

template<typename T>
const T& Vect<T>::operator[](std::size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data[index];
}

#endif
