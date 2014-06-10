#include <termi/termi.h>

static terminal_t **terminals;
static int terms;

int register_terminal(terminal_t *term)
{
	if (!term)
		return -EINVAL;
	
	if (!terminals) {
		terminals = malloc(sizeof(terminal_t *) * MAX_TERMINALS);
		if (!terminals)
			return -ENOMEM;
	}

	terminals[terms] = term;

	term->in_use = 0;

	return terms ++;
}

terminal_t *grab_terminal(int id) {
	if (terminals[id]->in_use)
		return NULL;

	terminals[id]->in_use = 1;
	return terminals[id];
}
