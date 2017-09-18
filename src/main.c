// No Header
// 12/01/2016 - 16:56:29

#include "misc.h"
#include "init_fct.h"
#include "kfs_type.h"
#include "multiboot.h"

void	kernel_main(unsigned long magic, multiboot_info_t *addr)
{
  if (magic == MULTIBOOT_BOOTLOADER_MAGIC)
    {
      init(addr);
      printk("Hello World\n");
    }

  while (1)
    __asm__ __volatile__ ("hlt");
}

