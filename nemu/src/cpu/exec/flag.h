#include "nemu.h"
#include "cpu/exec/helper.h"
//#include "cpu/exec/template-start.h"

void update_SF(int msbdes);

void update_ZF(int des);

void update_PF(int des);

void update_CF(int src1, int msbsrc1, int src2, int msbsrc2, int des, int msbdes, int op);

void logical_flag(int src1, int src2, int des, int msbdes);

void arith_flag(int src1, int msbsrc1, int src2, int msbsrc2, int des, int msbdes);

//#include "cpu/exec/template-end.h"

