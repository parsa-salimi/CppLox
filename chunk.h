#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"
#include "value.h"
#include <vector>



enum OpCode {   OP_RETURN,
                OP_CONSTANT_LONG,
                OP_NEGATE,
                OP_CONSTANT,
                OP_ADD,
                OP_SUBTRACT,
                OP_MULTIPLY,
                OP_DIVIDE,
                 };

struct Chunk {
    std::vector<uint8_t> code;
    std::vector<int> lines;
    ValueArray constants;


    void writeChunk(uint8_t byte, int line);
    int addConstant(Value value);
    void writeConstant(Value value, int line);

    int simpleInstruction(std::string name, int offset);
    int constantInstruction(std::string name, int offset);
    int longConstantInstruction(std::string name, int offset);

    void disassembleChunk(const char* name);
    int disassembleInstruction(int offset);
};



#endif
