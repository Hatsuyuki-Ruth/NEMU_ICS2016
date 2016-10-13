#include "cpu/exec/helper.h"

make_helper(jb_i_b);
make_helper(jb_i_v);

#define DATA_BYTE 1
#include "jb-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jb-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jb-template.h"
#undef DATA_BYTE

make_helper_v(jb_i)
