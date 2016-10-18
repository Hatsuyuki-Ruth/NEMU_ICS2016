#include "cpu/decode/modrm.h"
#include "cpu/reg.h"
#include "nemu.h"
#include "cpu/helper.h"
#include "cpu/exec/helper.h"
#include "cpu/exec/template-start.h"

#define instr call

make_helper(concat(call_i_, SUFFIX)){
	int im = concat(decode_rm_, SUFFIX)(eip + 1);
	cpu.esp -= DATA_BYTE;
	swaddr_write(cpu.esp, DATA_BYTE, cpu.eip + im);
	cpu.eip += op_src->val;
	print_asm("call 0x%x", cpu.eip + 1 + im);
	return 0;
}

make_helper(concat(call_rm_, SUFFIX)){
	int im = instr_fetch(eip + 1, DATA_BYTE);
	cpu.esp -= DATA_BYTE;
	swaddr_write(cpu.esp, DATA_BYTE, cpu.eip + im);
	cpu.eip = cpu.eip + im;
	print_asm("call 0x%x", eip + im + 5);
	return DATA_BYTE + 1;
}

#undef instr

#include "cpu/exec/template-end.h"

