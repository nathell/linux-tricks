#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/kd.h>
#include <signal.h>

int main() {
	struct consolefontdesc cfd;
	int i, j, fd = open("/dev/tty", O_RDWR);
	cfd.chardata = (char *)malloc(16384);
	if (cfd.chardata == NULL) exit(0);
	cfd.charcount = 512;
	ioctl(fd, GIO_FONTX, &cfd);
	for (i = 0; i < cfd.charcount; i++) for (j = 0; j < 8; j++) {	
		char tmp = cfd.chardata[32 * i + j];
		cfd.chardata[32 * i + j] = cfd.chardata[32 * i + 15 - j];
		cfd.chardata[32 * i + 15 - j] = tmp;
	}
	ioctl(fd, PIO_FONTX, &cfd);
}
