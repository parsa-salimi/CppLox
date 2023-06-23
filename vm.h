#ifndef VM_H
#define VM_H
#define STACK_MAX 256

#include "chunk.h"
#include "value.h"
#define STACK_MAX 256
#include <array>
#include <stack>

enum InterpretResult {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
};

struct VMStack {
    VMStack();
    std::array<Value, STACK_MAX> stack;
    Value *stackTop;
    void push(Value value);
    void printStack();
    Value pop();
};

struct VM {
    Chunk* chunk;
    uint8_t* ip;
    VMStack stack;

    template <class Func>
    void binary_op(Func func, std::string op_name);

    InterpretResult interpret(Chunk *chunk);
    InterpretResult run();

};

template <class Func>
void VM::binary_op(Func func, std::string op_name) {
    double b = stack.pop();
    double a = stack.pop();
    stack.push(func(a, b));
    }



#endif
