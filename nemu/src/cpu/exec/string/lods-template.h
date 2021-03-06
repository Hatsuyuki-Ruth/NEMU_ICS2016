#include "cpu/exec/template-start.h"

#define instr lods

static void do_execute(){
	REG(R_EAX) = swaddr_read(reg_l(R_ESI), DATA_BYTE, R_DS);
//	printf("%x\n", cpu.esi);
	if(cpu.DF == 0){
		reg_l(R_ESI) += DATA_BYTE;
	}
	else{
		reg_l(R_ESI) -= DATA_BYTE;
	}
//	printf("%x\n", cpu.esi);
	print_asm("lods");
}

make_instr_helper(n)

#undef instr

#include "cpu/exec/template-end.h"
