/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "test_common.h"
#include <ds/hash.h>
#include <ds/util.h>

/* keep top 2000 to test remove */
static char *inserted_items[2000];

void
test_htable(void **state) {
  char     keybuf[256];
  HTable  *htable;
  void    *found;
  char    *key;
  uint32_t count, i, k;
  uint32_t capacity;

  capacity = ds_prime_num(25);
  htable   = hash_new_str(capacity);

  /* 25 is not a prime number */
  assert_true(htable->capacity > 25);

  count = 1000;

  srand((unsigned int)time(NULL));

  /* make sure it is samll size: max 32 */
  for (i = 0; i < count; i++) {
    /* random key length */
    k = rand() % (sizeof(keybuf) / 8 - 1);

    rand_str(keybuf, k);
    key = strdup(keybuf);

    hash_set(htable, key, key);

    /* test find value */
    found = hash_get(htable, key);
    assert_non_null(found);

    /* found values must be same */
    assert_ptr_equal(key, found);
    inserted_items[i] = key;

    if (i == 10 || i == 50) {
      hash_unset(htable, key);
      found = hash_get(htable, key);
      assert_null(found);
    }
  }

  count = (uint32_t)htable->count;

  /* test resize */

  /* increase size */
  hash_resize(htable, 100);
  assert_true(htable->count == count);

  /* decrease size */
  hash_resize(htable, 15);
  assert_true(htable->count == count);

  /* some extra test after resizing table */
  for (i = 0; i < 10; i++) {
    /* random key length */
    k = rand() % (sizeof(keybuf) / 8 - 1);

    rand_str(keybuf, k);
    key = strdup(keybuf);

    hash_set(htable, key, key);

    /* test find value */
    found = hash_get(htable, key);
    assert_non_null(found);

    /* found values must be same */
    assert_ptr_equal(key, found);
    inserted_items[i] = key;

    if (i == 10 || i == 50) {
      hash_unset(htable, key);
      found = hash_get(htable, key);
      assert_null(found);
    }
  }

  count = (uint32_t)htable->count;

  /* test other hash funcs */
  htable->hashfn = ds_hashfn_sdbm;

  hash_resize(htable, 50);
  assert_true(htable->count == count);
}
