#pragma once
#include <vector>
#include <string>
#include "parser.h"
#include <cstdint>

std::vector<uint8_t> emit_bytecode(const std::vector<ASTNode*>& ast);
