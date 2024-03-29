#include <stdio.h>
#include <stdlib.h>
#include "utils/mu.h"
#include "../src/lex/lex.h"

mu_unit({
  test("Test lexer on files/01.as", {
    FILE *fp = fopen("./test/files/01.as", "r");

    if (fp == NULL)
    {
      fail("No such file!\n");
      return 0;
    }

    Lexer *lexer = new_lexer(fp);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "psh");
    assert_int_equal((int)lexer->token.line, 1);
    assert_int_equal((int)lexer->token.col, 3);

    next_token(lexer);
    assert(lexer->token.type == TOK_NUM, "token type should be [%d]", TOK_NUM);
    assert_str_equal(lexer->token.text, "0x1234");
    assert_int_equal((int)lexer->token.line, 1);
    assert_int_equal((int)lexer->token.col, 7);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "dup");
    assert_int_equal((int)lexer->token.line, 2);
    assert_int_equal((int)lexer->token.col, 3);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "add");
    assert_int_equal((int)lexer->token.line, 3);
    assert_int_equal((int)lexer->token.col, 3);

    next_token(lexer);
    assert(lexer->token.type == TOK_LABEL, "token type should be [%d]", TOK_LABEL);
    assert_str_equal(lexer->token.text, "@loop");
    assert_int_equal((int)lexer->token.line, 4);
    assert_int_equal((int)lexer->token.col, 1);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "psh");
    assert_int_equal((int)lexer->token.line, 5);
    assert_int_equal((int)lexer->token.col, 3);

    next_token(lexer);
    assert(lexer->token.type == TOK_REF, "token type should be [%d]", TOK_REF);
    assert_str_equal(lexer->token.text, "&loop");
    assert_int_equal((int)lexer->token.line, 5);
    assert_int_equal((int)lexer->token.col, 7);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "jmp");
    assert_int_equal((int)lexer->token.line, 6);
    assert_int_equal((int)lexer->token.col, 3);

    assert(next_token(lexer) == EOF, "lexer should be at the end");

    free_lexer(lexer);
  });

  test("Test lexer on files/03.as", {
    FILE *fp = fopen("./test/files/03.as", "r");

    if (fp == NULL)
    {
      fail("No such file!\n");
      return 0;
    }

    Lexer *lexer = new_lexer(fp);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "psh");
    assert_int_equal((int)lexer->token.line, 3);
    assert_int_equal((int)lexer->token.col, 3);

    next_token(lexer);
    assert(lexer->token.type == TOK_NUM, "token type should be [%d]", TOK_NUM);
    assert_str_equal(lexer->token.text, "0x1234");
    assert_int_equal((int)lexer->token.line, 3);
    assert_int_equal((int)lexer->token.col, 7);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "dup");
    assert_int_equal((int)lexer->token.line, 4);
    assert_int_equal((int)lexer->token.col, 3);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "add");
    assert_int_equal((int)lexer->token.line, 5);
    assert_int_equal((int)lexer->token.col, 3);

    next_token(lexer);
    assert(lexer->token.type == TOK_LABEL, "token type should be [%d]", TOK_LABEL);
    assert_str_equal(lexer->token.text, "@loop");
    assert_int_equal((int)lexer->token.line, 7);
    assert_int_equal((int)lexer->token.col, 1);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "psh");
    assert_int_equal((int)lexer->token.line, 8);
    assert_int_equal((int)lexer->token.col, 3);

    next_token(lexer);
    assert(lexer->token.type == TOK_REF, "token type should be [%d]", TOK_REF);
    assert_str_equal(lexer->token.text, "&loop");
    assert_int_equal((int)lexer->token.line, 8);
    assert_int_equal((int)lexer->token.col, 7);

    next_token(lexer);
    assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    assert_str_equal(lexer->token.text, "jmp");
    assert_int_equal((int)lexer->token.line, 10);
    assert_int_equal((int)lexer->token.col, 3);

    assert(next_token(lexer) == EOF, "lexer should be at the end");

    free_lexer(lexer);
  });
})
