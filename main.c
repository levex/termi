#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define _XOPEN_SOURCE
#include <stdlib.h>
extern char *ptsname(int fd);

#define EXIT(err, str) do { \
			printf("ERROR %d: %s", err, str); \
			exit(err); \
		} while(0);

int main(int argc, char *argv[])
{
	int fdmaster = -1;
	int rc;
	int sfd;
	const char *pts;
	struct stat ps;
	char buf[32];

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
			putchar(buf[i]);
		}
	}

	exit(0);
}
