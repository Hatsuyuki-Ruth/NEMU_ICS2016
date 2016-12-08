#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "cmovcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmovcc-template.h"
#undef DATA_BYTE

make_helper_v(cmovo)
make_helper_v(cmovno)

make_helper_v(cmovc)
make_helper_v(cmovnc)

make_helper_v(cmovz)
make_helper_v(cmovnz)

make_helper_v(cmova)
make_helper_v(cmovna)

make_helper_v(cmovs)
make_helper_v(cmovns)

make_helper_v(cmovp)
make_helper_v(cmovnp)

make_helper_v(cmovl)
make_helper_v(cmovnl)

make_helper_v(cmovg)
make_helper_v(cmovng)
