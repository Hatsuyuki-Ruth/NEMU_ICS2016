#include "cpu/exec/template-start.h"
#include "../flag.h"

#define instr dec

static void do_execute () {
	DATA_TYPE result = op_src->val - 1;
	OPERAND_W(op_src, result);

	/* TODO: Update EFLAGS. */
	//panic("please implement me");
	cpu.CF = op_src->val == 0;
	arith_flag(op_src->val, MSB(op_src->val), -1, 1, result, MSB(result));
	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
