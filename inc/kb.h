// No Header
// 17/12/2015 - 18:31:28

#ifndef _KFS_KB_H
#define _KFS_KB_H

#define IRQ_KEYBOARD	1

/* Normal KeyBoard */
#define CHAR_ESC	0x01
#define CHAR_F1		0x3B
#define CHAR_F2		0x3C
#define CHAR_F3		0x3D
#define CHAR_F4		0x3E
#define CHAR_F5		0x3F
#define CHAR_F6		0x40
#define CHAR_F7		0x41
#define CHAR_F8		0x42
#define CHAR_F9		0x43
#define CHAR_F10	0x44
#define CHAR_F11	0x57
#define CHAR_F12	0x58
#define CHAR_BQUOTE	0x29
#define CHAR_1		0x02
#define CHAR_2		0x03
#define CHAR_3		0x04
#define CHAR_4		0x05
#define CHAR_5		0x06
#define CHAR_6		0x07
#define CHAR_7		0x08
#define CHAR_8		0x09
#define CHAR_9		0x0A
#define CHAR_0		0x0B
#define CHAR_MINUS	0x0C
#define CHAR_EQU	0x0D
#define CHAR_BACKSPC	0x0E
#define CHAR_TAB	0x0F
#define CHAR_q		0x10
#define CHAR_w		0x11
#define CHAR_e		0x12
#define CHAR_r		0x13
#define CHAR_t		0x14
#define CHAR_y		0x15
#define CHAR_u		0x16
#define CHAR_i		0x17
#define CHAR_o		0x18
#define CHAR_p		0x19
#define CHAR_LBRAQ	0x1A
#define CHAR_RBRAQ	0x1B
#define CHAR_CAPSLOCK	0x3A
#define CHAR_a		0x1E
#define CHAR_s		0x1F
#define CHAR_d		0x20
#define CHAR_f		0x21
#define CHAR_g		0x22
#define CHAR_h		0x23
#define CHAR_j		0x24
#define CHAR_k		0x25
#define CHAR_l		0x26
#define CHAR_SEMICOL	0x27
#define CHAR_QUOTE	0x28
#define CHAR_SHARP	0x2B
#define CHAR_LMAJ	0x2A
#define CHAR_BSLASH	0x56
#define CHAR_z		0x2C
#define CHAR_x		0x2D
#define CHAR_c		0x2E
#define CHAR_v		0x2F
#define CHAR_b		0x30
#define CHAR_n		0x31
#define CHAR_m		0x32
#define CHAR_COMA	0x33
#define CHAR_DOT	0x34
#define CHAR_SLASH	0x35
#define CHAR_RMAJ	0x36
#define CHAR_ENTER	0x1C
#define CHAR_LCTRL	0x1D
#define CHAR_LALT	0x38
#define CHAR_SPACE	0x39

/* Numeric Pad */
#define NCHAR_NUMLOCK	0x45
#define NCHAR_STAR	0x37
#define NCHAR_MINUS	0x4A
#define NCHAR_7		0x47
#define NCHAR_8		0x48
#define NCHAR_9		0x49
#define NCHAR_PLUS	0x4E
#define NCHAR_4		0X4B
#define NCHAR_5		0x4C
#define NCHAR_6		0x4D
#define NCHAR_1		0x4F
#define NCHAR_2		0x50
#define NCHAR_3		0x51
#define NCHAR_0		0x52
#define NCHAR_DOT	0x53

/* Mod Key */
#define CHAR_MOD	0x60
/* Spec Charac :
** Enter	: 0x60 0x1C
** HOME		: 0x60 0x47
** END		: 0x60 0x4F
** INSERT	: 0x60 0x52
** Delete	: 0x60 0x53
** WIN		: 0x60 0x5B
** ALTGR	: 0x60 0x38
** PRTSC	: 0x60 0x37
** RCTRL	: 0x60 0x1D
** PgUp		: 0x60 0x49
** UP		: 0x60 0x48
** PgDn		: 0x60 0x51
** Left		: 0x60 0x4B
** Down		: 0x60 0x50
** Right	: 0x60 0x4D
** Pad /	: 0x60 0x35
*/

