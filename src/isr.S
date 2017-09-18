extern interrupt_switcher
extern irq_send_eoi

%macro ISR_COMMON_START 0
	pusha 			; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

 	mov ax, ds		; Lower 16-bits of eax = ds.
 	push eax		; save the data segment descriptor

 	mov ax, 0x10	  	; load the kernel data segment descriptor
 	mov ds, ax
 	mov es, ax
 	mov fs, ax
 	mov gs, ax
%endmacro

%macro ISR_COMMON_END 0
 	pop eax        		; reload the original data segment descriptor
 	mov ds, ax
 	mov es, ax
 	mov fs, ax
 	mov gs, ax

	popa			; Pops edi,esi,ebp...
  	add esp, 8     		; Cleans up the pushed error code
				; pushed ISR number
 	sti
%endmacro

%macro INTER_SWITCH 0
	mov eax, esp
	push eax
	mov eax, interrupt_switcher
	call eax		; do not touch esp with this type of call
	pop eax        		; pop esp (eax was push)
	mov esp, eax
%endmacro

;;; ISR CREATION
%macro ISR_ 1-*
[GLOBAL isr%1]			;extern irs_nbr func
isr%1:	
	cli
	mov al, %0		;check if error code set
	cmp al, 2
	jne .isrno
%rotate 1
	push byte %1		;push error code
%rotate -1
.isrno:
	push byte %1		;push isr number
ISR_COMMON_START
INTER_SWITCH
ISR_COMMON_END
	iret
%endmacro

[GLOBAL isr_reserved]
isr_reserved:	
	cli
	push byte 0		;blank
	push byte 0		;blank
ISR_COMMON_START
INTER_SWITCH
ISR_COMMON_END
	iret

[GLOBAL isr_nodef]
isr_nodef:	
	cli
	push byte 0
	push byte 0x30 	;; addr empty start
ISR_COMMON_START
INTER_SWITCH
ISR_COMMON_END
	iret

	;; First ISR
ISR_		0,0
ISR_		1,0
ISR_		2,0
ISR_		3,0
ISR_		4,0
ISR_		5,0
ISR_		6,0
ISR_		7,0
ISR_		8
ISR_		9,0
ISR_		10
ISR_		11
ISR_		12
ISR_		13
ISR_		14
ISR_		15

;;; IRQ CREATION
%macro IRQ_ 2
[GLOBAL irq%1]			;extern irs_nbr func
irq%1:	
	cli
 	push byte 0		;push error code
	push byte %2		;push isr number
ISR_COMMON_START
INTER_SWITCH
ISR_COMMON_END
	call irq_send_eoi
	iret
%endmacro

IRQ_ 0, 32
IRQ_ 1, 33
IRQ_ 2, 34
IRQ_ 3, 35
IRQ_ 4, 36
IRQ_ 5, 37
IRQ_ 6, 38
IRQ_ 7, 39
IRQ_ 8, 40
IRQ_ 9, 41
IRQ_ 10, 42
IRQ_ 11, 43
IRQ_ 12, 44
IRQ_ 13, 45
IRQ_ 14, 46
IRQ_ 15, 47
