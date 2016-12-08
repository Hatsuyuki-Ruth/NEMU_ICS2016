#include "cpu/exec/template-start.h"

#define instr leave

static void do_execute(){
	//int i;
	//for(i = REG(R_ESP);i < REG(R_EBP); i += DATA_BYTE) MEM_W(i, 0);
	REG(R_ESP) = REG(R_EBP);
	REG(R_EBP) = MEM_R(REG(R_ESP), R_SS);
	REG(R_ESP) += DATA_BYTE;
	print_asm("leave");
	//return 1;
}
make_instr_helper(n)

#undef instr

#include "cpu/exec/template-end.h"
