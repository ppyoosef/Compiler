#include "compiler/emitter.h"
#include "bytecode.h"
#include <unordered_map>

static std::vector<uint8_t> code;
static std::unordered_map<std::string, size_t> variables;

static void emit(ASTNode* node) {
    switch (node->type) {
        case ASTNode::NUMBER_LITERAL:
            code.push_back(static_cast<uint8_t>(OpCode::OP_CONSTANT));
            code.push_back(static_cast<uint8_t>(std::stoi(node->value)));
            break;
        case ASTNode::VAR_REFERENCE:
            code.push_back(static_cast<uint8_t>(OpCode::OP_LOAD_VAR));
            code.push_back(variables[node->name]);
            break;
        case ASTNode::BINARY_EXPR:
            emit(node->left);
            emit(node->right);
            if (node->value == "+") code.push_back(static_cast<uint8_t>(OpCode::OP_ADD));
            else if (node->value == "-") code.push_back(static_cast<uint8_t>(OpCode::OP_SUB));
            else if (node->value == "*") code.push_back(static_cast<uint8_t>(OpCode::OP_MUL));
            else if (node->value == "/") code.push_back(static_cast<uint8_t>(OpCode::OP_DIV));
            break;
        case ASTNode::VAR_DECL:
            emit(node->left);
            variables[node->name] = variables.size();
            code.push_back(static_cast<uint8_t>(OpCode::OP_STORE_VAR));
            code.push_back(variables[node->name]);
            break;
        case ASTNode::PRINT:
            emit(node->left);
            code.push_back(static_cast<uint8_t>(OpCode::OP_PRINT));
            break;
        case ASTNode::INPUT:
            variables[node->name] = variables.size();
            code.push_back(static_cast<uint8_t>(OpCode::OP_INPUT));
            code.push_back(variables[node->name]);
            break;
        }
}

std::vector<uint8_t> emit_bytecode(const std::vector<ASTNode*>& ast) {
    code.clear();
    variables.clear();
    for (auto* node : ast) emit(node);
    code.push_back(static_cast<uint8_t>(OpCode::OP_HALT));
    return code;
}