// No Header
// 15/01/2016 - 08:00:36

#include "interrupts.h"
#include "print_fct.h"

/*
** Description:
** Arguments:
**        n: interrupt index
**        handler: pointer to the IRQ handler
**        flags:
**              ISR_USER: the user can call it
*/
void		interrupts_set_isr(int n, isr_handler handler, int flags, _idt_call func)
{
  _idt_entry	e_idt;

  e_idt.l_base = (int)handler & 0xFFFF;
  e_idt.selector = 0x8;
  e_idt.zero = 0;
  if (flags != 0)
    e_idt.flag = 0x8E | 0x60;
  else
    e_idt.flag = 0x8E;
  e_idt.h_base = ((int)handler >> 16) & 0xFFFF;

  _idt[n] = e_idt;
  _idt_ftab[n] = func;
}

static void	set_reserved_int()
{
  int		i;

  i = 15;
  while (i < 32)
    interrupts_set_isr(i++, isr_reserved, 0, &isr_reserved);
}

static void	set_unpresent_int()
{
  int		i;

  i = 32;
  while (i < 256)
    interrupts_set_isr(i++, isr_nodef, 0, &isr_unmanaged);
}

int	isr_page_fault(struct regs *r)
{
  uint32_t cr2;
  asm volatile("mov %%cr2, %0": "=r"(cr2));
  printk_hex(cr2);
  printk("\nSystem Looping _96_\n");
  while (96);
  (void)r;
  /* dump_regs(r); */
  return (0);
}

/*
** Description: Initialize an IDT and fill it with interrupt gates.
** The first 32 entries must point to a default ISR handler which prints
** the cause of the exception, the saved context and the error code.
** The others must be set as "not present".
*/
void		init_interrupts(void)
{
  printk("[IDT][Start loading IDT]\n");
  _idtr		r_idt;

  r_idt.limit = sizeof(_idt) - 1;
  r_idt.base = (uint32_t)&_idt;

  printk("[IDT][Init IDT]\n");
  interrupts_set_isr(0, isr0, 0, &isr_common);
  interrupts_set_isr(1, isr1, 0, &isr_common);
  interrupts_set_isr(2, isr2, 0, &isr_common);
  interrupts_set_isr(3, isr3, 0, &isr_common);
  interrupts_set_isr(4, isr4, 0, &isr_common);
  interrupts_set_isr(5, isr5, 0, &isr_common);
  interrupts_set_isr(6, isr6, 0, &isr_common);
  interrupts_set_isr(7, isr7, 0, &isr_common);
  interrupts_set_isr(8, isr8, 0, &isr_common);
  interrupts_set_isr(9, isr9, 0, &isr_common);
  interrupts_set_isr(10, isr10, 0, &isr_common);
  interrupts_set_isr(11, isr11, 0, &isr_common);
  interrupts_set_isr(12, isr12, 0, &isr_common);
  interrupts_set_isr(13, isr13, 0, &isr_common);
  interrupts_set_isr(14, isr14, 0, &isr_page_fault);
  interrupts_set_isr(15, isr15, 0, &isr_common);
  set_reserved_int();
  set_unpresent_int();

  printk("[IDT][loading IDT]\n");
  __asm__ volatile("lidt %0\n"
		   : /* no output */
		   : "m" (r_idt)
		   : "memory");

  irq_init(BASE_IRQ);
  printk("[IDT][Done loading IDT]\n\n");
}
