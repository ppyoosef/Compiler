#pragma once
#include <vector>
#include <string>

struct Token {
    enum Type {
        IDENTIFIER, NUMBER, KEYWORD, SYMBOL, END
    } type;
    std::string lexeme;
};

std::vector<Token> tokenize(const std::string& source);