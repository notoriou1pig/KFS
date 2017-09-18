// No Header
// 18/12/2015 - 15:08:29

#ifndef _KFS_PRINT_FCT_H
#define _KFS_PRINT_FCT_H

#include "kfs_type.h"
#include "interrupts.h"

// Frame Buffer
void	write_frame_buffer(char);

// Serial Port
void	write_serial_port(char);

// Putstr Fcts
void	putchark(const char);
void	printk(const char *);

// Putnbr Fcts
void	printk_oct(uint8_t);
void	printk_nbr(int);
void	printk_long(uint64_t);

void	printk_oct_hex(uint8_t);
void	printk_hex(uint32_t);
void	printk_long_hex(uint64_t);

void	printk_oct_bin(uint8_t);
void	printk_bin(uint32_t);
void	printk_long_bin(uint64_t);

// Dump Registers
int	dump_regs(struct regs *);

#endif /* !_KFS_PRINT_FCT_H */
