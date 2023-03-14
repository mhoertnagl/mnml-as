// mnml-as - Assembler for the mnml-vm virtual stack machine.
// Copyright (C) 2023  Mathias Hörtnagl <mathias.hoertnagl[ÄT]gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// https://www.w3.org/People/Raggett/tidy/lexer.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils/types.h"
#include "utils/errio.h"
#include "lex.h"

#define MAX_LINE_LEN 256

Lexer *new_lexer(FILE *input)
{
  Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
  lexer->input = input;
  lexer->token.line = 1;
  lexer->token.col = 0;
  return lexer;
}

void free_lexer(Lexer *lexer)
{
  free(lexer);
}

void next_chr(Lexer *lexer)
{
  lexer->chr = getc(lexer->input);
  lexer->token.col++;
}

void skip_space(Lexer *lexer)
{
  while (lexer->chr != EOF && isspace(lexer->chr))
  {
    if (lexer->chr == '\n')
    {
      lexer->token.line++;
      lexer->token.col = 0;
    }
    next_chr(lexer);
  }
}

void read_text(Lexer *lexer)
{
  u32 p = 0;
  while (lexer->chr != EOF && !isspace(lexer->chr))
  {
    lexer->token.text[p++] = lexer->chr;
    next_chr(lexer);
  }
  lexer->token.text[p] = '\0';
}

i8 next_token(Lexer *lexer)
{
  next_chr(lexer);

  if (lexer->chr == EOF)
  {
    // Rewind to enable repeated
    // scanning of the input file.
    rewind(lexer->input);
    return EOF;
  }

  if (isspace(lexer->chr))
  {
    skip_space(lexer);
  }

  if (lexer->chr == '@')
  {
    lexer->token.type = TOK_LABEL;
    read_text(lexer);
    printf(
        "%lu:%lu Found label: [%s]\n",
        lexer->token.line,
        lexer->token.col,
        lexer->token.text);
  }
  else if (lexer->chr == '&')
  {
    lexer->token.type = TOK_REF;
    read_text(lexer);
    printf(
        "%lu:%lu Found reference: [%s]\n",
        lexer->token.line,
        lexer->token.col,
        lexer->token.text);
  }
  else if (isdigit(lexer->chr))
  {
    lexer->token.type = TOK_NUM;
    read_text(lexer);
    printf(
        "%lu:%lu Found number: [%s]\n",
        lexer->token.line,
        lexer->token.col,
        lexer->token.text);
  }
  else
  {
    lexer->token.type = TOK_OP;
    read_text(lexer);
    printf(
        "%lu:%lu Found keyword: [%s]\n",
        lexer->token.line,
        lexer->token.col,
        lexer->token.text);
  }
  return 0;
}
