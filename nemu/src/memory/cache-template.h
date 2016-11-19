/*
	Define CACHE_S, CACHE_B, CACHE_NAME, and possibly CACHE_WRITETHROUGH in advance.
	Undefine them outside this file.
*/

#define ADDR_LEN 32
#define CACHE_T (ADDR_LEN - (CACHE_S) - (CACHE_B))
#define CACHE_SET_NUM (1 << (CACHE_S))
#define CACHE_BLOCK_SIZE (1 << (CACHE_B))
#define CACHE_LINE_NUM (CACHE_L)

#define CACHE_LINE concat(CACHE_NAME, _cache_line)
#define CACHE_SET concat(CACHE_NAME, _cache_set)
#define CACHE concat(CACHE_NAME, _cache)
#define CACHE_OBJ concat(CACHE_NAME, _obj)
#define CACHE_READ concat(CACHE_NAME, _read)
#define CACHE_ALLOC concat(CACHE_NAME, _alloc)

typedef struct{
	uint8_t valid;
	uint32_t addr_t;
	#ifdef CACHE_WRITEBACK
		uint8_t dirty;
	#endif
	uint8_t data[CACHE_BLOCK_SIZE]; 
} CACHE_LINE;


typedef struct{
	CACHE_LINE lines[CACHE_LINE_NUM];
} CACHE_SET;

typedef struct{
	CACHE_SET sets[CACHE_SET_NUM];
} CACHE;

CACHE CACHE_OBJ;

#define SET_INDEX(addr) (((((~0U) >> (ADDR_LEN - (CACHE_S))) << (CACHE_B)) & (addr)) >> CACHE_B)

void CACHE_ALLOC(uint32_t addr) {

}

bool CACHE_READ(uint32_t *result, uint32_t addr) {
	int i;
	uint32_t set_index = SET_INDEX(addr);
	uint32_t block_index = (addr & ((1 << (CACHE_B)) - 1));
	for (i = 0; i < CACHE_LINE_NUM; i++) {
		if((addr >> (ADDR_LEN - (CACHE_T))) == CACHE_OBJ.sets[set_index].lines[i].addr_t){
			*result = CACHE_OBJ.sets[set_index].lines[i].data[block_index];
			return 1;
		}
	}
	printf("0x%x 0x%x 0x%x 0x%x\n", addr, (addr >> (ADDR_LEN - (CACHE_T))), set_index, block_index);
	return 0;
}

#undef ADDR_LEN
#undef CACHE_T
#undef CACHE_SET_NUM
#undef CACHE_BLOCK_SIZE
#undef CACHE_LINE_NUM

#undef CACHE_LINE
#undef CACHE_SET
#undef CACHE
#undef CACHE_OBJ
#undef CACHE_READ

#undef SET_INDEX
