// No Header
// 18/12/2015 - 11:15:55

#ifndef _KFS_IRQ_H
#define _KFS_IRQ_H

#include "interrupts.h"
int		irq_init(uint8_t base);
void		irq_mask(uint32_t irq);
void		irq_unmask(uint32_t irq);
void		irq_send_eoi(void);
int		printk_from_kbd(uint8_t c);

/* KeyBoard */
void		kb_init(void);
uint8_t		kb_get_key(void);

/* Timer */
int		pit_init(uint16_t freq);
uint32_t	pic_update_tick(void);

#endif /* _KFS_IRQ_H */
