// No Header
// 30/01/2016 - 17:57:16

#include "interrupts.h"
#include "print_fct.h"

static char	*isr_msg[16] =
  {
    "Divide by Zero Exception\n",		/* Int 0x0  */
    "Debug Exception\n",			/* Int 0x1  */
    "Non Maskable Interrupt Exception\n",	/* Int 0x2  */
    "Breakpoint Exception\n",			/* Int 0x3  */
    "Into Detected Overflow Exception\n",	/* Int 0x4  */
    "Out of Bounds Exception\n",		/* Int 0x5  */
    "Invalid Opcode Exception\n",		/* Int 0x6  */
    "No Coprocessor Exception\n",		/* Int 0x7  */
    "Double Fault Exception\n",			/* Int 0x8  */
    "Coprocessor Segment Overrun Exception\n",	/* Int 0x9  */
    "Bad TSS Exception\n",			/* Int 0xA */
    "Segment Not Present Exception\n",		/* Int 0xB */
    "Stack Fault Exception\n",			/* Int 0xC */
    "General Protection Fault Exception\n",	/* Int 0xD */
    "Page Fault Exception\n",			/* Int 0xE */
    "Error in Exception Managing\n"		/* Error    */
  };

int		isr_reserv(struct regs *r)
{
  printk("Reserved ISR\n");
  dump_regs(r);
  return (0);
}

int		isr_unmanaged(struct regs *r)
{
  printk("Unmanaged ISR\n");
  dump_regs(r);
  return (0);
}

int		isr_common(struct regs *r)
{
  printk(isr_msg[r->int_no]);
  dump_regs(r);
  printk("System Looping _96_\n");
  while (96);
  return (0);
}

int		interrupt_switcher(struct regs *r)
{
  _idt_ftab[r->int_no](r);
  return (0);
}
