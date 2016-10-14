#include "cpu/exec/template-start.h"

#define instr lods

static void do_execute(){
	REG(R_EAX) = swaddr_read(reg_l(R_ESI), DATA_BYTE);
	if(cpu.DF == 0){
		REG(R_ESI) += DATA_BYTE;
	}
	else{
		REG(R_ESI) -= DATA_BYTE;
	}
	print_asm("lods");
}

make_instr_helper(n)

#undef instr

#include "cpu/exec/template-end.h"
