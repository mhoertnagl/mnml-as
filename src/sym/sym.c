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
#include "sym.h"

SymbolTable *new_symbol_table()
{
  SymbolTable *table = (SymbolTable *)malloc(sizeof(SymbolTable));
  table->size = 0;
  return table;
}

void free_symbol_table(SymbolTable *table)
{
  free(table);
}

void add_symbol(SymbolTable *table, str name, i32 loc)
{
  Symbol symbol = table->symbols[table->size];
  symbol.name = name;
  symbol.loc = loc;
  table->size++;
}

i32 find_symbol(SymbolTable *table, str name)
{
  for (i32 i = 0; i < table->size; i++)
  {
    Symbol symbol = table->symbols[i];
    if (strcmp(name, symbol.name) == 0)
    {
      return symbol.loc;
    }
  }
  return -1;
}