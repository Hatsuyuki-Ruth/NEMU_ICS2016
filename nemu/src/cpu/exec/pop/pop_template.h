#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/helper.h"

#define instr pop

static void do_execute(){
	OPERAND_W (op_src, MEM_R(REG (R_ESP), R_SS));
	//MEM_W(REG (R_ESP) , 0);
	//Is it necessary?
	REG (R_ESP) += DATA_BYTE;
	print_asm_template1();
}

make_instr_helper(r)
//make_instr_helper(rm)

#undef instr

#include "cpu/exec/template-end.h"
