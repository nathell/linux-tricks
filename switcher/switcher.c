#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/vt.h>
#include <signal.h>

#define DD 32*('a'-'A')

int main() {
	int i = 1, fd = open("/dev/tty", O_RDWR);
  for (;;) {
    ioctl(fd, VT_ACTIVATE, i);
    i++;
    if (i == 8) i = 1;
    usleep(100000);
  }
}
