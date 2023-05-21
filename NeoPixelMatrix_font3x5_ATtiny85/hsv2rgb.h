/***************************************
 * Source:
 * Extract from Adafruit NeoPixel library
 ***************************************/
uint8_t HSV2R(uint16_t hue, uint8_t sat, uint8_t val)
{
  uint8_t r;
  hue = (hue * 1530L + 32768) / 65536;
  if (hue < 510) // Red to Green-1
  {
    if (hue < 255) // Red to Yellow-1
    {
      r = 255;
    }
    else // Yellow to Green-1
    {
      r = 510 - hue; // r = 255 to 1
    }
  }
  else if (hue < 1020) // Green to Blue-1
  {
    r = 0;
  }
  else if (hue < 1530) // Blue to Red-1
  {
    if (hue < 1275) // Blue to Magenta-1
    {
      r = hue - 1020; // r = 0 to 254
    }
    else // Magenta to Red-1
    {
      r = 255;
    }
  }
  else // Last 0.5 Red (quicker than % operator)
  {
    r = 255;
  }

  // Apply saturation and value to R,G,B, pack into 32-bit result:
  uint32_t v1 = 1 + val;  // 1 to 256; allows >>8 instead of /255
  uint16_t s1 = 1 + sat;  // 1 to 256; same reason
  uint8_t s2 = 255 - sat; // 255 to 0
  return ((((r * s1) >> 8) + s2) * v1) >> 8;
}

uint8_t HSV2G(uint16_t hue, uint8_t sat, uint8_t val)
{
  uint8_t g;
  hue = (hue * 1530L + 32768) / 65536;
  if (hue < 510) // Red to Green-1
  {
    if (hue < 255) // Red to Yellow-1
    {
      g = hue; // g = 0 to 254
    }
    else // Yellow to Green-1
    {
      g = 255;
    }
  }
  else if (hue < 1020) // Green to Blue-1
  {
    if (hue < 765) // Green to Cyan-1
    {
      g = 255;
    }
    else // Cyan to Blue-1
    {
      g = 1020 - hue; // g = 255 to 1
    }
  }
  else if (hue < 1530) // Blue to Red-1
  {
    g = 0;
  }
  else // Last 0.5 Red (quicker than % operator)
  {
    g = 0;
  }

  // Apply saturation and value to R,G,B, pack into 32-bit result:
  uint32_t v1 = 1 + val;  // 1 to 256; allows >>8 instead of /255
  uint16_t s1 = 1 + sat;  // 1 to 256; same reason
  uint8_t s2 = 255 - sat; // 255 to 0
  return ((((g * s1) >> 8) + s2) * v1) >> 8;
}

uint8_t HSV2B(uint16_t hue, uint8_t sat, uint8_t val)
{
  uint8_t b;
  hue = (hue * 1530L + 32768) / 65536;
  if (hue < 510) // Red to Green-1
  {
    b = 0;
  }
  else if (hue < 1020) // Green to Blue-1
  {
    if (hue < 765) // Green to Cyan-1
    {
      b = hue - 510; // b = 0 to 254
    }
    else // Cyan to Blue-1
    {
      b = 255;
    }
  }
  else if (hue < 1530) // Blue to Red-1
  {
    if (hue < 1275) // Blue to Magenta-1
    {
      b = 255;
    }
    else // Magenta to Red-1
    {
      b = 1530 - hue; // b = 255 to 1
    }
  }
  else // Last 0.5 Red (quicker than % operator)
  {
    b = 0;
  }

  // Apply saturation and value to R,G,B, pack into 32-bit result:
  uint32_t v1 = 1 + val;  // 1 to 256; allows >>8 instead of /255
  uint16_t s1 = 1 + sat;  // 1 to 256; same reason
  uint8_t s2 = 255 - sat; // 255 to 0
  return ((((b * s1) >> 8) + s2) * v1) >> 8;
}
