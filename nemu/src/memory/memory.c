#include "common.h"
#include "cache.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	uint32_t result = 0;
	uint8_t tmp;
	int j;
	for (j = len - 1; j >= 0; j--) {
		l1_read(&tmp, addr + len);
		result = result * 0x100 + tmp;
		printf("tmp: 0x%x\n", tmp);
	}
	printf("Len: %d. Cache result: 0x%x. DRAM result: 0x%x\n", len, result, dram_read(addr, len) & (~0u >> ((4 - len) << 3)));
	return result;
	//if(l1_read(&result, addr)) return result;
	//else return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	dram_write(addr, len, data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_write(addr, len, data);
}

