#include "cpu/exec/helper.h"

make_helper(adc_i2a_b);
make_helper(adc_i2rm_b);
make_helper(adc_r2rm_b);
make_helper(adc_rm2r_b);

make_helper(adc_i2a_v);
make_helper(adc_i2rm_v);
make_helper(adc_r2rm_v);
make_helper(adc_rm2r_v);
make_helper(adc_si2rm_v);

#define DATA_BYTE 1
#include "adc_template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "adc_template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "adc_template.h"
#undef DATA_BYTE

make_helper_v(adc_i2a)
make_helper_v(adc_i2rm)
make_helper_v(adc_r2rm)
make_helper_v(adc_rm2r)
make_helper_v(adc_si2rm)
