#include "cpu/exec/helper.h"

make_helper(jge_i_b);
make_helper(jge_i_v);

#define DATA_BYTE 1
#include "jge-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jge-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jge-template.h"
#undef DATA_BYTE

make_helper_v(jge_i)
