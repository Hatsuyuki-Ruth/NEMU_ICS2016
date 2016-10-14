#include "cpu/exec/helper.h"

make_helper(scas_n_b);
make_helper(scas_n_v);

#define DATA_BYTE 1
#include "scas-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "scas-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "scas-template.h"
#undef DATA_BYTE

make_helper_v(scas_n)
