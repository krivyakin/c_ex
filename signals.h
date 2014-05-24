#ifndef __C_EX_SIGNALS_H__
#define __C_EX_SIGNALS_H__

#include "c_ex.h"

declare_exception(signal_exception, exception);
declare_exception(floating_point, signal_exception);

void signals_init();

#endif /* __C_EX_SIGNALS_H__ */
