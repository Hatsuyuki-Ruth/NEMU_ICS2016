#include "cpu/exec/helper.h"
#include "cpu/helper.h"

make_helper(jmp_i_b);
make_helper(jmp_i_v);
//make_helper(jmp_rm_b);
make_helper(jmp_rm_v);

#define DATA_BYTE 1
#include "jmp_template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jmp_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jmp_template.h"
#undef DATA_BYTE

make_helper_v(jmp_i)
make_helper_v(jmp_rm)
