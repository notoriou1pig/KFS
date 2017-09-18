// No Header
// 30/01/2016 - 17:57:59

#include "kfs_type.h"
#include "misc.h"
#include "irq.h"

// Interrupt Request

/* ICW1 : 0b10001
** IWC4 set present
** Cascade mode
** edge trigged mode
*/

/* ICW2 :
** base -> start address Master Pic (after the 31's reserved interrupt)
** base + 0x8 -> start address Slave Pic (after the 39's Master IRQ)
*/

/* ICW3 :
** 0x04 -> IRQ2 cascade connected to Slave pic
** 0x02 -> Master Pic Pin 2 connected to Slave
*/

/* ICW4 :
** 0x01 -> Basic setting
*/

#define MASTER_A	0x20
#define MASTER_B	0x21
#define SLAVE_A		0xA0
#define SLAVE_B		0xA1

void		ICW(uint8_t base)
{
  printk("[IRQ][Send Initialization Command Words]\n");
  /* ICW1 */
  outb(MASTER_A, 0x11);
  outb(SLAVE_A, 0x11);

  /* ICW2 */
  outb(MASTER_B, base);
  outb(SLAVE_B, base + 0x08);

  /* ICW3 */
  outb(MASTER_B, 0x04);
  outb(SLAVE_B, 0x02);

  /* ICW4 */
  outb(MASTER_B, 0x01);
  outb(SLAVE_B, 0x01);
  printk("[IRQ][Initialization Command Words Sent]\n");
}  

/* No idea */
void		OCW1(void)
{
  outb(MASTER_B, 255);
  outb(SLAVE_B, 255);
}

int	irq_kbd(struct regs *r)
{
  uint8_t	c;

  c = kb_get_key();
  printk_from_kbd(c);
  (void)r;
  //dump_regs(r);
  return (0);
}

int	irq_pit(struct regs *r)
{
  pic_update_tick();
  printk("[PIT] TICK !!!");
  dump_regs(r);
  return (0);
}

int	irq_unmanaged(struct regs *r)
{  
  printk("unmanaged IRQ\n");
  dump_regs(r);
  return (0);
}

/*
** Description: Initialize PIC and set global interrupt flag.
** Arguments:
**	base: base offset in the IDT to use
**	      (Hint: the first 32 entries are reserved).
**  /!\ base have to be set at 32 ! Cause of assembly problem.
**      See isr.S
**  irq_send_eoi call in asm routine (see isr.S ==> irq macro)
*/
int	irq_init(uint8_t base)
{
  base = 32; //secure

  printk("[IRQ][Start initialing IRQ]\n");
  ICW(base);
  
  printk("[IRQ][Set IDT]\n");
  interrupts_set_isr(base, irq0, 0, &irq_unmanaged);
  interrupts_set_isr(base + 1, irq1, 0, &irq_kbd);
  interrupts_set_isr(base + 2, irq2, 0, &irq_unmanaged);
  interrupts_set_isr(base + 3, irq3, 0, &irq_unmanaged);
  interrupts_set_isr(base + 4, irq4, 0, &irq_unmanaged);
  interrupts_set_isr(base + 5, irq5, 0, &irq_unmanaged);
  interrupts_set_isr(base + 6, irq6, 0, &irq_unmanaged);
  interrupts_set_isr(base + 7, irq7, 0, &irq_unmanaged);
  interrupts_set_isr(base + 8, irq8, 0, &irq_unmanaged);
  interrupts_set_isr(base + 9, irq9, 0, &irq_unmanaged);
  interrupts_set_isr(base + 10, irq10, 0, &irq_unmanaged);
  interrupts_set_isr(base + 11, irq11, 0, &irq_unmanaged);
  interrupts_set_isr(base + 12, irq12, 0, &irq_unmanaged);
  interrupts_set_isr(base + 13, irq13, 0, &irq_unmanaged);
  interrupts_set_isr(base + 14, irq14, 0, &irq_unmanaged);
  interrupts_set_isr(base + 15, irq15, 0, &irq_unmanaged);
  printk("[IRQ][Done Setting IDT]\n");  

  OCW1();

  /* pit_init(1000); // Set frequency to 1000 Hz (eq 1 kHz) */
  kb_init();

  __asm__ __volatile__ ("sti");
  printk("[IRQ][IRQ Enabled]\n");
  return (0);
}

/*
** Description: Mask an IRQ (Hint: use OCW1)
** Arguments:
**	irq: irq number
** 0x21 is master port B
*/
void		irq_mask(uint32_t irq)
{
  uint8_t	tmp;
  uint8_t	ret;
  int		port = 0x21;

  if (irq > 7)
    {
      port = 0xA1;
      irq = irq - 8;
    }
  tmp = 1 << irq;
  ret = inb(port);
  tmp = ret | tmp;
  outb(port, tmp);
}

/*
** Description: Unmask an IRQ (Hint: use OCW1)
** Arguments:
**	irq: irq number
*/
void		irq_unmask(uint32_t irq)
{
  uint8_t	tmp;
  uint8_t	ret;
  int		port = 0x21;

  if (irq > 7)
    {
      port = 0xA1;
      irq = irq - 8;
    }
  tmp = 1 << irq;
  ret = inb(port);
  tmp = ret & ~tmp;
  outb(port, tmp);  
}

/*
** Description: Send EOI command to PIC (Hint: use OCW2)
** 0x20 is 0b00100000 to know the last interrupt
** 0x20 is also master PIC port A
** 0x40 is slave PIC port A
*/
void		irq_send_eoi(void)
{
  outb(MASTER_A, 0x20);
  outb(SLAVE_A, 0x20);
}
