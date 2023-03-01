#include "utils/mu.h"

mu_unit({
  int a = 1;

  test("Test 1", {
    assert(a == 1, "a should be [%d]", 1);
  });

  test("Test 2", {
    assert(a == 2, "a should be [%d]", 2);
  });
})
