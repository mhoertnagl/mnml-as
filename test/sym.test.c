#include "utils/mu.h"
// #include "../src/sym/sym.h"

mu_unit({
  int a = 1;

  // test("A new symbol table should be empty", {
  //   SymbolTable *table = new_symbol_table();
  //   assert(table->size == 0, "table size should be 0");
  // });

  test("Test 2", {
    assert(a == 2, "a should be [%d]", 2);
  });
})
