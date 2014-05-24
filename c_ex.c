#include <stdio.h>

#include "c_ex.h"
#include "signals.h"

struct c_ex_exception_t *c_ex_current_exception = NULL;
unsigned c_ex_levels = 0;
jmp_buf c_ex_env[C_EX_MAX_LEVEL];
char c_ex_message[1024] = { '\0' };

/* Predefined exeption types */
struct c_ex_exception_t c_ex_exception_exception = {
	.parent = NULL,
	.name = "exception"
};
exception_ctor(exception)

int c_ex_exception_type_is(struct c_ex_exception_t *type)
{
	struct c_ex_exception_t *e = c_ex_current_exception;

	while (e) {
		if (e == type) {
			c_ex_current_exception = NULL;
			c_ex_levels = 1;
			return 1;
		}
		e = e->parent;
	}

	return 0;
}

void c_ex_prev_try()
{
	--c_ex_levels;
	if (c_ex_levels) {
		longjmp(c_ex_env[c_ex_levels - 1], 1);
	}
}

static void uncatched_exception()
{
	fprintf(stderr, "Uncatched exception '%s' occured: %s\n",
		c_ex_current_exception->name,
		c_ex_current_exception->msg);
	exit(1);
}

__attribute__ ((__constructor__)) static void init()
{
	signals_init();

	++c_ex_levels;
	if (setjmp(c_ex_env[0]) == STAGE_CATCH)
	{
		uncatched_exception();
	}
}
