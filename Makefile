## No Header
## 15/01/2016 - 03:51:34

NAME		=	kfs.bin

CC		=	gcc -W -Wall -Wextra
CFLAGS		+=	-nostdinc -fno-builtin -m32 -O0
CFLAGS		+=	-fno-stack-protector -ffreestanding
CFLAGS		+=	-Wno-packed-bitfield-compat
CFLAGS		+=	-ggdb3 -g
CFLAGS		+=	-I$(INC)
LDFLAGS 	+=	-nostdlib

ASM 		= 	nasm
ASM_FORMAT	=	-f elf32

LINK		=	ld
LINK_ARCH	=	elf_i386
LINK_FILE	=	kfs.ld

RM		=	rm -vf

QEMU		=	qemu-system-i386
QEMU_OPTS	=	-serial stdio -m 512
QEMU_DEBUG	=	-s -S

#SRCS		=	$(shell find . -name "*.S" -or -name "*.c")
SRC_DIR		=	./src/
SRCS		=	main.c			\
			crt0.S			\
			misc.c			\
			segmentation.c		\
			gdt.S			\
			interrupts.c		\
			isr.S			\
			irq.c			\
			print_fct.c		\
			init_fct.c		\
			frame_buffer.c		\
			serial_port.c		\
			interrupt_switcher.c	\
			kbd_fct.c		\
			pit.c			\
			Memory/frame_alloc.c

OBJ_DIR		=	./obj/
OBJS		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCS)))
#OBJS		=	$(addsuffix .o, $(SRCS))
INC		=	inc

$(OBJ_DIR)%.S.o:	$(SRC_DIR)%.S
			$(ASM) $(ASM_FORMAT) $< -o $@

$(OBJ_DIR)%.c.o:	$(SRC_DIR)%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
		$(LINK) $(LDFLAGS) -m $(LINK_ARCH) -T $(LINK_FILE) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

run:		all
		$(QEMU) $(QEMU_OPTS) -kernel $(NAME)

nograph:	all
		$(QEMU) -nographic $(QEMU_OPTS) -kernel $(NAME)

debug:		all
		$(QEMU) $(QEMU_DEBUG) -kernel $(NAME) &
		gdb kfs.bin

.PHONY:		all clean fclean re run

