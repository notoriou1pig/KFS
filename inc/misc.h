// No Header
// 12/01/2016 - 00:04:23

#ifndef _KFS_MISC_H
#define _KFS_MISC_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define PORT_COM1 0x3F8
#define TAB_SIZE 4

#include "print_fct.h"

char	inb(int);
#define outb(port, val) __asm__ __volatile__ ("outb %%al,%%dx":		\
					      :"d" (port), "a" (val));
void	init_frame_buffer();
void	init_serial_port();

#endif /* _KFS_MISC_H */
