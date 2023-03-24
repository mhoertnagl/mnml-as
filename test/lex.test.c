#include <stdio.h>
#include <stdlib.h>
#include "utils/mu.h"
#include "../src/lex/lex.h"

mu_unit({
  test("Test source scanning files/01.as", {
    FILE *fp = fopen("./test/files/01.as", "r");

    if (fp == NULL)
    {
      fail("No such file!\n");
      return;
    }

    Lexer *lexer = new_lexer(fp);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "psh");
    assert(lexer->token.line == 1, "token line should be [%d]", 1);
    assert(lexer->token.col == 4, "token column should be [%d]", 4);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "pop");
    assert(lexer->token.line == 2, "token line should be [%d]", 2);
    assert(lexer->token.col == 4, "token column should be [%d]", 4);

    // TODO: continue with tests here.

    free_lexer(lexer);
  });
})
