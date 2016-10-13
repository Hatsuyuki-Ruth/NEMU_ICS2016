#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute(){
	DATA_TYPE res;
	if(DATA_BYTE == 2) res = ((int16_t)(op_src->val << 8)) >> 8;
	else res = ((int)(op_src->val << 24)) >> 24;
	OPERAND_W(op_dest, res);
	print_asm_template2();
}
make_instr_helper(rm2r)

#undef instr

#include "cpu/exec/template-end.h"
