#ifndef _WIN32
#include "Leds.h"

Leds::Leds()
{
  leds_fd = open(DEVCIE_LEDS, O_RDWR); // 打开设备下的LED，成功返回0
  Log() << "open leds:" << leds_fd;
  if (leds_fd == -1)
  {
    Log() << "Can not open " << DEVCIE_LEDS << ":" << strerror(errno);
    return;
  }
}

Leds::~Leds()
{
  ::close(leds_fd);
}

void Leds::on(int led_command)
{
  Log() << led_command << "on";
  if (led_command == 0)
  {
    // 打开所有灯
    ioctl(leds_fd, LED1, LED_ON);
    ioctl(leds_fd, LED2, LED_ON);
    ioctl(leds_fd, LED3, LED_ON);
    ioctl(leds_fd, LED4, LED_ON);
  }

  ioctl(leds_fd, led_command, LED_ON);
}

void Leds::off(int led_command)
{
  Log() << led_command << "off";
  if (led_command == 0)
  {
    // 关闭所有灯
    ioctl(leds_fd, LED1, LED_OFF);
    ioctl(leds_fd, LED2, LED_OFF);
    ioctl(leds_fd, LED3, LED_OFF);
    ioctl(leds_fd, LED4, LED_OFF);
  }
  ioctl(leds_fd, led_command, LED_OFF); // 1灯灭
}

#else

#endif // _LINUX
