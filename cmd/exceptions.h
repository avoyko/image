#ifndef CPP_HSE_EXCEPTIONS_H
#define CPP_HSE_EXCEPTIONS_H

#include "exception"
#include <string>

class Exception : public std::exception {
    std::string message_;

public:
    explicit Exception(const std::string text) : message_(text) {
    }

    const char* what() const noexcept override {
        return message_.c_str();
    }
};

#endif  // CPP_HSE_EXCEPTIONS_H
