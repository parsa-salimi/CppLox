#include "common.h"
#include "vm.h"
#include <functional>


VMStack::VMStack() {
    stackTop = stack.data();
}

void VMStack::push(Value value) {
    *stackTop = value;
    stackTop++;
}

void VMStack::printStack() {
    for (Value value : stack) {
        std::cout << "[ ";
        printValue(value);
        std::cout << " ]";
    }
    std::cout << "stackTop:  " <<  *stackTop;
    std::cout << std::endl;
}

Value VMStack::pop() {
    stackTop--;
    return *stackTop;
}

InterpretResult VM::interpret(Chunk *chunk) {
    this->chunk = chunk;
    ip = chunk->code.data();
    return run();
}


/*To make more efficient: direct threaded code, jump table, computed goto */
InterpretResult VM::run() {
#define READ_BYTE() (*ip++)
#define READ_CONSTANT() (chunk->constants.values[READ_BYTE()])

for(;;) {
    uint8_t instruction;
    #ifdef DEBUG_TRACE_EXECUTION
        std::cout << "         ";
        this->stack.printStack();
        chunk->disassembleInstruction((int)(ip - chunk->code.data()));
    #endif
    switch (instruction = READ_BYTE()) {
        case OP_RETURN: {
            printValue(stack.pop());
            std::cout << std::endl;
            return INTERPRET_OK;
        }
        case OP_CONSTANT_LONG: {
            int constant = 0;
            constant |= READ_BYTE();
            constant |= READ_BYTE() << 8;
            constant |= READ_BYTE() << 16;
            Value value = chunk->constants.values[constant];
            stack.push(value);
            break;
        }
        case OP_CONSTANT: {
            uint8_t constant = READ_BYTE();
            Value value = chunk->constants.values[constant];
            stack.push(value);
            break;
        }


        case OP_NEGATE: {
            stack.push(-stack.pop());
            break;
        }

        case OP_ADD: {
            binary_op(std::plus<double>(), "+");
            break;
        }

        case OP_SUBTRACT: {
            binary_op(std::minus<double>(), "-");
            break;
        }

        case OP_MULTIPLY: {
            binary_op(std::multiplies<double>(), "*");
            break;
        }

        case OP_DIVIDE: {
            binary_op(std::divides<double>(), "/");
            break;
        }

    }

}
#undef READ_BYTE
}
