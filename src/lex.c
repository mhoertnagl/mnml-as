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

#include "lex.h"
#include <ctype.h>
#include <stdio.h>

Token token;
Lexer lexer;

static void next() {
  lexer.chr = getc(lexer.input);
  lexer.col++;
}

void lexer_reset() {
  rewind(lexer.input);
  lexer.line = 1;
  lexer.col = 0;
  next();
}

static void skip_space() {
  while (lexer.chr != EOF && isspace(lexer.chr)) {
    if (lexer.chr == '\n') {
      lexer.line++;
      lexer.col = 0;
    }
    next();
  }
}

static void skip_comment() {
  if (lexer.chr == '#') {
    while (lexer.chr != EOF && lexer.chr != '\n') {
      next();
    }
  }
}

static void read_word() {
  int p = 0;
  while (lexer.chr != EOF && !isspace(lexer.chr)) {
    token.text[p++] = lexer.chr;
    next();
  }
  token.text[p] = '\0';
}

static void set_token(u8 type) {
  token.type = type;
  token.line = lexer.line;
  token.col = lexer.col;
  read_word();
}

int lexer_next_token() {
  if (lexer.chr == EOF) {
    return EOF;
  }

  while (isspace(lexer.chr) || lexer.chr == '#') {
    skip_comment();
    skip_space();
  }

  u8 type = TOK_OP;
  switch (lexer.chr) {
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

  set_token(type);
  return 0;
}
