#include "cpu/exec/helper.h"

make_helper(ja_i_b);
make_helper(ja_i_v);

#define DATA_BYTE 1
#include "ja-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "ja-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "ja-template.h"
#undef DATA_BYTE

make_helper_v(ja_i)
