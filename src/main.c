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
// #include <string.h>
// #include <ctype.h>
// #include "utils/types.h"
#include "utils/errio.h"
// #include "as/as.h"
#include "lex/lex.h"

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

  Lexer *lexer = new_lexer(src_fp);

  fclose(src_fp);

  return EXIT_SUCCESS;
}