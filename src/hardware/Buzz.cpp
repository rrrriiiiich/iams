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
  int ret = ioctl(buzz_fd, BUZZ_ON);
  if (ret == -1)
  {
    Log() << "ioctl BUZZ_ON failed";
  }
}

void Buzz::off()
{
  Log() << "off";
  int ret = ioctl(buzz_fd, BUZZ_OFF);
  if (ret == -1)
  {
    Log() << "ioctl BUZZ_OFF failed";
  }
}

#else

#endif // _LINUX
