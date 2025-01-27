#pragma once

#include <exception>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "stack.h"

class Calculator {
public:
    double calc(const char* str) throw(std::runtime_error);

private:
    struct OperOrNum {
        char type;
        double value;
    };

    template <typename T>
    T* customConstCast(const T* ptr) {
        return (T*)(ptr);
    }

    template <typename T>
    T** customConstCast(const T** ptr) {
        return (T**)(ptr);
    }
    
    bool maths(StackList<OperOrNum>& stack_nums, StackList<OperOrNum>& stack_oper, OperOrNum& item);
    bool isStringEmpty(const char* str);
    double strToDouble(const char* str, char** endPtr);
    int getOperatorPriority(char ch);
};