#pragma once
#include <vector>
#include <string>
#include "tokenizer.h"

struct ASTNode {
    enum Type {
        PRINT, VAR_DECL, BINARY_EXPR, NUMBER_LITERAL, VAR_REFERENCE, INPUT
    } type;
    std::string value;
    std::string name;
    ASTNode* left = nullptr;
    ASTNode* right = nullptr;
};

std::vector<ASTNode*> parse(const std::vector<Token>& tokens);
