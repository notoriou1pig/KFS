// No Header
// 15/01/2016 - 10:10:46

#ifndef _KFS_FRAME_ALLOC_H
#define _KFS_FRAME_ALLOC_H

#include "multiboot.h"
extern uint32_t	kernel_start_addr;
extern uint32_t	kernel_end_addr;

#define FRAME_SIZE 0x1000 //4kio

/*
** Struct for page_directory_entry && page_table_entry.
** Common is arranged like :
** 0 - Present in physical memory
** 1 - Page is Read/Write
** 2 - Access Level (set is access for everyone)
** 2 - PAGE DIR : Control for all page in the directory
** 3 - Write Through
** 4 - Cached bit, set if page will be cached
** 5 - Accessed bit !????? (cf. ASK_THEM)
** - Flag for Page_Dir_entry :
** 0 - zero
** 1 - Page size --> 4K or 4M
** 2 - Ignored
** - Flag for Page_Table_entry :
** 0 - Set if the page has been writtent
** 1 - zero
** 2 - Global flag !???? (cf. ASK_THEM)
*/
struct		s_page
{
  union {
    struct {
      uint8_t	common	: 6;
      uint8_t	flag	: 3;
      uint8_t	avail	: 3;
      uint32_t	physaddr: 20;
    } __attribute__ ((packed));
    uint32_t	addr;
  };
} __attribute__ ((packed));

typedef struct s_page	page_dir;
typedef struct s_page	page_tab;

/*
** Describes a physical address.
** Since paging is enabled, it is not possible to dereference this address.
*/
typedef unsigned int	phys_t;

/*
** A structure which describes a frame. It should contain:
**	     a reference counter
**	     a virtual  address where the frame is mapped
**           a physical address where the frame is mapped
*/
struct			frame
{
  phys_t		p_addr;    //physical address
  uint32_t		v_addr;    //virtual address
  uint8_t		ref_count; //if set, frame is use
} __attribute__ ((packed));


/* FRAME */
void		init_frame_alloc(multiboot_info_t *multiboot);
struct frame*	alloc_frame(void);
int		alloc_frames(int n, struct frame **frames);
void		free_frame(struct frame *frame);
phys_t		frame_to_phys(struct frame *frame);
struct frame*	phys_to_frame(phys_t addr);

/* PAGES */
void*		alloc_pages(struct frame* pdbr, uint32_t size);
int		map_pages(struct frame* pdbr,
			  void* vaddr,
			  struct frame *frames,
			  uint32_t size,
			  int flags);
void		*map_io(struct frame* pdbr, phys_t ioaddr, uint32_t len);
void		unmap_pages(struct frame *pdbr, void *vaddr, int n);

#endif /* !_KFS_FRAME_ALLOC_H */
