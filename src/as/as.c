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
#include "utils/types.h"
#include "vm.h"
#include "as.h"

// clang-format off
static const char keywords[][3] = {
  "psh", "pop", "nip", "swp", "ovr", "dup", "rot", "inc",
  "dec", "add", "sub", "mul", "div", "not", "and", "oor",
  "xor", "sll", "srl", "equ", "neq", "slt", "sgt", "sle",
  "sge", "jmp", "jal", "bra", "ldw", "stw", "drx", "dtx"
};
// clang-format on

i8 get_opcode(cstr keyword)
{
  for (u32 i = 0; i < sizeof(keywords) / 3; i++)
  {
    if (strncmp(keyword, keywords[i], 3) == 0)
    {
      return i;
    }
  }
  return -1;
}

void write_i8(Assembler *assembler, i8 val)
{
  fwrite(&val, 1, 1, assembler->output);
}

void write_u8(Assembler *assembler, u8 val)
{
  fwrite(&val, 1, 1, assembler->output);
}

// void write_i16(Assembler *assembler, i16 val)
// {
//   write_i8(assembler, val >> 8);
//   write_u8(assembler, val & 0xff);
//   // fwrite(&val, 2, 1, assembler->output);
// }

// void write_u16(Assembler *assembler, u16 val)
// {
//   write_u8(assembler, val >> 8);
//   write_u8(assembler, val & 0xff);
//   // fwrite(&val, 2, 1, assembler->output);
// }

Assembler *new_assembler(FILE *input, FILE *output)
{
  Assembler *assembler = malloc(sizeof(Assembler));
  assembler->lexer = new_lexer(input);
  assembler->table = new_symbol_table();
  assembler->output = output;
  assembler->ip = 0;
  return assembler;
}

void free_assembler(Assembler *assembler)
{
  free_symbol_table(assembler->table);
  free_lexer(assembler->lexer);
  free(assembler);
}

void resolve_labels(Assembler *assembler)
{
  u32 ip = 0;
  Lexer *lexer = assembler->lexer;
  SymbolTable *table = assembler->table;

  while (next_token(lexer) != EOF)
  {
    Token token = lexer->token;
    switch (token.type)
    {
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
      add_symbol(table, token.text + 1, ip);
      // ERROR: symbol already defined
      break;
    }
  }
}

void encode(Assembler *assembler)
{
  Lexer *lexer = assembler->lexer;
  SymbolTable *table = assembler->table;

  while (next_token(lexer) != EOF)
  {
    Token token = lexer->token;
    switch (token.type)
    {
    case TOK_OP:
    {
      u8 op = get_opcode(token.text);
      // ERROR: illegal operation
      write_u8(assembler, op);
      break;
    }
    case TOK_NUM:
    {
      i16 num = strtol(token.text, NULL, 0);
      // ERROR: number conversion error
      write_i8(assembler, num >> 8);
      write_u8(assembler, num & 0xff);
      // write_i16(assembler, num);
      break;
    }
    case TOK_REF:
    {
      i32 loc = find_symbol(table, token.text + 1);
      // ERROR: undefined reference
      write_u8(assembler, (loc >> 8) & 0xff);
      write_u8(assembler, loc & 0xff);
      // write_u16(assembler, loc);
      break;
    }
    }
  }
}

void assembler_run(Assembler *assembler)
{
  resolve_labels(assembler);
  encode(assembler);
  fflush(assembler->output);
}