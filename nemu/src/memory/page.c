#include "common.h"
#include "cpu/reg.h"
#include "memory/memory.h"

hwaddr_t page_translate(lnaddr_t addr) {
	if (!cpu.PG) return addr;
	else {
		uint32_t dir_ind = (addr >> 22) & 0x3ff;
		uint32_t table_ind = (addr >> 12) & 0x3ff;
		uint32_t offset = addr & 0xfff;
		uint32_t dir = cpu.CR3 & 0xfffff000;
		uint32_t dir_entry = hwaddr_read(dir + (dir_ind << 2), 4);
		uint32_t table = dir_entry & 0xfffff000;
		uint32_t table_entry = hwaddr_read(table + (table_ind << 2), 4);
		return (table_entry & 0xfffff000) | offset;
	}
}

