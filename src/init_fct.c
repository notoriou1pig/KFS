// No Header
// 15/01/2016 - 00:11:32

#include "misc.h"
#include "segmentation.h"
#include "multiboot.h"
#include "Memory/frame_alloc.h"

void		init(multiboot_info_t *multiboot)
{
  init_serial_port();
  init_frame_buffer();
  init_flat_gdt();
  init_interrupts();
  init_frame_alloc(multiboot);
}
