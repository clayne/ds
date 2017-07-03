/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "test_common.h"
#include "test_tests.h"

int
main(int argc, const char * argv[]) {
  const struct CMUnitTest tests[] = {
    /* red black tree */
    cmocka_unit_test(test_rb_topdown_str),
    cmocka_unit_test(test_rb_topdown_ptr),
    cmocka_unit_test(test_rb_topdown_custom_cmp),
    cmocka_unit_test(test_rb_topdown_freeenode),
    cmocka_unit_test(test_rb_topdown_custom_cmp_i32),
    cmocka_unit_test(test_rb_topdown_custom_cmp_i64),

    /* forward list */
    cmocka_unit_test(test_flist),

    /* hash table */
    cmocka_unit_test(test_htable)
  };

  return cmocka_run_group_tests(tests,
                                NULL,
                                NULL);
}