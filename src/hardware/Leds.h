#ifndef _WIN32

#ifndef Leds_H
#define Leds_H

#include "Logger.h"

extern "C"
{
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
// 定义幻数
#define LEDS_MAGIC 'l'
// 定义命令的最大序数
#define LEDS_MAX_NR 4

// 定义LED的魔幻数
#define LED1 _IO(LEDS_MAGIC, 0)
#define LED2 _IO(LEDS_MAGIC, 1)
#define LED3 _IO(LEDS_MAGIC, 2)
#define LED4 _IO(LEDS_MAGIC, 3)

#define LED_ON 0
#define LED_OFF 1

#define DEVCIE_LEDS "/dev/leds_misc"
}

class Leds
{
public:
  Leds();
  ~Leds();

  void on(int led_command = 0);
  void off(int led_command = 0);

private:
  int leds_fd;
};

#else

#endif // Leds_H

#endif // _LINUX
