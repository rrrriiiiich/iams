#ifndef _WIN32
#include "Buzz.h"

Buzz::Buzz()
{
  buzz_fd = ::open(DEVICE_BUZZ, O_RDWR); // 打开设备，成功返回0
  Log() << "open buzz:" << buzz_fd;
  if (buzz_fd == -1)
  {
    fprintf(stderr, "Can not open %s : %s !\n", DEVICE_BUZZ, strerror(errno));
  }
}

Buzz::~Buzz()
{
  ::close(buzz_fd);
}

void Buzz::on()
{
  Log() << "on";
  ioctl(buzz_fd, BUZZ_ON);
}

void Buzz::off()
{
  Log() << "off";
  ioctl(buzz_fd, BUZZ_OFF);
}

#else

#endif // _LINUX
