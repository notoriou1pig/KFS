// No Header
// 14/12/2015 - 17:04:05

char	inb(int port)
{
  char ret;

  __asm__ __volatile__ ("inb %%dx,%%al": "=al" (ret) :"d" (port));
  return (ret);
}
