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

#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include "utils/types.h"

#define MAX_TEXT_LEN 256

#define TOK_OP 0
#define TOK_NUM 1
#define TOK_REF 2
#define TOK_LABEL 3

typedef struct
{
  // clang-format off
  u8   type;
  u32  line;
  u32  col;
  char text[MAX_TEXT_LEN];
  // clang-format on
} Token;

typedef struct
{
  // clang-format off
  FILE  *input;
  char  chr;
  Token token;
  // clang-format on
} Lexer;

Lexer *new_lexer(FILE *input);

void free_lexer(Lexer *lexer);

i8 next_token(Lexer *lexer);

#endif