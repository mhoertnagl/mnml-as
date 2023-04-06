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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils/types.h"
#include "utils/errio.h"
#include "lex.h"

#define MAX_LINE_LEN 256

void next_chr(Lexer *lex)
{
  lex->chr = getc(lex->input);
  lex->col++;
}

i8 reset_lexer(Lexer *lex)
{
  rewind(lex->input);
  lex->line = 1;
  lex->col = 0;
  // Read the first character. This is required
  // to jump-start the scanning process.
  next_chr(lex);
  return EOF;
}

Lexer *new_lexer(FILE *input)
{
  Lexer *lex = malloc(sizeof(Lexer));
  lex->input = input;
  reset_lexer(lex);
  return lex;
}

void free_lexer(Lexer *lex)
{
  free(lex);
}

void skip_space(Lexer *lex)
{
  while (lex->chr != EOF && isspace(lex->chr))
  {
    if (lex->chr == '\n')
    {
      lex->line++;
      lex->col = 0;
    }
    next_chr(lex);
  }
}

void skip_comment(Lexer *lex)
{
  if (lex->chr == '#')
  {
    while (lex->chr != EOF && lex->chr != '\n')
    {
      next_chr(lex);
    }
  }
}

void read_text(Lexer *lex)
{
  u32 p = 0;
  while (lex->chr != EOF && !isspace(lex->chr))
  {
    lex->token.text[p++] = lex->chr;
    next_chr(lex);
  }
  lex->token.text[p] = '\0';
}

i8 next_token(Lexer *lex)
{
  if (lex->chr == EOF)
  {
    return reset_lexer(lex);
  }

  while (isspace(lex->chr) || lex->chr == '#')
  {
    skip_comment(lex);
    skip_space(lex);
  }

  u8 type = TOK_OP;
  switch (lex->chr)
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

  lex->token.type = type;
  lex->token.line = lex->line;
  lex->token.col = lex->col;
  read_text(lex);
  return 0;
}
