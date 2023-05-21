#define WIDTH 20
#define HEIGHT 5

#define NUM_PIXEL (WIDTH * HEIGHT)
#define HUE_SHIFT 10
#define HUE_OFFSET_LIMIT ((1 << (16 - HUE_SHIFT)) - 1)
#define BRIGHTNESS 3 // 1 - 255

#define SCORLL_DELAY 50 // ms
#define ws2812_port B    // Data port
#define ws2812_pin 0     // Data out pin

#include "font3x5.h"
#define CHAR_BYTE_SIZE (((FONT_WIDTH * FONT_HEIGHT) + 7) / 8)
#define BITMAP_BYTE_SIZE ((NUM_PIXEL + 7) / 8)

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "hsv2rgb.h"
#include "light_ws2812_1bitPixel.h"

uint16_t hue_offset = 0;
uint8_t bitmap[BITMAP_BYTE_SIZE]; // ATtiny13A only have space to store mono

char msg[] = "22:13";

void clearBitmap()
{
  uint8_t idx = BITMAP_BYTE_SIZE;
  while (idx--)
  {
    bitmap[idx] = 0x00;
  }
}

void write_char(int16_t x, uint8_t c)
{
  if (((x + FONT_WIDTH) <= 0) || (x >= WIDTH))
  {
    return;
  }

  int16_t font_idx = (c - FIRST_CHAR) * CHAR_BYTE_SIZE;
  uint8_t font_byte;
  uint8_t font_bit_mask = 1;

  for (uint8_t j = 0; j < FONT_WIDTH; j++)
  {
    if (x >= 0)
    {
      uint16_t bitmap_pos = x * HEIGHT;
      uint8_t h = HEIGHT;
      while (h--)
      {
        if (font_bit_mask == 1)
        {
          font_byte = pgm_read_byte(&font_data[font_idx++]);
          font_bit_mask = 0b10000000;
        }
        else
        {
          font_bit_mask >>= 1;
        }

        if (font_byte & font_bit_mask)
        {
          bitmap[bitmap_pos / 8] |= 0b10000000 >> (bitmap_pos % 8);
        }

        ++bitmap_pos;
      }
    }
    x++;
  }
}

uint8_t getPixelColorFunction(int16_t x, int16_t y, int16_t idx, uint8_t bit_mask, uint8_t bgrIdx)
{
  // check LED should on or off
  if (bitmap[idx] & bit_mask)
  {
    uint16_t i = hue_offset + x;
    if (i > HUE_OFFSET_LIMIT)
    {
      i -= HUE_OFFSET_LIMIT;
    }
    i <<= HUE_SHIFT;
    i = 65535 - i; // reverse
    switch (bgrIdx)
    {
    case 0: // Blue
      return HSV2B(i, 255, BRIGHTNESS);
    case 1: // Red
      return HSV2R(i, 255, BRIGHTNESS);
    default: // 2: Green
      return HSV2G(i, 255, BRIGHTNESS);
    }
  }
  else // LED off
  {
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
  for (uint8_t i = 0; i < (sizeof(msg) - 1); i++)
  {
    write_char((i * (FONT_WIDTH + CHAR_GAP)), msg[i]);
  }

  ws2812_set_leds_func_ptr(WIDTH, HEIGHT, getPixelColorFunction);

  --hue_offset;
  if (hue_offset == 0)
  {
    hue_offset = HUE_OFFSET_LIMIT;
  }

  _delay_ms(SCORLL_DELAY);
}
