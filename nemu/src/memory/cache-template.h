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
#define CACHE_WRITE concat(CACHE_NAME, _write)

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
	int i, j;
	uint32_t set_index = SET_INDEX(addr);
	uint32_t block_index = (addr & ((1 << (CACHE_B)) - 1));
	uint32_t addr_base = addr - block_index;
	printf("Allocating: %x\n", addr_base);
	for (i = 0; i < CACHE_LINE_NUM; i++) {
		if (!CACHE_OBJ.sets[set_index].lines[i].valid || i == CACHE_LINE_NUM - 1) {
			CACHE_OBJ.sets[set_index].lines[i].valid = 1;
			CACHE_OBJ.sets[set_index].lines[i].addr_t = (addr >> (ADDR_LEN - (CACHE_T)));
			for(j = 0; j < CACHE_BLOCK_SIZE; j++) {
				CACHE_OBJ.sets[set_index].lines[i].data[j] = (dram_read(addr_base + j, 1) & 0xffU);
				//printf("%x ", dram_read(addr_base + j, 1) & 0xff);
			}
			//printf("\n");
			return;
		}
	}
}

void CACHE_READ(uint8_t *result, uint32_t addr) {
	int i;
	uint32_t set_index = SET_INDEX(addr);
	uint32_t block_index = (addr & ((1 << (CACHE_B)) - 1));
	//printf("0x%x 0x%x 0x%x 0x%x\n", addr, (addr >> (ADDR_LEN - (CACHE_T))), set_index, block_index);
	for (i = 0; i < CACHE_LINE_NUM; i++) {
		if (CACHE_OBJ.sets[set_index].lines[i].valid &&
		   (addr >> (ADDR_LEN - (CACHE_T))) == CACHE_OBJ.sets[set_index].lines[i].addr_t) {
			*result = CACHE_OBJ.sets[set_index].lines[i].data[block_index];
			puts("HIT");
			return;
			//return 1;
		}
	}
	puts("MISS");
	CACHE_ALLOC(addr);
	for (i = 0; i < CACHE_LINE_NUM; i++) {
		if (CACHE_OBJ.sets[set_index].lines[i].valid &&
		   (addr >> (ADDR_LEN - (CACHE_T))) == CACHE_OBJ.sets[set_index].lines[i].addr_t) {
			*result = CACHE_OBJ.sets[set_index].lines[i].data[block_index];
			return;
		}
	}
	//return 0;
}

#ifdef CACHE_WRITETHROUGH
void CACHE_WRITE(uint32_t addr, uint8_t datum) {
	int i;
	uint32_t set_index = SET_INDEX(addr);
	uint32_t block_index = (addr & ((1 << (CACHE_B)) - 1));
	for (i = 0; i < CACHE_LINE_NUM; i++) {
		if (CACHE_OBJ.sets[set_index].lines[i].valid &&
		   (addr >> (ADDR_LEN - (CACHE_T))) == CACHE_OBJ.sets[set_index].lines[i].addr_t) {
			CACHE_OBJ.sets[set_index].lines[i].data[block_index] = datum;
			return;
		}
	}
}
#endif

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
#undef CACHE_ALLOC
#undef CACHE_WRITE

#undef SET_INDEX
