#include <stdio.h>
#include <stdlib.h>
#include "utils/mu.h"
#include "../src/as/vm.h"
#include "../src/as/as.h"

mu_unit({
  test("Test assembly of files/02.as", {
    FILE *src_fp = fopen("./test/files/03.as", "r");
    FILE *bin_fp = fopen("./test/files/03.vm", "wb");

    if (src_fp == NULL)
    {
      fail("Could not open input file!\n");
      return 0;
    }

    if (bin_fp == NULL)
    {
      fail("Could not open output file!\n");
      return 0;
    }

    Assembler *assembler = new_assembler(src_fp, bin_fp);

    assembler_run(assembler);

    free_assembler(assembler);
    fclose(src_fp);
    fflush(bin_fp);
    fclose(bin_fp);

    int val = 42;
    FILE *out_fp = fopen("./test/files/02.vm", "r");

    fread(&val, 1, 1, out_fp);
    assert_int_equal(val, VM_PSH);

    val = 42;
    // fread(&val, 2, 1, out_fp);
    // assert_int_equal(val, 0x1234);
    fread(&val, 1, 1, out_fp);
    assert_int_equal(val, 0x12);
    fread(&val, 1, 1, out_fp);
    assert_int_equal(val, 0x34);

    val = 42;
    fread(&val, 1, 1, out_fp);
    assert_int_equal(val, VM_DUP);

    val = 42;
    fread(&val, 1, 1, out_fp);
    assert_int_equal(val, VM_ADD);

    val = 42;
    fread(&val, 1, 1, out_fp);
    assert_int_equal(val, VM_PSH);

    val = 42;
    // fread(&val, 2, 1, out_fp);
    // assert_int_equal(val, 0x0005);
    fread(&val, 1, 1, out_fp);
    assert_int_equal(val, 0x00);
    fread(&val, 1, 1, out_fp);
    assert_int_equal(val, 0x05);

    val = 42;
    fread(&val, 1, 1, out_fp);
    assert_int_equal(val, VM_JMP);

    fclose(out_fp);
  });
})
