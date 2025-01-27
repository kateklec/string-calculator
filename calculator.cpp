#include "calculator.h"

bool Calculator::maths(StackList<OperOrNum>& stack_nums, StackList<OperOrNum>& stack_oper, OperOrNum& item) {
    double b, a, c;
    a = stack_nums.top().value;
    stack_nums.pop();

    if (stack_oper.top().type != '_') {
        if (stack_nums.empty()) {
            throw std::runtime_error("Insufficient data for operation!");
        }
        b = stack_nums.top().value;
        stack_nums.pop();
    }

    switch (stack_oper.top().type) {
    case '_': {
        c = -a;
        break;
    }
    case '+': { c = b + a; break; }
    case '-': { c = b - a; break; }
    case '*': { c = b * a; break; }
    case '/': {
        if (a == 0) {
            throw std::runtime_error("Division by 0!");
        }
        c = b / a;
        break; }
    case '^': {c = pow(b, a); break; }
    default: {
        throw std::runtime_error("Unknown operator!");
    }
    }

    item.type = '0';
    item.value = c;
    stack_nums.push(item);
    stack_oper.pop();
    return true;
}

bool Calculator::isStringEmpty(const char* str) {
    if (str == nullptr || *str == '\0') return true;

    while (*str) {
        if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r') {
            return false;
        }
        ++str;
    }
    return true;
}

double Calculator::strToDouble(const char* str, char** endPtr) {
    double res = 0.0;
    bool isNegative = false;
    bool hasDecimal = false;
    double decimalPart = 0.1;

    if (!str || !*str) {
        if (endPtr) *endPtr = customConstCast<char>(str);
        throw std::runtime_error("Empty string or null pointer provided.");
    }

    const char* start = str;

    if (*str == '-') {
        isNegative = true;
        ++str;
    }
    else if (*str == '+') {
        ++str;
    }

    while (*str >= '0' && *str <= '9') {
        res = res * 10 + (*str - '0');
        ++str;
    }

    if (*str == '.') {
        hasDecimal = true;
        ++str;
        while (*str >= '0' && *str <= '9') {
            res += (*str - '0') * decimalPart;
            decimalPart *= 0.1;
            ++str;
        }
    }

    if (endPtr) *endPtr = customConstCast<char>(str);

    if (str == start || (hasDecimal && str == start + 1)) {
        throw std::runtime_error("Unable to parse number from string.");
    }

    return isNegative ? -res : res;
}

int Calculator::getOperatorPriority(char ch) {
    if (ch == '^') return 4;
    if (ch == '_') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

double Calculator::calc(const char* str) throw(std::runtime_error) {

    if (isStringEmpty(str)) {
        throw std::runtime_error("Input string is empty.");
    }

    StackList<OperOrNum> stack_nums;
    StackList<OperOrNum> stack_oper;

    OperOrNum item;
    bool flag = 1;
    const char* start = str;

    while (*str != '\0') {

        char ch = *str;

        if (ch == ' ') {
            ++str;
            continue;
        }

        if (ch == '-' && (flag == 1 || str == start || *(str - 1) == '(' || *(str - 1) == '^')) {

            item.type = '_';
            item.value = 0;
            stack_oper.push(item);
            flag = 0;
            ++str;
            continue;
        }

        if ((ch >= '0' && ch <= '9') || (ch == '.')) {

            char* endPtr;
            double value = strToDouble(str, &endPtr);

            if (endPtr == str) {
                throw std::runtime_error("Unable to parse number from string.");
            }

            if (*str == '.') {
                const char* newStr = "0";
                char combinedStr[1024];

                combinedStr[0] = '0';

                int i = 1;
                while (*str) {
                    combinedStr[i++] = *str++;
                }
                combinedStr[i] = '\0';

                const char* endPtr;
                double value = strToDouble(combinedStr, customConstCast<char>(&endPtr));
            }

            item.type = '0';
            item.value = value;
            stack_nums.push(item);
            flag = 0;
            str = endPtr;
            continue;
        }

        if (ch == '+' || (ch == '-' && flag == 0) || ch == '*' || ch == '/' || ch == '^') {

            if (stack_oper.size() > 0 && stack_nums.size() == 0) {
                if (stack_oper.top().type == '+' || stack_oper.top().type == '-' || stack_oper.top().type == '*'
                    || stack_oper.top().type == '/' || stack_oper.top().type == '^' || stack_oper.top().type == '_') {
                    throw std::runtime_error("Consecutive operators (e.g., ++, --, +++) are not allowed.");
                }
            }

            if (stack_oper.size() == 0) {
                item.type = ch;
                item.value = 0;
                stack_oper.push(item);
                ++str;
                continue;

            }
            if (stack_oper.size() != 0 &&
                (getOperatorPriority(ch) > getOperatorPriority(stack_oper.top().type) ||
                    (ch == '^' && stack_oper.top().type == '^'))) {
                item.type = ch;
                item.value = 0;
                stack_oper.push(item);
                ++str;
                continue;
            }
            if (stack_oper.size() != 0 && getOperatorPriority(ch) <= getOperatorPriority(stack_oper.top().type)) {
                if (maths(stack_nums, stack_oper, item) == false) {
                    throw std::runtime_error("Error performing operation maths.");
                }
                continue;
            }
        }

        if (ch == '(') {
            item.type = ch;
            item.value = 0;
            stack_oper.push(item);
            ++str;
            continue;
        }

        if (ch == ')') {
            if (stack_nums.size() == 0) {
                throw std::runtime_error("Invalid expression.");
            }
            while (!stack_oper.empty() && stack_oper.top().type != '(') {
                if (maths(stack_nums, stack_oper, item) == false) {
                    throw std::runtime_error("Error performing operation maths.");
                }
            }
            if (!stack_oper.empty() && stack_oper.top().type == '(') {
                stack_oper.pop();
            }
            else {
                throw std::runtime_error("Mismatched parentheses.");
            }
            ++str;
            continue;
        }

        throw std::runtime_error("Invalid character in input.");
    }

    if ((stack_oper.size() != 0) && (stack_nums.size() == 0)) {
        throw std::runtime_error("Operator found, but no operands available.");
    }

    while (stack_oper.size() != 0) {
        if (maths(stack_nums, stack_oper, item) == false) {
            throw std::runtime_error("Error performing operation maths.");
        }
        else continue;
    }

    if (stack_nums.size() > 1) {
        throw std::runtime_error("Invalid expression.");
    }

    return stack_nums.top().value;
}