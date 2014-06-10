#include <termi/termi.h>
#include <termi/test.h>

#include <stdio.h>
#include <gtk/gtk.h>

int test_term_init(terminal_t *term)
{
	GtkWidget *window;
	int p_pid = getpid();
	int c_pid = -1;
	c_pid = fork();
	if (!c_pid) {
		gtk_init(0, 0);
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "Termi");
		gtk_widget_show(window);

		gtk_main();
	}

	printf("initialized test terminal with window %d\n", c_pid);
	return 0;
}

int test_term_receive(terminal_t *term, char c)
{
	putchar(c);
	return 0;
}
