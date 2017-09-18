# Kernel Programming I - Kernel From Scratch
## Introduction

## Hello World !

The aim of this project is to get a basic build system for your own kernel.

### You must:
1. Write a Makefile with the following rules:
  	+ all: compile the kernel and the generate the ELF file.
	+ boot: boot the kernel using Qemu or Bochs.
	+ debug: boot the kernel and attach a gdb on it.

2. Write a function void printk(const char *msg) which prints on the framebuffer and on the serial port with the following line protocol:
      + 38400 bauds
      + 8 bits per word
      + No parity check
      + 1 stop bit

3. Send us a tarball of the sources of your kernel:<br/>
      kfs-login_x<br/>
      +-- Makefile<br/>
      +-- kfs.ld<br/>
      +-- src/<br/>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;+-- crt0.S<br/>
      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;+-- main.c<br/>

### You will learn:
+ How VGA text-mode works
+ How 16550 UART chip works

## Conclusion
Corrections will take place in your computers.

# Kernel Programming II - Kernel From Scratch
## Introduction

The specifications described below should be be considered as guidelines.</br>
This is not mandantory to perfectly fit this API but is highly recommended.

## Summary

  1. Segmentation
  2. Interrupts handling
  3. Keyboard driver
  4. Timer driver

## Segmentation
### Brief

Firstly, you have to configure segmentation in order to get a flat memory model.

Reference: Intel Manual 3A Chapter 3</br>
File: src/segmentation.c</br>
Header: inc/segmentation.h</br>
MyFile: src/gdt.S</br>

### Functions

