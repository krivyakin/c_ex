#ifndef __C_EX_H__
#define __C_EX_H__

#include <setjmp.h>
#include <stdlib.h>
#include <string.h>


#define exception_ctor(type)						\
void type(const char *msg) {						\
	c_ex_current_exception = &c_ex_exception_##type;		\
	strncpy(c_ex_message, msg, sizeof(c_ex_message) - 1);		\
	c_ex_current_exception->msg = c_ex_message;			\
}

#define exception_type(type, p)						\
struct c_ex_exception_t c_ex_exception_##type = {			\
	.parent = &c_ex_exception_##p,					\
	.name = #type							\
};									\

#define define_exception(type, p)					\
exception_type(type, p)							\
exception_ctor(type)

#define declare_exception(type, p)					\
extern struct c_ex_exception_t c_ex_exception_##type;				\
extern void type(const char *msg);

#define try								\
	++c_ex_levels;							\
	for (int stage = setjmp(c_ex_env[c_ex_levels - 1]);		\
		stage < STAGE_OUT; ++stage)				\
		if (c_ex_current_exception && stage == STAGE_PREV_TRY) {\
			c_ex_prev_try();				\
		} else if (stage == STAGE_TRY)				\

#define catch(type, name)						\
	else if (stage == STAGE_CATCH)					\
		for (struct c_ex_exception_t *name = c_ex_current_exception;\
			name && c_ex_exception_type_is(			\
				&c_ex_exception_##type);)

#define throw(e)							\
do {									\
	e;								\
	longjmp(c_ex_env[c_ex_levels - 1], STAGE_CATCH);		\
} while (0)

#define C_EX_MAX_LEVEL 10

struct c_ex_exception_t
{
	struct c_ex_exception_t *parent;
	const char *name;
	char *msg;
};

enum c_ex_stage
{
	STAGE_TRY = 0,
	STAGE_CATCH = 1,
	STAGE_PREV_TRY = 2,
	STAGE_OUT = 3,
};

extern struct c_ex_exception_t *c_ex_current_exception;
extern unsigned c_ex_levels;
extern jmp_buf c_ex_env[C_EX_MAX_LEVEL];
extern char c_ex_message[1024];
extern struct c_ex_exception_t c_ex_exception_exception;

int c_ex_exception_type_is(struct c_ex_exception_t *type);
void c_ex_prev_try();
void exception(const char *msg);

#endif /* __C_EX_H__ */
