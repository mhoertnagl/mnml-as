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

#ifndef SYM_H
#define SYM_H

#include "utils/types.h"

#define TABLE_SIZE (1 << 16)

typedef struct
{
  // clang-format off
  str name;
  u16 loc;
  // clang-format on
} Symbol;

typedef struct
{
  // clang-format off
  u32    size;
  Symbol *symbols[TABLE_SIZE];
  // clang-format on
} SymbolTable;

SymbolTable *new_symbol_table();

void free_symbol_table(SymbolTable *table);

void add_symbol(SymbolTable *table, str name, u16 loc);

i32 find_symbol(SymbolTable *table, str name);

#endif