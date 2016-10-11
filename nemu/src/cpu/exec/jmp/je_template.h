#include "cpu/exec/template-start.h"

#define instr je

static void do_execute(){
	DATA_TYPE_S disp = op_src->val;
	print_asm("je 0x%x", cpu.eip + 1 + DATA_BYTE + disp);
	if(cpu.ZF) cpu.eip += disp;
}
make_instr_helper(i)

#include "cpu/exec/template-end.h"

