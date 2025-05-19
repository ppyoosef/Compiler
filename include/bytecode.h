#pragma once

enum class OpCode {
    OP_CONSTANT,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_PRINT,
    OP_STORE_VAR,
    OP_LOAD_VAR,
    OP_HALT,
    OP_INPUT,
};
