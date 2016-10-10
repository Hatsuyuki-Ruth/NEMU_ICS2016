#include "cpu/exec/helper.h"
#include "cpu/exec/template-start.h"
#include "cpu/decode/modrm.h"

make_helper(concat(push_r_, SUFFIX)){
	int num_reg = instr_fetch(eip, 1) & 7;
	cpu.esp -= DATA_BYTE;
	swaddr_write(cpu.esp, DATA_BYTE, REG(num_reg));
	printf("%d %d %d\n", num_reg, REG(num_reg), DATA_BYTE);
	return 1;
}

#include "cpu/exec/template-end.h"
	
