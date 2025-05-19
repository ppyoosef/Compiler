#include "tokenizer.h"
#include <cctype>

std::vector<Token> tokenize(const std::string& src) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < src.size()) {
        if (isspace(src[i])) {
            ++i;
        } else if (isalpha(src[i])) {
            size_t start = i;
            while (isalnum(src[i])) ++i;
            std::string word = src.substr(start, i - start);
            if (word == "let" || word == "print")
                tokens.push_back({Token::KEYWORD, word});
            else
                tokens.push_back({Token::IDENTIFIER, word});
        } else if (isdigit(src[i])) {
            size_t start = i;
            while (isdigit(src[i])) ++i;
            tokens.push_back({Token::NUMBER, src.substr(start, i - start)});
        } else {
            tokens.push_back({Token::SYMBOL, std::string(1, src[i++])});
        }
    }
    tokens.push_back({Token::END, ""});
    return tokens;
}