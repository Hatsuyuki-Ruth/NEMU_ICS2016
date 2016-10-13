#include "cpu/exec/helper.h"

make_helper(jp_i_b);
make_helper(jp_i_v);

#define DATA_BYTE 1
#include "jp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jp-template.h"
#undef DATA_BYTE

make_helper_v(jp_i)
