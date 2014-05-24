#include <stdio.h>

#include "c_ex.h"
#include "signals.h"

/*
 * logic_error is an example of inherited exception. All exception must derived
 * from 'exception'.
 * If you want to use new exception type in several files then you need
 * to declate it in header (declare_exception) and define in (source define_exception).
 */
define_exception(logic_error, exception);

/* Test simple exception */
void test_1()
{
	try {
		puts("test1:start");
		throw(exception("test_1 exception"));
		puts("test1:middle (if you see it then something wrong");
	} catch (exception, e) {
		printf("Exception '%s' catched: %s\n", e->name, e->msg);
	}
	puts("test1:end\n");
}

/* Test inherited exception */
void test_2()
{
	try {
		puts("test2:start");
		throw(logic_error("test_2 exception"));
		puts("test2:middle (if you see it then something wrong)");
	} catch (exception, e) {
		printf("Exception '%s' catched: %s\n", e->name, e->msg);
	}
	puts("test2:end\n");
}

/* Test nested try blocks */
void test_3()
{
	try {
		puts("test3:start");
		try {
			throw(exception("test_3 exception"));
		} catch (logic_error, e) {
			printf("Exception '%s' catched in nested 'try' block"
				"(if you see it then something wrong): %s\n", e->name, e->msg);
		}
	} catch (exception, e) {
		printf("Exception '%s' catched: %s\n", e->name, e->msg);
	}

	puts("test3:end\n");
}

void test_4()
{
	puts("test4:start");
	try {
		/* Not optimize that variable */
		volatile int zero = 0;
		zero /= zero;
	} catch (floating_point, e) {
		printf("Exception '%s' catched (division be zero): %s\n", e->name, e->msg);
	}
	puts("test5:end\n");
}

/* Test uncatched exception. Programm will terminate during that test */
void test_5()
{
	puts("test5:start");
	try {
		throw(exception("test_5 exception"));
	} catch (logic_error, e) {
		printf("Exception '%s' catched (if you see it then something wrong): %s\n",
			e->name, e->msg);
	}
}

int main(void)
{
	test_1();
	test_2();
	test_3();
	test_4();
	test_5();

	return 0;
}
