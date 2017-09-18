// No Header
// 15/12/2015 - 12:01:32

#ifndef _KFS_SEGMENTATION_H
#define _KFS_SEGMENTATION_H

#include "kfs_type.h"

extern void	init_seg_reg();
void		init_flat_gdt(void);

struct		s_gdt_register
{
  uint16_t	limit;		// 0-15
  uint32_t	base;		// 16-47
} __attribute__	((packed));

struct	s_gdt_entry
{
  union {
    struct {
      uint16_t	l_limit;	// 0-15
      uint16_t	l_base;		// 0-15
    };
    uint32_t	low;		// 0-31
  };
  union {
    struct {
      uint8_t	m_base;		// 16-23
      uint8_t	access;
      union {
	struct {
	  uint8_t	h_limit : 4;	// 16-19
	  uint8_t	flags : 4;
	};
	uint8_t		f;
      };
      uint8_t	h_base;		// 24-31
    };
    uint32_t	high;
  };
} __attribute__ ((packed));

typedef struct s_gdt_register	_gdtr;
typedef struct s_gdt_entry	_gdt_entry;

#define _GDT_HIGH_GRAN (1 << 3)
#define _GDT_32B (1 << 2)
#define _GDT_GRAN(v) (v << 4)

/*
** Don't Know what is _GDT_ACCESS 
** _GDT_RW grant read right in code segment
**	     and write right in data segment
** Don't Know what is_GDT_EXPAND 
** Don't Know what is_GDT_CONFORM
** 
** Use _GDT_RINGED to set ring level to 3
**
** _GDT_PRES set Present segment to true //Don't use
** Use _GDT_DATA to Data Segment
** Use _GDT_CODE to Data Segment
*/
//USE IT WITH OR '|'
#define _GDT_ACCESS	(1)
#define _GDT_RW		(1 << 1)
#define _GDT_EXPAND	(1 << 2)
#define _GDT_CONFOM	(1 << 2)
#define _GDT_RINGED(f)	(3 << 5) | f 
#define _GDT_PRES(f)	(1 << 7) | f
#define _GDT_DATA(f)	(1 << 4) | _GDT_PRES(f)
#define _GDT_CODE(f)	(1 << 4) | (1 << 3) | _GDT_PRES(f)

/*
** Expand Access flag
      Expand   Write   Access
0  0  0        0       0       Data         Read-Only
1  0  0        0       1       Data         Read-Only, accessed
2  0  0        1       0       Data         Read/Write
3  0  0        1       1       Data         Read/Write, accessed
4  0  1        0       0       Data         Read-Only, expand-down
5  0  1        0       1       Data         Read-Only, expand-down, accessed
6  0  1        1       0       Data         Read/Write, expand-down
7  0  1        1       1       Data         Read/Write, expand-down, accessed

      Conform  Read    Access
8  1  0        0       0       Code        Execute-Only
9  1  0        0       1       Code        Execute-Only, accessed
10 1  0        1       0       Code        Execute/Read
11 1  0        1       1       Code        Execute/Read, accessed
12 1  1        0       0       Code        Execute-Only, conforming
13 1  1        0       1       Code        Execute-Only, conforming, accessed
14 1  1        1       0       Code        Execute/Read, conforming
15 1  1        1       1       Code        Execute/Read, conforming, accessed
*/

#endif /* _KFS_SEGMENTATION_H */
