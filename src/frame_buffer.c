// No Header
// 12/01/2016 - 00:03:41

#include "misc.h"

char*		frame_buffer;

void		init_frame_buffer()
{
  int	y = 0;
  frame_buffer = (char*) 0xB8000;
  while (y < (VGA_HEIGHT * VGA_WIDTH * 2))
    {
      frame_buffer[y] = 0;
      y = y + 2;
    }
}


static void	scroll_frame_buffer()
{
  int		i = 0;
  int		j = 0;

  do
    {
      j = 0;
      while (j < (VGA_WIDTH * 2))
	{
	  frame_buffer[i * (VGA_WIDTH * 2) + j] =
	    frame_buffer[i * (VGA_WIDTH * 2) + (j + VGA_WIDTH * 2)];
	  j += 2;
	}
      i++;
    }  while (i < VGA_HEIGHT - 1);
  j = 0;
  while (j < (VGA_WIDTH * 2))
    {
      frame_buffer[i * (VGA_WIDTH * 2) + j] = 0;
      j += 2;
    }
}

void		write_frame_buffer(char c)
{
  static int	i = 0;
  static int	j = 0;

  if (c == '\n')
    {
      i++;
      j = 0;
    }
  else if (c == '\t')
    j += (TAB_SIZE - (j % TAB_SIZE)) * 2;
  else if (c == '\b')
    {
      j -= 2;
      frame_buffer[i * (VGA_WIDTH * 2) + j] = ' ';
      if (j < 0)
	{
	  j = (VGA_WIDTH * 2) - 2;
	  i--;
	}
    }
  else
    {
      frame_buffer[i * (VGA_WIDTH * 2) + j] = c;
      j = j + 2;
    }
  if (j >= (VGA_WIDTH * 2))
    {
      j = 0;
      i++;
    }
  if (i >= VGA_HEIGHT)
    {
      i = VGA_HEIGHT - 1;
      scroll_frame_buffer();
    }
}
