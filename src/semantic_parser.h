#pragma once

#include <vector>

#include "lexer.h"

enum class stoken_type {
    op,
    literal
};
struct stoken {
    token token;
    stoken_type type;
};

std::vector<stoken> stransform(const std::vector<token>& tokens) {
    std::vector<stoken> result;
    std::stack<std::pair<token, stoken_type>> stack;

    auto flush = [&stack, &result]() {
        while (!stack.empty()) {
            auto& top = stack.top();

            result.push_back({ top.first, top.second });

            stack.pop();
        }
    };

    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        auto& t = *it;

        if (t.type == token_type::op) {
            stack.push({ t, stoken_type::op });
        }
        else if (t.type == token_type::number) {
            result.push_back({ t, stoken_type::literal });
        }
    }

    flush();

    // postfix -> prefix
    std::reverse(result.begin(), result.end());
    return result;
}
