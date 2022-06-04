#pragma once
#include <iostream>

class Exception: public std::exception {

public:
    Exception(const char* what): mWhat(what) { }

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return mWhat;
    }

protected:
    const char* mWhat;
};