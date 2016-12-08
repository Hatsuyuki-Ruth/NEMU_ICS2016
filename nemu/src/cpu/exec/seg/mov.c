#include "cpu/exec/helper.h"

static inline void do_mov_cr_rm2r() {
	uint32_t cr_ind = (instr_fetch(cpu.eip + 2, 1) >> 3) & 0x7;
	print_asm("mov %s, CR%d", op_src->str, cr_ind);
	cpu.CR[cr_ind] = op_src->val;
	if (cr_ind == 3) {
		/* TODO: Flush TLB. */
	}
}

make_helper(mov_cr_rm2r_l) {
	return idex(eip, decode_rm2r_l, do_mov_cr_rm2r);
}

static inline void do_mov_cr_r2rm() {
	uint32_t cr_ind = (instr_fetch(cpu.eip + 2, 1) >> 3) & 0x7;
	print_asm("mov CR%d, %s", cr_ind, op_src->str);
	write_operand_l(op_dest, cpu.CR[cr_ind]);
}

make_helper(mov_cr_r2rm_l) {
	return idex(eip, decode_r2rm_l, do_mov_cr_r2rm);
}

