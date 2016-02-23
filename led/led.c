#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/kd.h>

int main (int argc, char **argv) {
  int times, fd;
  char state;
  if (argc != 2)
    times = 250000;
  else
    times = atoi(argv[1]) * 1000;
  state = 0;
  fd = open ("/dev/tty", O_RDWR);
  for (;;) { 
    ioctl (fd, KDSETLED, state);
    state++;
    if (state == 8) 
      state = 0;
      usleep (times);
  } 
}
