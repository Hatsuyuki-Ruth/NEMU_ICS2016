#include "common.h"

#include <stdio.h>

extern uint32_t dram_read(hwaddr_t, size_t);
extern void dram_write(hwaddr_t, size_t, uint32_t);

#define CACHE_L 8
#define CACHE_S 8
#define CACHE_B 8
#define CACHE_WRITETHROUGH
#define CACHE_NAME l1

#include "cache-template.h"

#undef CACHE_L
#undef CACHE_S
#undef CACHE_B 
#undef CACHE_WRITETHROUGH
#undef CACHE_NAME
