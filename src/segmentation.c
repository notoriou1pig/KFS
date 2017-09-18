// No Header
// 15/12/2015 - 12:42:15

#include "segmentation.h"
#include "print_fct.h"

_gdt_entry	_gdt[3];

/*
** Description: Set a GDT entry.
** Arguments:
**         n: entry index
**         base: segment base address
**         limit: segment limit
**         access: segment access attributes
**         granularity: segment limit granularity
*/
static int	set_gdt_entry(int n, uint32_t base, uint32_t limit,	\
			      uint8_t access, uint8_t gran)
{
  _gdt_entry	e_gdt;

  if (gran != 0)
    gran = 0xcf;

  e_gdt.l_limit = limit	& 0x0000FFFF;
  e_gdt.l_base	= base	& 0x0000FFFF;

  e_gdt.m_base	= (base	& 0x00FF0000) >> 16;
  e_gdt.access	= access;
  e_gdt.h_limit = (limit & 0x000F0000) >> 16;
  e_gdt.flags	= (gran	& 0xF0) >> 4;
  e_gdt.h_base	= (base	& 0xFF000000) >> 24;

  _gdt[n] = e_gdt;
  return (0);
}

/*
** Description: This function sets a GDT in order to get a flat memory model.
** It must reloads the segment selectors according to the new GDT.
** A minimal GDT will be:
**         Null segment
**         Kernel code segment
**         Kernel data segment
*/
void		init_flat_gdt(void)
{
  printk("[GDT][Start loading flat model]\n");
  _gdtr		r_gdt;

  r_gdt.limit = sizeof(_gdt) - 1;
  r_gdt.base = (uint32_t)&_gdt;

  printk("[GDT][Init GDT]\n");
  /* NULL Segment */
  set_gdt_entry(0, 0, 0, 0, 0);

  /* Kernel Code Segment */
  set_gdt_entry(1,
		0,
		0xFFFFFFFF,
		_GDT_CODE(_GDT_RW),
		_GDT_GRAN(_GDT_32B));

  /* Kernel Data Segment */
  set_gdt_entry(2,
		0,
		0xFFFFFFFF,
 		_GDT_DATA(_GDT_RW),
  		_GDT_GRAN(_GDT_32B));

  /* load GDT */
  printk("[GDT][Loading GDT]\n");
  __asm__ volatile("lgdt %0\n"
  		   : /* no output */
  		   : "m" (r_gdt)
  		   : "memory");

  /* reload segment selectors : gdt.S */
  printk("[GDT][Reloading segment selectors]\n");
  init_seg_reg();

  /* Done =D */
  printk("[GDT][Done loading flat model]\n\n");
}
