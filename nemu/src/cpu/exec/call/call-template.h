#include "cpu/decode/modrm.h"
#include "cpu/reg.h"
#include "nemu.h"
#include "cpu/helper.h"
#include "cpu/exec/helper.h"
#include "cpu/exec/template-start.h"

#define instr call

make_helper(concat(call_rm_, SUFFIX)){
	int len = concat(decode_rm_, SUFFIX)(eip + 1);
	//printf("%x\n", im);
	cpu.esp -= DATA_BYTE;
	swaddr_write(cpu.esp, DATA_BYTE, cpu.eip + len, R_SS);
	cpu.eip = op_src->val;
	print_asm("call 0x%x", cpu.eip);
	return 0;
}

make_helper(concat(call_i_, SUFFIX)){
	int im = instr_fetch(eip + 1, DATA_BYTE);
	//printf("%x\n", im);
	cpu.esp -= DATA_BYTE;
	swaddr_write(cpu.esp, DATA_BYTE, cpu.eip + DATA_BYTE, R_SS);
	cpu.eip = cpu.eip + im;
	print_asm("call 0x%x", eip + im + DATA_BYTE + 1);
	return DATA_BYTE + 1;
}

#undef instr

#include "cpu/exec/template-end.h"

