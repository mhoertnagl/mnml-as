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

#pragma once

#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef uint64_t u64;

#define MAX_LINE_LEN 256
#define MAX_TEXT_LEN 256

#define TOK_OP 0
#define TOK_NUM 1
#define TOK_REF 2
#define TOK_LABEL 3

typedef struct {
  u8 type;
  u64 line;
  u64 col;
  char text[MAX_TEXT_LEN];
} Token;

typedef struct {
  FILE *input;
  char chr;
  u64 line;
  u64 col;
} Lexer;

extern Token token;
extern Lexer lexer;

void lexer_reset();

int lexer_next_token();
