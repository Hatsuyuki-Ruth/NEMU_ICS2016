#include "cpu/exec/template-start.h"
#include "../flag.h"

#define instr scas

static void do_execute(){
	DATA_TYPE dest = swaddr_read(reg_l(R_EDI), DATA_BYTE);
	DATA_TYPE src = REG(R_EAX);
	DATA_TYPE res = src - dest;
	cpu.CF = src < dest;
	arith_flag(src, MSB(src), (~dest) + 1, MSB((~dest) + 1), res, MSB(res));
	printf("%x\n", cpu.edi);
	if(cpu.DF == 0){
		REG(R_EDI) += DATA_BYTE;
	}
	else{
		REG(R_EDI) -= DATA_BYTE;
	}
	printf("%x\n", cpu.edi);
	print_asm("scas");
}

make_instr_helper(n)

#undef instr

#include "cpu/exec/template-end.h"
