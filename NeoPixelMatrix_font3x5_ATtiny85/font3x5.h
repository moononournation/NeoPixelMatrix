/*
Design you own font:
https://moononournation.github.io/Font-Stuff/FontDesign.html

fontsetvalue:
745C 4FC2 4CDA 8D54 E13E ED64 7564 8DB0 DD76 4D5C 0280
*/
#include <avr/pgmspace.h>

#define FONT_WIDTH 3
#define FONT_HEIGHT 5
#define CHAR_GAP 1
#define FIRST_CHAR '0'

static const uint8_t font_data[] PROGMEM = {
0x74, 0x5C, 0x4F, 0xC2, 0x4C, 0xDA, 0x8D, 0x54,
0xE1, 0x3E, 0xED, 0x64, 0x75, 0x64, 0x8D, 0xB0,
0xDD, 0x76, 0x4D, 0x5C, 0x02, 0x80
};
