#include "compiler/compiler.h"
#include "tokenizer.h"
#include "parser.h"
#include "emitter.h"
#include <fstream>

bool compile_source_to_bytecode(const std::string &sourcePath, const std::string &outBytecodePath) {
    std::ifstream in(sourcePath);
    if (!in) return false;
    std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    auto tokens = tokenize(src);
    auto ast = parse(tokens);
    auto bytecode = emit_bytecode(ast);

    std::ofstream out(outBytecodePath, std::ios::binary);
    if (!out) return false;
    out.write(reinterpret_cast<const char*>(bytecode.data()), bytecode.size());
    return true;
}