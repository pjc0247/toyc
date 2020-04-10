#pragma once

#include <map>
#include <vector>
#include <stack>

enum class token_type {
    space,
    op,
    number,
    string
};

struct token {
    std::string raw;
    token_type type;
};

static std::map<std::string, token_type> tokens = {
    { " ", token_type::space },
    { "+", token_type::op },
    { "-", token_type::op },
    { "*", token_type::op },
    { "/", token_type::op },
};

token parse_single(const std::string& src) {
    if (src.length() > 2 &&
        src[0] == '\"' && src[src.length() - 1] == '\"') {
        return { src, token_type::string };
    }
    return { src, token_type::number };
}
std::vector<token> parse(const std::string& src) {
    std::vector<token> result;

    auto last_offset = 0;

    auto push_token = [&result](const std::string& token, token_type type) {
        if (type == token_type::space) return;

        result.push_back({ token, type });
    };
    auto flush = [src, &result, &last_offset](int until) {
        if (until - last_offset == 0) goto advance;

        result.push_back(
            parse_single(
                src.substr(last_offset, until - last_offset)));

    advance:
        last_offset = until + 1;
    };

    for (int i = 0; i < src.length(); i++) {
        auto candidate = src.substr(i, 1);
        auto it = tokens.find(candidate);

        if (it != tokens.end()) {
            flush(i);
            push_token(candidate, it->second);
        }
    }
    flush(src.length());

    return result;
}
