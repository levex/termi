#include <termi/termi.h>
#include <termi/test.h>

#include <stdio.h>


int test_term_receive(terminal_t *term, char c)
{
	putchar(c);
	return 0;
}
