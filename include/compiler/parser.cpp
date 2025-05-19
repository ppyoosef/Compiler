#include "compiler/parser.h"
#include <stdexcept>

static size_t index = 0;
static std::vector<Token> toks;

static Token peek() { return toks[index]; }
static Token advance() { return toks[index++]; }
static bool match(const std::string& s) { if (peek().lexeme == s) { advance(); return true; } return false; }

static ASTNode* parse_expression();

static ASTNode* parse_primary() {
    if (peek().type == Token::NUMBER) {
        auto val = advance();
        return new ASTNode{ASTNode::NUMBER_LITERAL, val.lexeme};
    } else if (peek().type == Token::IDENTIFIER) {
        auto val = advance();
        return new ASTNode{ASTNode::VAR_REFERENCE, "", val.lexeme};
    }
    throw std::runtime_error("Unexpected token: " + peek().lexeme);
}

static ASTNode* parse_term() {
    ASTNode* left = parse_primary();
    while (match("*") || match("/")) {
        std::string op = toks[index - 1].lexeme;
        ASTNode* right = parse_primary();
        auto node = new ASTNode{ASTNode::BINARY_EXPR, op};
        node->left = left;
        node->right = right;
        left = node;
    }
    return left;
}

static ASTNode* parse_expression() {
    ASTNode* left = parse_term();
    while (match("+") || match("-")) {
        std::string op = toks[index - 1].lexeme;
        ASTNode* right = parse_term();
        auto node = new ASTNode{ASTNode::BINARY_EXPR, op};
        node->left = left;
        node->right = right;
        left = node;
    }
    return left;
}

std::vector<ASTNode*> parse(const std::vector<Token>& tokens) {
    toks = tokens;
    index = 0;
    std::vector<ASTNode*> nodes;
    while (peek().type != Token::END) {
        if (match("let")) {
            auto name = advance();
            match("=");
            ASTNode* expr = parse_expression();
            auto node = new ASTNode{ASTNode::VAR_DECL, "", name.lexeme, expr};
            nodes.push_back(node);
        } else if (match("print")) {
            ASTNode* expr = parse_expression();
            auto node = new ASTNode{ASTNode::PRINT};
            node->left = expr;
            nodes.push_back(node);
        } else if (match("input")) {
            auto name = advance();
            auto node = new ASTNode{ASTNode::INPUT, "", name.lexeme};
            nodes.push_back(node);
        } else {
            throw std::runtime_error("Unexpected token at start of statement: " + peek().lexeme);
        }
    }
    return nodes;
}
