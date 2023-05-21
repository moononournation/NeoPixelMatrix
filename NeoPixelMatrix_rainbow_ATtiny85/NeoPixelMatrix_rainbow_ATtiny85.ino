#define WIDTH 20
#define HEIGHT 5

#define NUM_PIXEL (WIDTH * HEIGHT)
#define HUE_SCALE (65535 / WIDTH)
#define BRIGHTNESS 2 // 1 - 255

#define SCORLL_DELAY 100 // ms
#define ws2812_port B    // Data port
#define ws2812_pin 0     // Data out pin

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "hsv2rgb.h"
#include "light_ws2812_1bitPixel.h"

uint16_t hue_offset = 0; // right most position

uint8_t getPixelColorFunction(int16_t x, int16_t y, int16_t idx, uint8_t bit_mask, uint8_t bgrIdx)
{
  uint16_t i = hue_offset + x;
  if (i > WIDTH)
  {
    i -= WIDTH;
  }
  i *= HUE_SCALE;
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

void setup()
{
  // init pin
  DDRB |= _BV(ws2812_pin);
}

void loop()
{
  ws2812_set_leds_func_ptr(WIDTH, HEIGHT, getPixelColorFunction);

  if (++hue_offset >= WIDTH)
  {
    hue_offset = 0;
  }

  _delay_ms(SCORLL_DELAY);
}
