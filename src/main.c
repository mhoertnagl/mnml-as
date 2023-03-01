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
#include "as/as.h"

#define MAX_LINE_LEN 256
#define MAX_TEXT_LEN 256

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

typedef struct
{
  // clang-format off
  char text[MAX_TEXT_LEN];
  // clang-format on
} Token;

i8 chr;
u32 line = 1;
u32 col = 0;
char text[MAX_TEXT_LEN];

void next_chr(FILE *input)
{
  chr = getc(input);
  col++;
}

void skip_space(FILE *input)
{
  while (chr != EOF && isspace(chr))
  {
    if (chr == '\n')
    {
      line++;
      col = 0;
    }

    next_chr(input);
  }
}

void read_text(FILE *input)
{
  u32 p = 0;
  while (chr != EOF && !isspace(chr))
  {
    text[p++] = chr;
    next_chr(input);
  }
  text[p] = '\0';
}

i8 next_token(FILE *input)
{
  next_chr(input);

  if (chr == EOF)
  {
    return EOF;
  }

  if (isspace(chr))
  {
    skip_space(input);
  }

  if (chr == '@')
  {
    read_text(input);
    printf("%lu:%lu Found label: [%s]\n", line, col, text);
  }
  else if (isdigit(chr))
  {
    read_text(input);
    printf("%lu:%lu Found number: [%s]\n", line, col, text);
  }
  else
  {
    read_text(input);
    printf("%lu:%lu Found keyword: [%s]\n", line, col, text);
  }
  return 0;
}

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    printf("Usage: %s input.as output.vm\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *src_fp;
  FILE *bin_fp;

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

  while (next_token(src_fp) != EOF)
  {
    /* code */
  }

  fclose(src_fp);

  return EXIT_SUCCESS;
}
