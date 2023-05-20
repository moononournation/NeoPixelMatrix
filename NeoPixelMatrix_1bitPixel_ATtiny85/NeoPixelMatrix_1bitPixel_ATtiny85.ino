#define WIDTH 54
#define HEIGHT 8

#define NUM_PIXEL (WIDTH * HEIGHT)
#define HUE_SCALE (65535 / WIDTH)
#define BRIGHTNESS 2 // 1 - 255

#define FONT_WIDTH 5
#define FONT_HEIGHT 8
#define BITMAP_SIZE ((NUM_PIXEL + 7) / 8)
#define CHAR_GAP 1       // space for each character
#define SCORLL_DELAY 100 // ms
#define ws2812_port B    // Data port
#define ws2812_pin 0     // Data out pin

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "glcdfont.h"
#include "hsv2rgb.h"
#include "light_ws2812_1bitPixel.h"

int8_t offset = WIDTH;       // right most position
uint8_t bitmap[BITMAP_SIZE]; // ATtiny13A only have space to store mono

char msg[] = "Hello NeoPixel! @moononournation";

void clearBitmap()
{
  uint8_t idx = BITMAP_SIZE;
  while (idx--)
  {
    bitmap[idx] = 0x00;
  }
}

void write_char(int8_t x, uint8_t c)
{
  if ((x + FONT_WIDTH) <= 0)
    return;

  uint16_t idx = (uint16_t)c * FONT_WIDTH;
  for (uint8_t j = 0; j < FONT_WIDTH; j++)
  {
    if (x >= 0)
    {
      bitmap[x] = pgm_read_byte(&font[idx]);
    }
    x++;
    idx++;
  }
}

uint8_t getPixelColorFunction(uint8_t idx, uint8_t bit_idx, uint8_t brg_idx)
{
  uint8_t bit_mask;
  bit_mask = (0b10000000 >> bit_idx);
  if (bitmap[idx] & bit_mask)
  { // check LED should on or off
    switch (brg_idx)
    {
    case 0: // Blue
      return HSV2B((uint16_t)idx * HUE_SCALE, 255, BRIGHTNESS);
      return 0;
    case 1: // Red
      return HSV2R((uint16_t)idx * HUE_SCALE, 255, BRIGHTNESS);
      return 0;
    default: // 2: Green
      return HSV2G((uint16_t)idx * HUE_SCALE, 255, BRIGHTNESS);
      return 0;
    }
  }
  else
  { // LED off
    return 0;
  }
}

void setup()
{
  // init pin
  DDRB |= _BV(ws2812_pin);
}

void loop()
{
  clearBitmap();

  uint8_t i = 0;
  for (; i < (sizeof(msg) - 1); i++)
  {
    write_char(offset + (i * (FONT_WIDTH + CHAR_GAP)), msg[i]);
  }

  offset--;
  if (offset < (-(FONT_WIDTH + CHAR_GAP) * (int8_t)sizeof(msg))) // left most position
  {
    offset = WIDTH; // return to right most position
  }

  ws2812_set_leds_func_ptr(WIDTH * HEIGHT, getPixelColorFunction);

  _delay_ms(SCORLL_DELAY);
}
