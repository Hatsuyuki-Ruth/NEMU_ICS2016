#include "common.h"

#include <stdio.h>

#define CACHE_L 8
#define CACHE_S 7
#define CACHE_B 6
#define CACHE_WRITETHROUGH
#define CACHE_NAME l1

#include "cache-template.h"

#undef CACHE_L
#undef CACHE_S
#undef CACHE_B 
#undef CACHE_WRITETHROUGH
#undef CACHE_NAME
