#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <stdexcept>
#include <string>

class CustomException : public std::exception {
private:
    std::string message_;
public:
    CustomException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

#endif
