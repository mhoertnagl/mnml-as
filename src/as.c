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

#include "as.h"
#include "lex.h"
#include "sym.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Assembler assembler;

// clang-format off
static const char keywords[][3] = {
  "psh", "dup", "ldw", "stw", "add", "sub", "mul", "div",
  "equ", "neq", "sgt", "sge", "slt", "sle", "jmp", "bra",
  "jal", "ret", "hlt"
};
// clang-format on

static u8 get_opcode(cstr keyword) {
  for (u64 i = 0; i < sizeof(keywords) / 3; i++) {
    if (strncmp(keyword, keywords[i], 3) == 0) {
      return i;
    }
  }
  return -1;
}

void write_u8(u8 val) {
  fwrite(&val, sizeof(u8), 1, assembler.output);
}

void write_u64(u64 val) {
  fwrite(&val, sizeof(u64), 1, assembler.output);
}

static void resolve() {
  u64 ip = 0;
  while (lexer_next_token() != EOF) {
    switch (token.type) {
    case TOK_OP:
      ip++;
      break;
    case TOK_NUM:
      ip += 2;
      break;
    case TOK_REF:
      ip += 2;
      break;
    case TOK_LABEL:
      // Add the label without the leading @ character.
      symbol_add(token.text + 1, ip);
      // ERROR: symbol already defined
      break;
    }
  }
}

static void encode() {
  while (lexer_next_token() != EOF) {
    switch (token.type) {
    case TOK_OP: {
      u8 op = get_opcode(token.text);
      // ERROR: illegal operation
      write_u8(op);
      break;
    }
    case TOK_NUM: {
      u64 num = strtol(token.text, NULL, 0);
      write_u64(num);
      break;
    }
    case TOK_REF: {
      u64 loc = symbol_find(token.text + 1);
      write_u64(loc);
      break;
    }
    }
  }
}

void assembler_run(FILE *input, FILE *output) {
  resolve();
  encode();
  fflush(assembler.output);
}