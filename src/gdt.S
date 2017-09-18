[GLOBAL init_seg_reg]

init_seg_reg:
	jmp 0x08:.flush   	; 0x08 : offset of kernel code segment
.flush:
	mov ax, 0x10      	; 0x10 : offset of kernel data segment
	mov ds, ax      	; Load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
