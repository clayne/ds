/*
 * Copyright (c), Recep Aslantas.
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "common.h"
#include "../include/ds/hash-funcs.h"

/*
   References:
     o http://www.cse.yorku.ca/~oz/hash.html
 */

DS_EXPORT
uint32_t
ds_hashfn_djb2(void *key) {
  const char *str;
  uint32_t    hash;
  int         c;

  str = key;

  hash = 5381;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

DS_EXPORT
uint32_t
ds_hashfn_sdbm(void *key) {
  const char *str;
  uint32_t    hash;
  int         c;

  str = key;

  hash = 0;
  while ((c = *str++))
    hash = c + (hash << 6) + (hash << 16) - hash;

  return hash;
}