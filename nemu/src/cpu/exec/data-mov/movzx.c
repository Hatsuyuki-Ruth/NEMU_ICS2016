#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "movzx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movzx-template.h"
#undef DATA_BYTE

make_helper_v(movzx_rm2r)

static void do_movzx_b(){
	uint32_t res = op_src->val & 0xffff;
	write_operand_l(op_dest, res);
	print_asm_template2();
}

make_helper(movzx_rm2r_b){
	return idex(eip, decode_rm2r_l, do_movzx_b);
}
