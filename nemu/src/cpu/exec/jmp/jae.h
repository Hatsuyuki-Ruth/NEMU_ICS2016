#include "cpu/exec/helper.h"

make_helper(jae_i_b);
make_helper(jae_i_v);

#define DATA_BYTE 1
#include "jae-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jae-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jae-template.h"
#undef DATA_BYTE

make_helper_v(jae_i)
