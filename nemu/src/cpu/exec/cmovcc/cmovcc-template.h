#include "cpu/exec/template-start.h"
#define instr cmovcc

make_helper(concat(cmovo_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if (cpu.OF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovno_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(!cpu.OF) OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovc_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(cpu.CF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovnc_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(!cpu.CF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovz_,SUFFIX)){
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(cpu.ZF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovnz_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(!cpu.ZF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmova_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(!cpu.CF && !cpu.ZF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovna_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(cpu.CF || cpu.ZF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovs_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(cpu.SF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovns_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(!cpu.SF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovp_,SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(cpu.PF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovnp_,SUFFIX))
{
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(!cpu.PF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovl_,SUFFIX)){
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(cpu.SF != cpu.OF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovnl_,SUFFIX)){
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(cpu.SF == cpu.OF)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}
 
make_helper(concat(cmovg_,SUFFIX)){
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(!cpu.ZF && (cpu.SF == cpu.OF))
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

make_helper(concat(cmovng_,SUFFIX)){
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	if(cpu.ZF || (cpu.SF != cpu.OF))
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
	return len + 1;
}

#include "cpu/exec/template-end.h"
