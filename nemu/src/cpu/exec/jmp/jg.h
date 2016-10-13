#include "cpu/exec/helper.h"

make_helper(jg_i_b);
make_helper(jg_i_v);

#define DATA_BYTE 1
#include "jg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jg-template.h"
#undef DATA_BYTE

make_helper_v(jg_i)
