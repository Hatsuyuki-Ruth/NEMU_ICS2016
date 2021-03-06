#include "cpu/exec/helper.h"

make_helper(ljmp) {
	uint32_t new_eip = instr_fetch(cpu.eip + 1, 4);
	uint16_t seg = instr_fetch(cpu.eip + 1 + 4, 2);
	cpu.eip = new_eip;
	cpu.seg[R_CS] = seg;
	print_asm("ljmp 0x%x, 0x%x\n", seg, new_eip);
	//return 1 + 4 + 2;
	/* Directly point to new_eip */
	return 0;
}

