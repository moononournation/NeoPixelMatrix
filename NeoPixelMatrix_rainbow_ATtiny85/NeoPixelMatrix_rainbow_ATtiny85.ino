/*
  https://github.com/moononournation/Font-Stuff
*/
const uint16_t numPixel = 240;
const uint16_t hueScale = 65535 / numPixel;
#define CHAR_GAP 1      // space for each character
#define SCORLL_DELAY 10 // ms
#define ws2812_port B   // Data port
#define ws2812_pin 0    // Data out pin

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "hsv2rgb.h"
#include "light_ws2812_1bitPixel.h"

uint16_t offset = 0; // right most position

uint8_t getPixelColorFunction(uint16_t i, uint8_t brg_idx)
{
  i += offset;
  if (i >= numPixel)
  {
    i -= numPixel;
  }
  i *= hueScale;
  i = 65535 - i;
  switch (brg_idx)
  {
  case 0: // Blue
    return HSV2B(i, 255, 2);
  case 1: // Red
    return HSV2R(i, 255, 2);
  default: // 2: Green
    if (offset > numPixel)
    {
      offset = 0;
    }
    else
    {
      ++offset;
    }
    return HSV2G(i, 255, 2);
  }
}

void setup()
{
  // init pin
  DDRB |= _BV(ws2812_pin);
}

void loop()
{
  ws2812_set_leds_func_ptr(numPixel, getPixelColorFunction);

  _delay_ms(SCORLL_DELAY);
}
