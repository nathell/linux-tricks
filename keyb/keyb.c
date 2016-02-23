#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/kd.h>
#include <signal.h>

#define DD 32*('a'-'A')

int main() {
	struct consolefontdesc cfd;
	int i, j, fd = open("/dev/tty", O_RDWR);
	cfd.chardata = (char *)malloc(16384);
	if (cfd.chardata == NULL) exit(0);
	cfd.charcount = 512;
	ioctl(fd, GIO_FONTX, &cfd);
	for (i = 32 * 'A'; i < 32 * ('Z' + 1); i++) {
		char tmp = cfd.chardata[i];
		cfd.chardata[i] = cfd.chardata[i + DD];
		cfd.chardata[i + DD] = tmp;
	}
	ioctl(fd, PIO_FONTX, &cfd);
}
