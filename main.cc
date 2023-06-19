#include "chunk.h"


int main() {
    Chunk chunk;
    for(int i = 0; i < 500; i++) {
        chunk.writeConstant(1.2, 123);
    }
    chunk.writeChunk(OP_RETURN, 123);
    chunk.disassembleChunk("test chunk");
    return 0;
}
