#include "cpu/exec/helper.h"

make_helper(jno_i_b);
make_helper(jno_i_v);

#define DATA_BYTE 1
#include "jno-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jno-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jno-template.h"
#undef DATA_BYTE

make_helper_v(jno_i)
