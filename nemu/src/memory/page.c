#include "common.h"
#include "cpu/reg.h"
#include "memory/memory.h"

hwaddr_t page_translate(lnaddr_t addr) {
	if (!cpu.PG) return addr;
	else {
		return addr;
	}
}
