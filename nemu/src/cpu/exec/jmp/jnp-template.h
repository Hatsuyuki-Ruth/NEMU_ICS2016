#include "cpu/exec/template-start.h"

#define instr jnp

static void do_execute(){
	DATA_TYPE_S disp = op_src->val;
	print_asm("jnp $0x%x", cpu.eip + 1 + DATA_BYTE + disp);
	if(cpu.PF == 0) cpu.eip += disp;
}
make_instr_helper(i)

#undef instr

#include "cpu/exec/template-end.h"
