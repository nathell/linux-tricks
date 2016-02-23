#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/kd.h>
#include <signal.h>

int main() {
	unsigned char ble[48];
	int i, dir = 1, fd = open("/dev/tty", O_RDWR);
	ioctl(fd, GIO_CMAP, ble);
	for (i = 0; i < 48; i++) ble[i] = 255 - ble[i];
	ioctl(fd, PIO_CMAP, ble);
}
