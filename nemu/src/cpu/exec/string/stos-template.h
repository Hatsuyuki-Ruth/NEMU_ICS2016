#include "cpu/exec/template-start.h"

#define instr stos

static void do_execute(){
	printf("%x\n", reg_l(R_EDI));
	REG(R_EAX) = swaddr_read(reg_l(R_EDI), DATA_BYTE);
	printf("OK\n");
	if(cpu.DF == 0){
		reg_l(R_EDI) += DATA_BYTE;
	}
	else{
		reg_l(R_EDI) -= DATA_BYTE;
	}
	print_asm("stos");
}

make_instr_helper(n)

#undef instr

#include "cpu/exec/template-end.h"