int	set_gdt_entry(int n, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

Description: Set a GDT entry.</br>
Arguments:</br>
+ n: entry index
+ base: segment base address
+ limit: segment limit
+ access: segment access attributes
+ granularity: segment limit granularity

void	init_flat_gdt(void);

Description: This function sets a GDT in order to get a flat memory model.</br>
It must reloads the segment selectors according to the new GDT.</br>
A minimal GDT will be:</br>
+ Null segment
+ Kernel code segment
+ Kernel data segment

## Interrupts
### Brief

In protected mode, interrupts are handled thanks to an Interrupt Descriptor Table.</br>
These functions allows the initialization of this structure.</br>
File: src/interrupts.c</br>
Header: inc/interrupts.h</br>

### Types

struct	regs;

Description: A struct which hold a context</br>
(registers, segment selectors, flags, #).


int	(/*isr_handler)(struct regs* regs);

Description: A pointer to an IRQ handler</br>
Arguments:</br>
	regs: saved context</br>

### Functions

void	interrupts_init(void);

Description: Initialize an IDT and fill it with interrupt gates.
The first 32 entries must point to a default ISR handler which prints
the cause of the exception, the saved context and the error code.
The others must be set as "not present".

void	interrupts_set_isr(int n, isr_handler handler, int flags);

Description:
Arguments:
	n: interrupt index
        handler: pointer to the IRQ handler
        flags:
              ISR_USER: the user can call it

## IRQ
### Brief

Now that the IDT is set up, the external interrupts have to handled.
This can be achieved thanks to the Programmable Interrupt Controller which is
responsible for multiplexing interrupts from peripherals
into one interrupt line on the CPU.

Chip reference: i8259A
File: src/irq.c
Header: inc/irq.h

### Functions

int	irq_init(uint8_t base);

Description: Initialize PIC and set global interrupt flag.
Arguments:
	base: base offset in the IDT to use
		(Hint: the first 32 entries are reserved).

void	irq_mask(int irq);

Description: Mask an IRQ (Hint: use OCW1)
Arguments:
	irq: irq number

void	irq_unmask(int irq);

Description: Unmask an IRQ (Hint: use OCW1)
Arguments:
	irq: irq number

void	irq_send_eoi(void);

Description: Send EOI command to PIC (Hint: use OCW2)

## Keyboard
### Brief

In order to test PIC configuration,
you can write a simple keyboard driver which is hooked on the IRQ1.

Chip reference: i8042
File: src/kb.c
Header: inc/kb.h

### Functions

void	kb_init(void);

Description: Register and unmask an IRQ handler for keyboard events.

int	kb_get_key(void);

Description: Returns the key code of last pressed key.

## Programmable Interrupt Timer
### Brief

Once your keyboard driver is working,
let's try to get some periodic interrupts.
This can be achieved by configuring the Programmable Interrupt Timer.

Chip reference: i8254
File: src/pit.c
Header: inc/pit.h

### Functions

int	pit_init(int freq);

Description: Configure PIT in mode 2 (rate generator) at a given frequency.
Register and unmask an IRQ handler for timer events.
(Hint: Input clock frequency is 1193182 Hertz)

Arguments:
	freq: timer frequency (Hertz)

int	pit_get_ticks(void);

Description: Returns the number of ticks elapsed since the machine started.

## Bonus: Serial
### Brief

Try to improve your serial driver by handling UART interrupts.

File: src/serial.c
Header: inc/serial.h

### Functions

int	uart_init(void);

Description: Configure UART. Register and unmask an IRQ handler for UART events.

void	uart_send(uint8_t c);

Description: Send a character using UART

Arguments:
	c: character to be sent

uint8_t	uart_recv(void);

Description: Returns the last received character

## Conclusion

Corrections will take place in your computers. Have fun :)

# Kernel Programming III - Kernel From Scratch
## Introduction

Here is the assigments for Kernel Programming III - Kernel From Scratch.

Subject: [KERNEL] LOGIN_X LOGIN_Y - KFS

The specifications described below should be be considered as guidelines.
This is not mandantory to perfectly fit this API but is highly recommended.
## Summary
   Frame allocator

## Frame allocator
### Types

typedef unsigned int	phys_t;

Description: describes a physical address. Since paging is enabled,
it is not possible to dereference this address.

struct			frame;

Description: A structure which describes a frame. It should contain:
	     a reference counter
	     a virtual address where is the frame is mapped

### Functions

void		init_frame_alloc(multiboot_info_t *multiboot);

Description: Initialize frame allocator. It should use memory map structure
included in multiboot info in order to get RAM size.
Arguments:
	multiboot: a pointer to the multiboot struture provided by the bootloader.

struct frame*	alloc_frame(void);

Description: Allocate a new frame and return a pointer the structure
which describes it.

int		alloc_frames(int n, struct frame **frames);

Description: Allocate n physically contiguous frames.
Arguments:
	n: number of frames to allocate.
	frames: pointer to allocated frames

void		free_frame(struct frame *frame);

Description: Decrement reference counter of a frame.

phys_t		frame_to_phys(struct frame *frame);

Description: Get physical address of a frame.

struct frame*	phys_to_frame(phys_t addr);

Description: Get frame data from physical address.

## Page allocator
### Functions

void*		alloc_pages(struct frame* pdbr, size_t n);

Description: find n consecutive free virtual pages and return their address.

Arguments:
	pdbr: frame which contains page directory
	n: number of pages needed

int		map_pages(struct frame* pdbr,
		          void* vaddr,
			  struct frame *frames,
			  size_t n,
			  int flags);

Description: Map n physical pages to virtual pages.

Arguments:
	pdbr: frame which contains page directory
	vaddr: address of virtual pages
	frames: frames to map
	n: number of frames to map
	flags: access right associated to pages

void		*map_io(struct frame* pdbr, phys_t ioadddr, size_t len);

Description: Map an IO memory range. Be careful with ioaddr alignment.

Arguments:
	pdbr: frame which contains page directory
	ioaddr: base address of IO memory range
	len: size of IO memory range

Example: Map VGA text buffer to virtual address space

void *video_mem = map_io(pdbr, 0xB8000, 80 * 25 * 2);

void		unmap_pages(struct frame *pdbr, void *vaddr, int n);

Description: Unmap pages.

Arguments:
	pbdr: frame which contains page directory
	vaddr: address of pages to unmap
	n: number of pages to unmap