typedef struct	keymap_s
{
  uint8_t	code;
  uint8_t	charac;
  uint8_t	maj_charac;
}		_charset;

static _charset	keymap[85] = {
  {CHAR_ESC, 0, 0}, {CHAR_F1, 0, 0},  {CHAR_F2, 0, 0},
  {CHAR_F3, 0, 0},  {CHAR_F4, 0, 0},  {CHAR_F5, 0, 0},
  {CHAR_F6, 0, 0},  {CHAR_F7, 0, 0},  {CHAR_F8, 0, 0},
  {CHAR_F9, 0, 0},  {CHAR_F10, 0, 0}, {CHAR_F11, 0, 0},
  {CHAR_F12, 0, 0},

  {CHAR_BQUOTE, '`', '|'}, {CHAR_1, '1', '!'}, {CHAR_2, '2', '"'},
  {CHAR_3, '3', '#'},      {CHAR_4, '4', '$'}, {CHAR_5, '5', '%'},
  {CHAR_6, '6', '^'},      {CHAR_7, '7', '&'}, {CHAR_8, '8', '*'},
  {CHAR_9, '9', '('},      {CHAR_0, '0', ')'}, {CHAR_MINUS, '-', '_'},
  {CHAR_EQU, '=', '+'},    {CHAR_BACKSPC, '\b', '\b'},

  {CHAR_TAB, '\t', '\t'}, {CHAR_q, 'q', 'Q'}, {CHAR_w, 'w', 'W'},
  {CHAR_e, 'e', 'E'},     {CHAR_r, 'r', 'R'}, {CHAR_t, 't', 'T'},
  {CHAR_y, 'y', 'Y'},     {CHAR_u, 'u', 'U'}, {CHAR_i, 'i', 'I'},
  {CHAR_o, 'o', 'O'},     {CHAR_p, 'p', 'P'}, {CHAR_LBRAQ, '[', '{'},
  {CHAR_RBRAQ, ']', '}'},

  {CHAR_CAPSLOCK, 0, 0}, {CHAR_a, 'a', 'A'},       {CHAR_s, 's', 'S'},
  {CHAR_d, 'd', 'D'},    {CHAR_f, 'f', 'F'},       {CHAR_g, 'g', 'G'},
  {CHAR_h, 'h', 'H'},    {CHAR_j, 'j', 'J'},       {CHAR_k, 'k', 'K'},
  {CHAR_l, 'l', 'L'},    {CHAR_SEMICOL, ';', ':'}, {CHAR_QUOTE, '\'', '@'},
  {CHAR_SHARP, '#', '~'},
  
  {CHAR_LMAJ, 0, 0},     {CHAR_BSLASH, '\\', '|'}, {CHAR_z, 'z', 'Z'},
  {CHAR_x, 'x', 'X'},    {CHAR_c, 'c', 'C'},       {CHAR_v, 'v', 'V'},
  {CHAR_b, 'b', 'B'},    {CHAR_n, 'n', 'N'},       {CHAR_m, 'm', 'M'},
  {CHAR_COMA, ',', '<'}, {CHAR_DOT, '.', '>'},     {CHAR_SLASH, '/', '?'},
  {CHAR_RMAJ, 0, 0},

  {CHAR_ENTER, '\n', '\n'}, {CHAR_LCTRL, 0, 0}, {CHAR_LALT, 0, 0},
  {CHAR_SPACE, ' ', ' '},

  {NCHAR_NUMLOCK, 0, 0}, {NCHAR_STAR, '*', 0}, {NCHAR_MINUS, '-', 0},
  {NCHAR_PLUS, '+', 0},
  {NCHAR_7, '7', 0},     {NCHAR_8, '8', 0},    {NCHAR_9, '9', 0},
  {NCHAR_4, '4', 0},     {NCHAR_5, '5', 0},    {NCHAR_6, '6', 0},
  {NCHAR_1, '1', 0},     {NCHAR_2, '2', 0},    {NCHAR_3, '3', 0},
  {NCHAR_0, '0', 0},     {NCHAR_DOT, '.', 0}
};

#endif /* !_KFS_KB_H */
