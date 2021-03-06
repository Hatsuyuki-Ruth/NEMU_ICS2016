#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/cltd.h"
#include "data-mov/cwtl.h"
#include "data-mov/movsx.h"
#include "data-mov/movzx.h"

#include "arith/dec.h"
#include "arith/inc.h"
#include "arith/neg.h"
#include "arith/imul.h"
#include "arith/mul.h"
#include "arith/idiv.h"
#include "arith/div.h"
#include "arith/add.h"
#include "arith/sub.h"
#include "arith/adc.h"
#include "arith/sbb.h"

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"
#include "logic/shld.h"

#include "set/setcc.h"

#include "string/rep.h"

#include "misc/misc.h"

#include "special/special.h"

#include "cmp/cmp.h"
#include "call/call.h"
#include "push/push.h"
#include "pop/pop.h"
#include "test/test.h"

#include "jmp/jmp.h"
#include "jmp/jcc.h"

#include "ret/ret.h"
#include "leave/leave.h"

#include "string/lods.h"
#include "string/movs.h"
#include "string/stos.h"
#include "string/scas.h"

#include "seg/lgdt.h"
#include "seg/mov.h"
#include "seg/ljmp.h"

#include "string/std.h"

#include "cmovcc/cmovcc.h"

