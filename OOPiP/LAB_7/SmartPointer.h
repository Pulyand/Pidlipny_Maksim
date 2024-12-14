#ifndef SMARTPOINTER_H
#define SMARTDOINTER_H

#include <memory>

template<typename T>
using SmartPointer = std::shared_ptr<T>;

#endif
