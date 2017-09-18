// No Header
// 18/12/2015 - 11:16:11

#ifndef _KFS_PIT_H
#define _KFS_PIT_H

#define IRQ_PIT	0

int		pit_init(uint16_t freq);
uint32_t	pit_get_ticks(void);

#endif /* !_KFS_PIT_H */
