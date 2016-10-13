#include "cpu/exec/helper.h"

make_helper(jle_i_b);
make_helper(jle_i_v);

#define DATA_BYTE 1
#include "jle-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jle-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jle-template.h"
#undef DATA_BYTE

make_helper_v(jle_i)
