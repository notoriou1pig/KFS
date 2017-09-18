// No Header
// 06/01/2016 - 17:49:11

#include "print_fct.h"

void		putchark(const char c)
{
  write_frame_buffer(c);
  write_serial_port(c);
}

void		printk(const char *msg)
{
  int	i = 0;
  
  while (msg[i] != 0)
    {
      putchark(msg[i]);
      i++;
    }
}

void		printk_oct(uint8_t nbr)
{
  char	tmp;

  if (nbr >= 10)
    printk_oct(nbr / 10);
   tmp = nbr % 10 + 48;
  putchark(tmp);
}

void		printk_nbr(int nbr)
{
  char	tmp;

  if (nbr < 0)
    {
      nbr = nbr * -1;
      putchark('-');
    }
  if (nbr >= 10)
    printk_nbr(nbr / 10);
   tmp = nbr % 10 + 48;
  putchark(tmp);
}

void		printk_long(uint64_t nbr)
{
  printk_nbr(nbr >> 32);
  printk_nbr(nbr);
}

static void	_hex_print_octet(uint8_t nbr, uint8_t rec)
{
  uint8_t	tmp;

  if (nbr >= 16 || rec < 1)
    _hex_print_octet(nbr / 16, 1);
  tmp = nbr % 16;
  if (tmp >= 10)
    tmp += 55;
  else
    tmp += 48;
  putchark(tmp);
}

static void	_hex_print_32(uint32_t nbr, int rec)
{
  if (rec < 3)
    _hex_print_32(nbr / 256, rec + 1);
  _hex_print_octet(nbr % 256, 0);
}

static void	_hex_print_64(uint64_t nbr, int rec)
{
  if (rec < 7)
    _hex_print_64(nbr / 256, rec + 1);
  _hex_print_octet(nbr % 256, 0);
}

void		printk_oct_hex(uint8_t nbr)
{
  //  printk("0x");
  _hex_print_octet(nbr, 0);
}

void		printk_hex(uint32_t nbr)
{
  //  printk("0x");
  _hex_print_32(nbr, 0);
}

void		printk_long_hex(uint64_t nbr)
{
  //  printk("0x");
  _hex_print_64(nbr, 0);
}

static void	_bin_print_octet(uint8_t nbr, uint8_t rec)
{
  uint8_t	tmp;

  if (nbr >= 2 || rec < 7)
    _bin_print_octet(nbr / 2, rec + 1);
  tmp = nbr % 2;
  tmp += 48;
  putchark(tmp);
}
static void	_bin_print_32(uint32_t nbr, int rec)
{
  if (rec < 3)
    _bin_print_32(nbr / 256, rec + 1);
  _bin_print_octet(nbr % 256, 0);
}

static void	_bin_print_64(uint64_t nbr, int rec)
{
  if (rec < 7)
    _bin_print_64(nbr / 256, rec + 1);
  _bin_print_octet(nbr % 256, 0);
}

void		printk_oct_bin(uint8_t nbr)
{
  printk("0b");
  _bin_print_octet(nbr, 0);
}

void		printk_bin(uint32_t nbr)
{
  printk("0b");
  _bin_print_32(nbr, 0);
}

void		printk_long_bin(uint64_t nbr)
{
  printk("0b");
  _bin_print_64(nbr, 0);
}

int		dump_regs(struct regs *r)
{
  printk("\nDUMP REGS :\n");

  printk("Interrupt nbr ");
  printk_nbr(r->int_no);
  printk(" with error code ");
  printk_nbr(r->err_code);
  printk("\n");

  printk("Proc Regs : \n");
  printk("eax: "); printk_hex(r->eax); printk("\t");
  printk("ebx: "); printk_hex(r->ebx); printk("\t");
  printk("ecx: "); printk_hex(r->ecx); printk("\t");
  printk("edx: "); printk_hex(r->edx); printk("\n");

  printk("edi: "); printk_hex(r->edi); printk("\t");
  printk("esi: "); printk_hex(r->esi); printk("\t");
  printk("ebp: "); printk_hex(r->ebp); printk("\t");
  printk("esp: "); printk_hex(r->esp); printk("\n");

  printk("eip: "); printk_hex(r->eip); printk("\t");
  printk("ds : "); printk_hex(r->ds); printk("\t");
  printk("cs : "); printk_hex(r->cs); printk("\t");
  printk("ss : "); printk_hex(r->ss); printk("\n");

  printk("eflags  : "); printk_hex(r->eflags); printk("\n");
  printk("useresp : "); printk_hex(r->useresp); printk("\n\n");
  return (0);
}
