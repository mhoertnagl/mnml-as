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
#include "utils/errio.h"
#include "as/as.h"

#define MAX_LINE_LEN 255

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
    if (strncmp(mn, keywords[i], 3) == 0)
    {
      return i / 4;
    }
  }
  return -1;
}

int main(int argc, char **argv)
{
  printf("Keyword table size: %d", sizeof(keywords));

  if (argc < 3)
  {
    printf("Usage: %s input.as output.vm\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *src_fp;
  FILE *bin_fp;

  i32 read;
  u32 len = 0;
  char line[MAX_LINE_LEN];

  src_fp = fopen(argv[1], "r");

  if (src_fp == NULL)
  {
    perrorf("ERROR: Source file [%s] not found.\n", argv[1]);
    return EXIT_FAILURE;
  }

  bin_fp = fopen(argv[2], "wb");

  if (bin_fp == NULL)
  {
    perrorf("ERROR: Binary file [%s] not found.\n", argv[2]);
    return EXIT_FAILURE;
  }

  while (fgets(line, MAX_LINE_LEN, src_fp) != NULL)
  {
    fwrite(line, 10, 1, bin_fp);
    printf(line);
  }

  fclose(src_fp);

  return EXIT_SUCCESS;
}
