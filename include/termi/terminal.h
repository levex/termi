#ifndef __TERMINAL_H
#define __TERMINAL_H

struct termi_terminal__t__;

typedef struct termi_terminal__t__ {

/* variables */
	int in_use;

/* functions */
	int (*init_instance)(struct termi_terminal__t__ *term);
	int (*receive_char)(struct termi_terminal__t__ *term, char c);

} terminal_t;

int register_terminal(terminal_t *t);
terminal_t *grab_terminal(int id);

#endif /* __TERMINAL_H */
