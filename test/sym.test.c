#include "utils/mu.h"
#include "../src/sym/sym.h"

mu_unit({
  test("A new symbol table should be empty", {
    SymbolTable *table = new_symbol_table();
    assert(table->size == 0, "table size should be 0");
    free_symbol_table(table);
  });

  test("Adding a symbol should increase table size by one", {
    SymbolTable *table = new_symbol_table();
    add_symbol(table, "x", 42);
    assert(table->size == 1, "table size should be 1");
    free_symbol_table(table);
  });

  test("An added a symbol should be stored in the table", {
    SymbolTable *table = new_symbol_table();
    add_symbol(table, "x", 42);
    Symbol *sym = table->symbols[0];
    assert_str_equal(sym->name, "x");
    assert(sym->loc == 42, "location of first symbol should be 42");
    free_symbol_table(table);
  });

  test("An added symbol should be findable again", {
    SymbolTable *table = new_symbol_table();
    add_symbol(table, "x", 42);
    i32 loc = find_symbol(table, "x");
    assert(loc == 42, "'x' should have location 42");
    free_symbol_table(table);
  });

  test("Multiple added symbol should be findable again", {
    SymbolTable *table = new_symbol_table();
    add_symbol(table, "x0", 42);
    add_symbol(table, "x1", 43);
    add_symbol(table, "x2", 44);
    i32 loc2 = find_symbol(table, "x2");
    i32 loc0 = find_symbol(table, "x0");
    i32 loc1 = find_symbol(table, "x1");
    assert(loc2 == 44, "'x2' should have location 44");
    assert(loc1 == 43, "'x1' should have location 43");
    assert(loc0 == 42, "'x0' should have location 42");
    free_symbol_table(table);
  });

  test("A not added symbol should not be findable", {
    SymbolTable *table = new_symbol_table();
    add_symbol(table, "x", 42);
    i32 loc = find_symbol(table, "y");
    assert(loc == -1, "'y' should not be in the table");
    free_symbol_table(table);
  });
})
