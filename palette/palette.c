#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/kd.h>
#include <signal.h>

int fd;
unsigned char ble[48];

void handle_sig(int signum) {
	ioctl(fd, PIO_CMAP, ble);
	exit(0);
}

/* intens od 0 do 255 */
void fade(int intens, unsigned char *in, unsigned char *out) {
	int temp, i;
	for (i = 0; i < 48; i++) {
		temp = in[i];
		out[i] = (unsigned char)(temp * intens / 255);
	}
}

int main() {
	unsigned char rob[48];
	int intens = 254, dir = 1;
	fd = open("/dev/tty", O_RDWR);
	ioctl(fd, GIO_CMAP, ble);
	signal(SIGINT, handle_sig);
	for (;;) {
		fade(intens, ble, rob);
		ioctl(fd, PIO_CMAP, rob);
		usleep(1);
		if (dir) intens-=2; else intens+=2;
		if (intens == 0 || intens == 254) dir = 1 - dir;
	}
}
