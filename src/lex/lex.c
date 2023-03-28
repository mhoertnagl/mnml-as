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

void next_chr(Lexer *lexer)
{
  lexer->chr = getc(lexer->input);
  lexer->col++;
}

Lexer *new_lexer(FILE *input)
{
  Lexer *lexer = malloc(sizeof(Lexer));
  lexer->input = input;
  lexer->line = 1;
  lexer->col = 0;
  // Read the first character. This is required
  // to jump-start the scanning process.
  next_chr(lexer);
  return lexer;
}

void free_lexer(Lexer *lexer)
{
  free(lexer);
}

void skip_space(Lexer *lexer)
{
  while (lexer->chr != EOF && isspace(lexer->chr))
  {
    if (lexer->chr == '\n')
    {
      lexer->line++;
      lexer->col = 0;
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
  if (lexer->chr == EOF)
  {
    // Rewind to enable repeated scanning
    // of the input file.
    rewind(lexer->input);
    // We need to read the next token, or else
    // the current character will remain EOF.
    next_chr(lexer);
    return EOF;
  }

  if (isspace(lexer->chr))
  {
    skip_space(lexer);
  }

  // TODO: Support for comments.

  u8 type = TOK_OP;

  switch (lexer->chr)
  {
  case '@':
    type = TOK_LABEL;
    break;
  case '&':
    type = TOK_REF;
    break;
  case '0' ... '9':
    type = TOK_NUM;
    break;
  }

  lexer->token.type = type;
  lexer->token.line = lexer->line;
  lexer->token.col = lexer->col;

  read_text(lexer);
  return 0;
}
