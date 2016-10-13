#include "cpu/exec/helper.h"

make_helper(jo_i_b);
make_helper(jo_i_v);

#define DATA_BYTE 1
#include "jo-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jo-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jo-template.h"
#undef DATA_BYTE

make_helper_v(jo_i)
