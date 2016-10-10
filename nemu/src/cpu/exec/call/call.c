#include "cpu/decode/modrm.h"
#include "cpu/reg.h"
#include "nemu.h"
#include "cpu/helper.h"
#include "cpu/exec/helper.h"

make_helper(call_rm){
	return 0;
}

make_helper(call_rel32){
	int im = instr_fetch(eip + 1, 4);
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.eip + 4);
	cpu.eip = cpu.eip + im;
	print_asm("call 0x%x", eip + im + 5);
	return 5;
}

