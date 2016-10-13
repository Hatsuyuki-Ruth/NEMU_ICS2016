#include "cpu/exec/template-start.h"

#define instr jo

static void do_execute(){
	DATA_TYPE_S disp = op_src->val;
	print_asm("jo $0x%x", cpu.eip + 1 + DATA_BYTE + disp);
	if(cpu.OF == 1) cpu.eip += disp;
}
make_instr_helper(i)

#undef instr

#include "cpu/exec/template-end.h"
