#include "common.h"
#include "cpu/reg.h"
#include "memory/memory.h"

lnaddr_t seg_translate(swaddr_t addr, uint8_t sreg) {
	if (!cpu.PE) return addr;
	uint32_t seg_des1 = hwaddr_read(cpu.GDTR + (cpu.seg[sreg] >> 3), 4);
	uint32_t seg_des2 = hwaddr_read(cpu.GDTR + (cpu.seg[sreg] >> 3) + 4, 4);
	uint32_t seg_base = (seg_des1 >> 16) + (seg_des2 & 0xff) + ((seg_des2 >> 24) << 24);
	printf("%s: %x\n", seg_reg_name[sreg], seg_base);
	return seg_base + addr;
}

