; Declare constants used for creating a multiboot header.
bits 32
MBALIGN     equ  1<<0	; align loaded modules on page boundaries
MEMINFO     equ  1<<1	; provide memory map
FLAGS       equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002 ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS) ; checksum of above, to prove we are multiboot

; Declare a header as in the Multiboot Standard. We put this into a special
; section so we can force the header to be in the start of the final program.
; Don't need to understand all these details as it is just magic values that
; is documented in the multiboot standard. The bootloader will search for this
; magic sequence and recognize us as a multiboot kernel.
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; Currently the stack pointer register(esp) points at anything and using it may
; cause massive harm. Instead, we'll provide our own stack. We will allocate
; room for a small temporary stack by creating a symbol at the bottom of it,
; then allocating 16 Kbytes for it, and finally creating a symbol at the top.
section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 16384
stack_top:

; The linker script specifies _start as the entry point to the kernel and the
; bootloader will jump to this position once the kernel has been loaded. It
; doesn't make sense to return from this function as the bootloader is gone.
section .text
global _start
_start:

;;  To set up a stack, we simply set the esp register to point to the top of
;;  our stack (as it grows downwards).
	;;   	mov esp, stack_top

;;  We are now ready to actually execute C code. We cannot embed that in an
;;  assembly file, so we'll create a kernel.c file in a moment. In that file,
;;  we'll create a C entry point called kernel_main and call it here.
	extern enable_paging
	extern kernel_main
	push ebx
	push eax
	call enable_paging
;;  Remember next instruction disable interrupt !!
	call kernel_main

	cli
.hang:
	hlt
	jmp .hang
