#include <stdio.h>
#include <string>

#include "lexer.h"
#include "semantic_parser.h"

using namespace std;

int main()
{
    auto expr = "1 + 2 + 3";
    auto tokens = parse(expr);
    auto stokens = stransform(tokens);

    printf("\n\nlexed\n");
    for (auto& t : tokens)
        printf("|%s|\n", t.raw.c_str());

    printf("\n\stransformed\n");
    for (auto& n : stokens)
        printf("|%s|\n", n.token.raw.c_str());
}
