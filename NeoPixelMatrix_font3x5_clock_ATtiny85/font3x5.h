/*
Design you own font:
https://moononournation.github.io/Font-Stuff/FontDesign.html

fontsetvalue:
FC7E 003E BD7A AD7E E13E ED6E FD6E 843E FD7E ED7E 0280
*/
#include <avr/pgmspace.h>

#define FONT_WIDTH 3
#define FONT_HEIGHT 5
#define CHAR_GAP 1
#define FIRST_CHAR '0'

static const uint8_t font_data[] PROGMEM = {
0xFC, 0x7E, 0x00, 0x3E, 0xBD, 0x7A, 0xAD, 0x7E,
0xE1, 0x3E, 0xED, 0x6E, 0xFD, 0x6E, 0x84, 0x3E,
0xFD, 0x7E, 0xED, 0x7E, 0x02, 0x80
};
/* old
745C 4FC2 4CDA 8D54 E13E ED6C 7D66 85F0 DD76 CD7C 0280
*/
