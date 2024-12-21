#ifndef _WIN32

#ifndef BUZZ_H
#define BUZZ_H

#include "Logger.h"

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define DEVICE_BUZZ "/dev/buzz_misc"

#define BUZZ_MAGIC 'b'

#define BUZZ_ON _IOW(BUZZ_MAGIC, 1, unsigned long)
#define BUZZ_OFF _IOW(BUZZ_MAGIC, 0, unsigned long)
}

class Buzz
{
public:
  Buzz();
  ~Buzz();

  void on();
  void off();

private:
  int buzz_fd;
};

#else

#endif // BUZZ_H

#endif // _LINUX
