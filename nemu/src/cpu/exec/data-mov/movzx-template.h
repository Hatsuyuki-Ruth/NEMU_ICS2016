#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute(){
	DATA_TYPE res = op_src->val & 0xff;
	OPERAND_W(op_dest, res);
	print_asm_template2();
}
make_instr_helper(rm2r)

#undef instr

#include "cpu/exec/template-end.h"
