#include "cpu/exec/helper.h"

make_helper(jns_i_b);
make_helper(jns_i_v);

#define DATA_BYTE 1
#include "jns-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jns-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jns-template.h"
#undef DATA_BYTE

make_helper_v(jns_i)
