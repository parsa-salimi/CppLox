#include "chunk.h"
#include <iostream>
#include <iomanip>

void Chunk::writeChunk(uint8_t byte, int line) {
    code.push_back(byte);
    lines.push_back(line);
}

void Chunk::disassembleChunk(const char* name) {
    std::cout << "==" << name << "==" << std::endl;

    for (int offset = 0; offset < code.size();) {
        offset = disassembleInstruction(offset);
    }
}

int Chunk::addConstant(Value value) {
    constants.writeValueArray(value);
    return constants.values.size() - 1;
}

void Chunk::writeConstant(Value value, int line) {
    int constant = addConstant(value);
    if (constant <= UINT8_MAX) {
        writeChunk(OP_CONSTANT, line);
        writeChunk(constant, line);
        return;
    }
    writeChunk(OP_CONSTANT_LONG, line);
    // write 3 chunks, each for the nth byte constant, unsigned
    // 8 bits, 1 byte
    writeChunk((constant >> 0) & 0xff, line);
    writeChunk((constant >> 8) & 0xff, line);
    writeChunk((constant >> 16) & 0xff, line);
}

int Chunk::simpleInstruction(std::string name, int offset) {
    std::cout << name << std::endl;
    return offset + 1;
}

int Chunk::constantInstruction(std::string name, int offset) {
    uint8_t constant = code[offset + 1];
    std::cout << std::setfill(' ') << std::left <<  std::setfill(' ') << std::setw(16) << name;
    std::cout << std::setfill(' ') << std::right << std::setw(4)  << (int)constant << " ";
    constants.printValueArray(constant);
    std::cout << std::endl;
    return offset + 2;
}

int Chunk::longConstantInstruction(std::string name, int offset) {
    uint8_t constant1 = code[offset + 1];
    uint8_t constant2 = code[offset + 2];
    uint8_t constant3 = code[offset + 3];
    int constant = constant1 | (constant2 << 8) | (constant3 << 16);
    std::cout << std::left << std::setfill(' ') <<  std::setw(16) << name;
    std::cout << std::right << std::setfill(' ') << std::setw(4) << constant << " ";
    constants.printValueArray(constant);
    std::cout << std::endl;
    return offset + 4;
}

int Chunk::disassembleInstruction(int offset) {
    std::cout << std::setfill('0') << std::setw(4) << offset << " ";
    if (offset > 0 && lines[offset] == lines[offset - 1]) {
        std::cout << "   | ";
    } else {
        std::cout << std::setfill(' ') << std::setw(4) << lines[offset] << " ";
    }


    uint8_t instruction = code[offset];
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", offset);
        case OP_CONSTANT_LONG:
            return longConstantInstruction("OP_CONSTANT_LONG", offset);
        default:
            std::cout << "Unknown opcode " << instruction << std::endl;
            return offset + 1;
    }
}
