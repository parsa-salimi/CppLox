#include "chunk.h"
#include "vm.h"


int main(int argc, char* argv[]) {
    Chunk chunk;
    VM vm;
    if(argc == 1) {
        repl();
    }
    else if (argc == 2) {
        runFile(argv[1]);
    }
    else {
        std::cerr << "Usage: clox [path]" << std::endl;
        exit(64);
    }
    return 0;
}
