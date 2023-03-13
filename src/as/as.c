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
static const char keywords[][4] = {
  "psh", "pop", "nip", "swp", "ovr", "dup", "rot", "inc",
  "dec", "add", "sub", "mul", "div", "not", "and", "oor",
  "xor", "sll", "srl", "equ", "neq", "slt", "sgt", "sle",
  "sge", "jmp", "jal", "bra", "ldw", "stw", "drx", "dtx"
};
// clang-format on

i8 get_opcode(cstr mn)
{
  for (u32 i = 0; i < sizeof(keywords); i += 4)
  {
    if (strncmp(mn, keywords[i], 4) == 0)
    {
      return i / 4;
    }
  }
  return -1;
}

Assembler *new_assembler(FILE *input, FILE *output)
{
  Assembler *assembler = (Assembler *)malloc(sizeof(Assembler));
  assembler->lexer = new_lexer(input);
  assembler->output = output;
  assembler->ip = 0;
  return assembler;
}

void free_assembler(Assembler *assembler)
{
  free_lexer(assembler->lexer);
  free(assembler);
}

u8 assembler_run(Assembler *assembler)
{
  // While there are tokens left.
  // If token is a label
  //   add token and current ip to symbol table
  // If token is a number
  //   convert text to 16bit number and save it to output
  //   ip += 2
  // If token is an operation code
  //   convert text to opcode and save it to output
  //   ip += 1
}