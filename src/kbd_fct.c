// No Header
// 15/01/2016 - 00:13:24

#include "misc.h"
#include "irq.h"
#include "kb.h"

int		printk_from_kbd(uint8_t c)
{
  int	i;

  i = 0;
  while (i != 85 && keymap[i].code != c)
    i++;
  if (i == 85)
    return (1);
  putchark(keymap[i].charac);
  return (0);
}

void		kb_init(void)
{
  irq_unmask(IRQ_KEYBOARD);
}

uint8_t		kb_get_key(void)
{
  uint8_t	ret;
  do {
    ret = inb(0x64);
  } while ((ret & 0x01) == 0);
  ret = inb(0x60);
  return (ret);
}

