#include "include/compiler/compiler.h"
#include "include/vm/vm.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: mylang <source.my>\n";
        return 1;
    }

    std::string source = argv[1];
    std::string bytecode = "out.mybc";

    if (!compile_source_to_bytecode(source, bytecode)) {
        std::cerr << "Compilation failed.\n";
        return 1;
    }

    if (!run_bytecode(bytecode)) {
        std::cerr << "Execution failed.\n";
        return 1;
    }

    return 0;
}