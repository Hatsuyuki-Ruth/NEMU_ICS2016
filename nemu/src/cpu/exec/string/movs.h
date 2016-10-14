#include "cpu/exec/helper.h"

make_helper(movs_n_b);
make_helper(movs_n_v);

#define DATA_BYTE 1
#include "movs-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "movs-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movs-template.h"
#undef DATA_BYTE

make_helper_v(movs_n)
