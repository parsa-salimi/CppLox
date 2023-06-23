#include "value.h"

void ValueArray::writeValueArray(Value value) {
    values.push_back(value);
}

void printValue(Value value) {
    std::cout << "'" << value << "'";
}

void ValueArray::printValueArray(int index) {
    printValue(values[index]);
}
