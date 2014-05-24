#include <signal.h>

#include "c_ex.h"
#include "signals.h"

/* TODO: add excepions for each of signals that can be caught */
define_exception(signal_exception, exception);
define_exception(floating_point, signal_exception);

static void fpe_handler(int signo)
{
	throw(floating_point("SIGFPE"));
}

void signals_init()
{
	/* TODO: user should be able define which exactly signals need convert to exceptions */
	signal(SIGFPE, fpe_handler);
}
