#include "utils/mu.h"

mu_unit({
  int a = 1;
  int b = 2;

  test("Test 1", {
    assert(a == 1, "a should be [%d]", 1);
  });

  test("Test 2", {
    assert(b == 2, "b should be [%d]", 2);
  });
})
