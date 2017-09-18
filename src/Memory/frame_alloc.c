// No Header
// 17/01/2016 - 21:32:15

#include "misc.h"
#include "Memory/frame_alloc.h"

page_dir	*page_directory;
page_tab	*page_table;
phys_t		phys_memory_addr;
phys_t		end_phys_memory_addr;
struct frame	*frame_addr;
struct frame	*frame_directory;

void		enable_paging(void)
{
  int		i;
  uint32_t	addr;

  // Set Page Directory and Page table to seconde page of 4M
  page_directory = (page_dir*)&kernel_end_addr;
  //align the pointer !!
  page_directory = (page_dir*)((uint32_t)page_directory & (uint32_t)0xfffff000);
  page_directory += 0x1000;

  //Identity Paging with only 4M pages
  i = 0;
  addr = 0;
  while (i < 1024)
    {
      page_directory[i++].addr = addr | 0b10000011;
      addr += 0x400000;
    }

  //set page_table into memory
  page_table = (page_tab*)&page_directory[i];
  i = 0;
  while (i < 1023) //Only 1023 cause first 4M is for Kernel code.
    page_table[i++].addr = 0x0;
  
  //Enable 4M Pages
  __asm__ volatile("mov %cr4, %eax");
  __asm__ volatile("or $0x10, %eax");
  __asm__ volatile("mov %eax, %cr4");

  //Give page_directory addr to CPU
  __asm__ volatile("mov %0, %%eax" :: "r"((uint32_t)page_directory));
  __asm__ volatile("mov %eax, %cr3");

  //Enable Paging
  __asm__ volatile("mov %cr0, %eax");
  __asm__ volatile("or $0x80000000, %eax");
  __asm__ volatile("mov %eax, %cr0");

  //Paging Done
}

// Naive implem ==> Possible to get frame with address trick
struct frame*	phys_to_frame(phys_t addr)
{
  struct frame	*tmp;

  tmp = frame_addr;
  while (tmp->ref_count != 255 && tmp->p_addr != addr)
    tmp += sizeof(struct frame);
  return (tmp);
}

// Naive implem ==> Possible to get phys_t with address trick
phys_t		frame_to_phys(struct frame *frame)
{
  return (frame->p_addr);
}

void		free_frame(struct frame *frame)
{
  frame->v_addr = 0;
  frame->ref_count = 0;
}

uint32_t	get_kernel_size()
{
  return ((uint32_t)&kernel_end_addr - (uint32_t)&kernel_start_addr);
}

struct frame*	alloc_frame(void)
{
  struct frame	*new_frame;

  new_frame = frame_directory;
  new_frame->p_addr = phys_memory_addr;
  new_frame->ref_count = 0;
  new_frame->v_addr = 0;
  phys_memory_addr += FRAME_SIZE;
  frame_directory += sizeof(struct frame);
  return (new_frame);
}

int		alloc_frames(int n, struct frame **frames)
{
  while (n > 0)
    {
      *frames = alloc_frame();
      *frames += sizeof(struct frame);
      n--;
    }
  return (0);
}

void		set_used_frame(uint32_t size, uint32_t n)
{
  struct frame	*tmp;

  tmp = phys_to_frame((phys_t)&kernel_start_addr);

  //add offset of kernel_start to size.
  size += (uint32_t)&kernel_start_addr;

  // set every used frame to use.
  while (frame_to_phys(tmp) <= ((phys_t)size + n * FRAME_SIZE))
    {
      tmp->ref_count = 1;
      tmp += sizeof(struct frame);
    }
}

void		init_frame_alloc(multiboot_info_t *multiboot)
{
  multiboot_memory_map_t	*mmap;
  uint32_t			n_entry = 0;
  uint32_t			tmp_entry = 0;
  uint32_t			kernel_size;
  uint32_t			page_dir_size;
  struct frame			*frame_tab;

  page_dir_size = (sizeof(page_dir) * 1024) + (sizeof(page_table) * 1024 * 1023);
  // Frame addr is after Kernel and after page dir/table
  // So it suppose to start in third page of 4M.
  frame_addr = (struct frame *)((uint32_t)&kernel_end_addr + page_dir_size);

  frame_directory = frame_addr;
  kernel_size = get_kernel_size();

  //Get memory map to setup frames
  for (mmap = (multiboot_memory_map_t *) multiboot->mmap_addr;
       (unsigned long) mmap < multiboot->mmap_addr + multiboot->mmap_length;
       mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
  					  + mmap->size + sizeof (mmap->size)))
    {
      if (mmap->type == 1)
	{
	  phys_memory_addr = mmap->addr;
	  end_phys_memory_addr = phys_memory_addr + mmap->len;
	  tmp_entry = mmap->len / FRAME_SIZE;
	  alloc_frames(tmp_entry, &frame_tab);
	  n_entry += tmp_entry;
	}
    }
  //alloc one last frame and set its reference counter to 255. Arbittrary end value.
  //TODO : Use end_phys_memory_addr instead
  frame_tab = alloc_frame();
  frame_tab->ref_count = 255;

  //Set frame already use by Kernel, page directory/table and frames.
  set_used_frame(kernel_size + page_dir_size, n_entry);

  //reset frame_directory pointer to base.
  frame_directory = frame_addr;
}

void*		alloc_pages(struct frame* pdbr, uint32_t size)
{
  (void)pdbr;
  (void)size;
  return (0);
}

int		map_pages(struct frame* pdbr,
			  void* vaddr,
			  struct frame *frames,
			  uint32_t size,
			  int flags)
{
  (void)pdbr;
  (void)vaddr;
  (void)frames;
  (void)size;
  (void)flags;
  return (0);
}

void		*map_io(struct frame* pdbr, phys_t ioaddr, uint32_t len)
{
  (void)pdbr;
  (void)ioaddr;
  (void)len;
  return (0);
}

void		unmap_pages(struct frame *pdbr, void *vaddr, int n)
{
  (void)pdbr;
  (void)vaddr;
  (void)n;
}
