#include "common.h"

#include <stdio.h>

extern uint32_t dram_read(hwaddr_t, size_t);
extern void dram_write(hwaddr_t, size_t, uint32_t);

/*
	The L2 cache defined here.
*/

void _dram_read(uint8_t *result, uint32_t addr){
	*result = dram_read(addr, 1);
}

#define CACHE_L 16
#define CACHE_S 12
#define CACHE_B 12
#define CACHE_WRITEBACK
#define CACHE_NAME l2
#define CACHE_NEXT_LEVEL_READ(result, addr) _dram_read((result), (addr))
#define CACHE_NEXT_LEVEL_WRITE(addr, data) dram_write((addr), 1, (data))

#include "cache-template.h"

#undef CACHE_L
#undef CACHE_S
#undef CACHE_B 
#undef CACHE_WRITEBACK
#undef CACHE_NAME
#undef CACHE_NEXT_LEVEL_READ
#undef CACHE_NEXT_LEVEL_WRITE

/*
	The L1 cache defined here.
*/

#define CACHE_L 8
#define CACHE_S 8
#define CACHE_B 8
#define CACHE_WRITETHROUGH
#define CACHE_NAME l1
#define CACHE_NEXT_LEVEL_READ(result, addr) l2_read((result), (addr))
#define CACHE_NEXT_LEVEL_WRITE(addr, data) l2_write((addr), (data))

#include "cache-template.h"

#undef CACHE_L
#undef CACHE_S
#undef CACHE_B 
#undef CACHE_WRITETHROUGH
#undef CACHE_NAME
#undef CACHE_NEXT_LEVEL_READ
#undef CACHE_NEXT_LEVEL_WRITE
