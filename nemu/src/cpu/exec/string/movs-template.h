#include "cpu/exec/template-start.h"

#define instr movs

static void do_execute(){
	swaddr_write(reg_l(R_EDI), DATA_BYTE, swaddr_read(reg_l(R_ESI), DATA_BYTE));
	if(cpu.DF == 0){
		REG(R_EDI) += DATA_BYTE;
		REG(R_ESI) += DATA_BYTE;
	}
	else{
		REG(R_EDI) -= DATA_BYTE;
		REG(R_ESI) -= DATA_BYTE;
	}
	print_asm("movs");
}

make_instr_helper(n)

#undef instr

#include "cpu/exec/template-end.h"
