#include <stdio.h>
#include <stdlib.h>
#include "utils/mu.h"
#include "../src/as/as.h"

mu_unit({
  test("Test assembly of files/02.as", {
    FILE *src_fp = fopen("./test/files/02.as", "r");
    FILE *bin_fp = fopen("./test/files/02.vm", "wb");

    if (src_fp == NULL)
    {
      fail("Could not open input file!\n");
      return 0;
    }

    if (bin_fp == NULL)
    {
      fail("Could not open output file!\n");
      return 0;
    }

    Assembler *assembler = new_assembler(src_fp, bin_fp);

    assembler_run(assembler);

    free_assembler(assembler);
    fclose(src_fp);
    fclose(bin_fp);
    // Lexer *lexer = new_lexer(fp);

    // next_token(lexer);
    // assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    // assert_str_equal(lexer->token.text, "psh");
    // assert_int_equal((int)lexer->token.line, 1);
    // assert_int_equal((int)lexer->token.col, 3);

    // next_token(lexer);
    // assert(lexer->token.type == TOK_NUM, "token type should be [%d]", TOK_NUM);
    // assert_str_equal(lexer->token.text, "0x1234");
    // assert_int_equal((int)lexer->token.line, 1);
    // assert_int_equal((int)lexer->token.col, 7);

    // next_token(lexer);
    // assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    // assert_str_equal(lexer->token.text, "dup");
    // assert_int_equal((int)lexer->token.line, 2);
    // assert_int_equal((int)lexer->token.col, 3);

    // next_token(lexer);
    // assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    // assert_str_equal(lexer->token.text, "add");
    // assert_int_equal((int)lexer->token.line, 3);
    // assert_int_equal((int)lexer->token.col, 3);

    // next_token(lexer);
    // assert(lexer->token.type == TOK_LABEL, "token type should be [%d]", TOK_LABEL);
    // assert_str_equal(lexer->token.text, "@loop");
    // assert_int_equal((int)lexer->token.line, 4);
    // assert_int_equal((int)lexer->token.col, 1);

    // next_token(lexer);
    // assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    // assert_str_equal(lexer->token.text, "psh");
    // assert_int_equal((int)lexer->token.line, 5);
    // assert_int_equal((int)lexer->token.col, 3);

    // next_token(lexer);
    // assert(lexer->token.type == TOK_REF, "token type should be [%d]", TOK_REF);
    // assert_str_equal(lexer->token.text, "&loop");
    // assert_int_equal((int)lexer->token.line, 5);
    // assert_int_equal((int)lexer->token.col, 7);

    // next_token(lexer);
    // assert(lexer->token.type == TOK_OP, "token type should be [%d]", TOK_OP);
    // assert_str_equal(lexer->token.text, "jmp");
    // assert_int_equal((int)lexer->token.line, 6);
    // assert_int_equal((int)lexer->token.col, 3);

    // free_lexer(lexer);
  });
})
