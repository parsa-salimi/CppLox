#ifndef VALUE_H
#define VALUE_H

#include "common.h"


typedef double Value;
struct ValueArray {
    std::vector<Value> values;

    void writeValueArray(Value value);
    void printValue(Value value);
    void printValueArray(int index);
};


#endif
