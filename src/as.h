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

#include "lex.h"
#include "sym.h"
#include <stdint.h>

typedef uint8_t u8;
typedef uint64_t u64;
typedef const char *cstr;

#define SRC_EXT "as"
#define BIN_EXT "vm"

typedef struct {
  SymbolTable table;
  FILE        *output;
  u64         ip;
} Assembler;

extern Assembler assembler;

void assembler_run(FILE *input, FILE *output);
