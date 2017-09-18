// No Header
// 30/01/2016 - 18:02:11

#include "misc.h"
#include "irq.h"
#include "pit.h"

#define PIT_CONTROL_PORT	0x43 // Control port of PIT
#define PIT_COUNT1_PORT		0x40 // Fire int at define frequency
#define PIT_COUNT2_PORT		0x41 // Not Use Anymore 
#define PIT_COUNT3_PORT		0x42 // Link to Speaker PC

#define INTERN_FREQ		1193182 //Hertz

/* Configure Pit in mode 2 with freq */
int     pit_init(uint16_t freq)
{
  outb(PIT_CONTROL_PORT, 0x00110100);
  outb(PIT_COUNT1_PORT, freq >> 8);
  outb(PIT_COUNT1_PORT, freq);
  printk_bin(freq);
  putchark('\n');
  printk_oct_bin(freq >> 8);
  putchark('\n');
  printk_oct_bin(freq);
  /* irq_unmask(IRQ_PIT); */
  return (0);
}

static uint32_t	pic_tick(uint8_t b)
{
  static uint32_t	tick = 0;

  if (b == 1)
    tick++;
  return (tick);
}

uint32_t	pic_update_tick(void)
{
  return (pic_tick(1));
}

uint32_t	pit_get_ticks(void)
{
  return (pic_tick(0));
}
