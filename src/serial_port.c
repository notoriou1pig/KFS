// No Header
// 12/01/2016 - 00:04:11

#include "misc.h"

void	init_serial_port()
{
  outb(PORT_COM1+1, 0x00);
  outb(PORT_COM1+3, 0x80);
  outb(PORT_COM1, 0x03);
  outb(PORT_COM1+1, 0x00);
  outb(PORT_COM1+3, 0x03);
  outb(PORT_COM1+2, 0xC7);
  outb(PORT_COM1+4, 0x0B);
}

void	write_serial_port(char c)
{
  outb(PORT_COM1, c);
  if (c == '\b')
    {
      outb(PORT_COM1, ' ');
      outb(PORT_COM1, c);
    }
}
