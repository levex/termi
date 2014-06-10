#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <termi/pty.h>
#include <termi/terminal.h>
#include <termi/test.h>

#define EXIT(err, str) do { \
			printf("ERROR %d: %s", err, str); \
			exit(err); \
		} while(0);

terminal_t __test_term = {
	.receive_char = test_term_receive,
	.init_instance = test_term_init,
};

int main(int argc, char *argv[])
{
	int fdmaster = -1;
	int rc, termid;
	const char *pts;
	char buf[32];
	terminal_t *term;

	termid = register_terminal(&__test_term);
	if (termid < 0)
		EXIT(termid, "unable to register test terminal\n");

	term = grab_terminal(termid);
	if (term == NULL)
		EXIT(1, "unable to grab the test terminal\n");
	
	/* open a master pty */
	fdmaster = posix_openpt(O_RDWR | O_NOCTTY);
	if (fdmaster < 0)
		EXIT(fdmaster, "failed to open a master pty!\n");

	/* grant access to pty */
	rc = grantpt(fdmaster);
	if (rc)
		EXIT(rc, "failed to grantpt!\n");

	/* now we need to unlock the spty */
	rc = unlockpt(fdmaster);
	if (rc)
		EXIT(rc, "failed to unlock master pty!\n");

	/* now let us get the name of the pty */
	pts = ptsname(fdmaster);
	if (!pts)
		EXIT(1, "no name for pty!\n");
	printf("Created pseudo tty: %s\n", pts);

	/* let's invoke an infinite read on it */
	while (1) {
		int nread, i;

		nread = read(fdmaster, buf, 32);
		if (nread < 0) {
			lseek(fdmaster, 0, SEEK_SET);
			continue;
		}
		
		for(i = 0; i < nread; i++) {
			term->receive_char(term, buf[i]);
		}
	}

	exit(0);
}
