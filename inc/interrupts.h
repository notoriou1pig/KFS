// No Header
// 18/12/2015 - 14:55:50

#ifndef _KFS_INTERRUPTS_H
#define _KFS_INTERRUPTS_H

#include "kfs_type.h"

#define BASE_IRQ 32
#define ISR_USER 1

struct		s_idt_register
{
  uint16_t	limit;		// 0-15
  uint32_t	base;		// 16-47
} __attribute__	((packed));

struct	regs
{
  uint32_t ds;                  // Data segment selector
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
  uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
  uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} __attribute__ ((packed));

struct		s_idt_entry
{
  uint16_t	l_base;		// 0-15
  uint16_t	selector;
  uint8_t	zero;
  union {
    struct {
      uint8_t	type : 4;
      uint8_t	attribute : 4;
    };
    uint8_t	flag;
  };
  uint16_t	h_base;		// 16-31
} __attribute__ ((packed));

typedef	int	(*isr_handler)(struct regs* regs);
typedef struct s_idt_register	_idtr;
typedef struct s_idt_entry	_idt_entry;
typedef int	(* _idt_call)(struct regs *r);

/* IDT && TAB_PTR */
_idt_entry	_idt[256];
_idt_call	_idt_ftab[256];

extern int	isr0(struct regs*);
extern int	isr1(struct regs*);
extern int	isr2(struct regs*);
extern int	isr3(struct regs*);
extern int	isr4(struct regs*);
extern int	isr5(struct regs*);
extern int	isr6(struct regs*);
extern int	isr7(struct regs*);
extern int	isr8(struct regs*);
extern int	isr9(struct regs*);
extern int	isr10(struct regs*);
extern int	isr11(struct regs*);
extern int	isr12(struct regs*);
extern int	isr13(struct regs*);
extern int	isr14(struct regs*);
extern int	isr15(struct regs*);
extern int	isr_reserved(struct regs*);

/* Interrupt List
** 0  - Division by zero exception
** 1  - Debug exception
** 2  - Non maskable interrupt
** 3  - Breakpoint exception
** 4  - 'Into detected overflow'
** 5  - Out of bounds exception
** 6  - Invalid opcode exception
** 7  - No coprocessor exception
** 8  - Double fault (pushes an error code)
** 9  - Coprocessor segment overrun
** 10 - Bad TSS (pushes an error code)
** 11 - Segment not present (pushes an error code)
** 12 - Stack fault (pushes an error code)
** 13 - General protection fault (pushes an error code)
** 14 - Page fault (pushes an error code)
** 15-31 - Reserved
*/

extern int	irq0(struct regs*);
extern int	irq1(struct regs*);
extern int	irq2(struct regs*);
extern int	irq3(struct regs*);
extern int	irq4(struct regs*);
extern int	irq5(struct regs*);
extern int	irq6(struct regs*);
extern int	irq7(struct regs*);
extern int	irq8(struct regs*);
extern int	irq9(struct regs*);
extern int	irq10(struct regs*);
extern int	irq11(struct regs*);
extern int	irq12(struct regs*);
extern int	irq13(struct regs*);
extern int	irq14(struct regs*);
extern int	irq15(struct regs*);

/*
** IRQ List
*/

extern int	isr_nodef(struct regs*);
void		interrupts_set_isr(int n, isr_handler handler, int flags, _idt_call);
void		init_interrupts(void);
int		irq_init(uint8_t base);

int		isr_reserv(struct regs *);
int		isr_unmanaged(struct regs *);
int		isr_common(struct regs *);
int		interrupt_switcher(struct regs *);


#endif /* _KFS_INTERRUPTS_H */
