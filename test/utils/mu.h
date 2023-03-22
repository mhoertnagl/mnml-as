// mu.h - Minimalist unit testing framework.
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

#ifndef MU_H
#define MU_H

#include <stdio.h>

// clang-format off

typedef struct
{
  int tests_run;
  int tests_failed;
} Mu;

/**
 * Defines a standalone unit test program.
 * 
 * @param body The body block containing 
 *             the unit tests. 
 */
#define mu_unit(body)                                                        \
int main()                                                                   \
{                                                                            \
  Mu __mu__ = {                                                              \
    .tests_run    = 0,                                                       \
    .tests_failed = 0                                                        \
  };                                                                         \
  printf("\n═══════════════════════════════════════════════════════════\n"); \
  printf(" µ Unit v1.0\n");                                                  \
  printf("───────────────────────────────────────────────────────────\n");   \
  printf(" Running file %s\n\n", __FILE__);                                  \
  body                                                                       \
  printf("\n───────────────────────────────────────────────────────────\n"); \
  if (__mu__.tests_failed == 0) {                                            \
    printf(                                                                  \
      " PASSED %d TESTS\n",                                                  \
      __mu__.tests_run                                                       \
    );                                                                       \
  } else {                                                                   \
    printf(                                                                  \
      " FAILED %d of %d TESTS\n",                                            \
      __mu__.tests_failed,                                                   \
      __mu__.tests_run                                                       \
    );                                                                       \
  }                                                                          \
  printf("═══════════════════════════════════════════════════════════\n\n"); \
  return 0;                                                                  \
}

/**
 * Defines a single unit test.
 * 
 * @param name The name of the unit test.
 * @param body The test function body block. 
 */
#define test(name, body)   \
    printf(" ▶ %s", name); \
    body                   \
    __mu__.tests_run++;                 

/**
 * Asserts that the test condition is true or prints the 
 * failing message if the condition is not satisfied.
 * 
 * @param test     The test condition.
 * @param __format The failing message template.
 * @param args     Optional template arguments.
 */
#define assert(test, __format, args...)                         \
  if (!(test)) {                                                \
    printf(" … FAIL\n   ▸ %d: "__format"\n", __LINE__, ##args); \
    __mu__.tests_failed++;                                      \
  } else {                                                      \
    printf(" … OK\n");                                          \
  }

// clang-format on

#endif
