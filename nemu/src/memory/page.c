#include "common.h"
#include "cpu/reg.h"
#include "memory/memory.h"
#include <stdlib.h>

#define TLB_LEN 64

typedef struct {
	lnaddr_t va;
	hwaddr_t pa;
	bool valid;
} tlb_entry;

static tlb_entry tlb_cache[TLB_LEN];

void flush_tlb() {
	int i;
	for (i = 0; i < TLB_LEN; i++) {
		tlb_cache[i].valid = 0;
	}
}

static int find_tlb(lnaddr_t va) {
	int i;
	for (i = 0; i < TLB_LEN; i++) {
		if (tlb_cache[i].valid && tlb_cache[i].va == va) return i;
	}
	return -1;
}

static void insert_tlb(lnaddr_t va, hwaddr_t pa) {
	int i;
	for (i = 0; i < TLB_LEN; i++) {
		if (!tlb_cache[i].valid) {
			tlb_cache[i].valid = 1;
			tlb_cache[i].va = va;
			tlb_cache[i].pa = pa;
			return;
		}
	}
	i = rand() % TLB_LEN;
	tlb_cache[i].va = va;
	tlb_cache[i].pa = pa;
}

hwaddr_t page_translate(lnaddr_t addr) {
	if (!cpu.PG) return addr;
	else {
		int tlb_ind = find_tlb(addr & 0xfffff000);
		if (tlb_ind != -1) return tlb_cache[tlb_ind].pa + (addr & 0xfff);
		uint32_t dir_ind = (addr >> 22) & 0x3ff;
		uint32_t table_ind = (addr >> 12) & 0x3ff;
		uint32_t offset = addr & 0xfff;
		uint32_t dir = cpu.CR3 & 0xfffff000;
		uint32_t dir_entry = hwaddr_read(dir + (dir_ind << 2), 4);
		uint32_t table = dir_entry & 0xfffff000;
		uint32_t table_entry = hwaddr_read(table + (table_ind << 2), 4);
		insert_tlb(addr & 0xfffff000, table_entry & 0xfffff000);
		return (table_entry & 0xfffff000) | offset;
	}
}

