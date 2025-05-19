#include "vm/vm.h"
#include "bytecode.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

bool run_bytecode(const std::string& bytecodePath) {
    std::ifstream in(bytecodePath, std::ios::binary);
    if (!in) return false;

    std::vector<uint8_t> code((std::istreambuf_iterator<char>(in)), {});
    std::vector<int> stack;
    int vars[256] = {0};
    size_t ip = 0;

    while (ip < code.size()) {
        auto op = static_cast<OpCode>(code[ip++]);
        switch (op) {
            case OpCode::OP_CONSTANT:
                stack.push_back(code[ip++]);
                break;
            case OpCode::OP_ADD:
            case OpCode::OP_SUB:
            case OpCode::OP_MUL:
            case OpCode::OP_DIV: {
                int b = stack.back(); stack.pop_back();
                int a = stack.back(); stack.pop_back();
                if (op == OpCode::OP_ADD) stack.push_back(a + b);
                else if (op == OpCode::OP_SUB) stack.push_back(a - b);
                else if (op == OpCode::OP_MUL) stack.push_back(a * b);
                else if (op == OpCode::OP_DIV) stack.push_back(a / b);
                break;
            }
            case OpCode::OP_PRINT:
                std::cout << stack.back() << std::endl;
                stack.pop_back();
                break;
            case OpCode::OP_STORE_VAR:
                vars[code[ip++]] = stack.back();
                stack.pop_back();
                break;
            case OpCode::OP_LOAD_VAR:
                stack.push_back(vars[code[ip++]]);
                break;
            case OpCode::OP_HALT:
                return true;
            case OpCode::OP_INPUT: {
                int index = code[ip++];
                int val;
                std::cout << "Input: ";
                std::cin >> val;
                vars[index] = val;
                break;
            }
        }
    }
    return true;
}
