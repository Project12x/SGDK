#include "config.h"
#include "types.h"

#include "pal.h"
#include "pal_cycle.h"

void PAL_cycleUp(u16 palIndex, u16 startColor, u16 endColor) {
  u16 base;
  u16 saved;
  u16 i;

  if (endColor <= startColor)
    return;

  base = (palIndex << 4);
  saved = PAL_getColor(base + endColor);

  for (i = endColor; i > startColor; i--) {
    PAL_setColor(base + i, PAL_getColor(base + i - 1));
  }
  PAL_setColor(base + startColor, saved);
}

void PAL_cycleDown(u16 palIndex, u16 startColor, u16 endColor) {
  u16 base;
  u16 saved;
  u16 i;

  if (endColor <= startColor)
    return;

  base = (palIndex << 4);
  saved = PAL_getColor(base + startColor);

  for (i = startColor; i < endColor; i++) {
    PAL_setColor(base + i, PAL_getColor(base + i + 1));
  }
  PAL_setColor(base + endColor, saved);
}

void PAL_cycleColorsUp(u16 *colors, u16 count) {
  u16 saved;
  u16 i;

  if (count < 2)
    return;

  saved = colors[count - 1];
  for (i = count - 1; i > 0; i--) {
    colors[i] = colors[i - 1];
  }
  colors[0] = saved;
}

void PAL_cycleColorsDown(u16 *colors, u16 count) {
  u16 saved;
  u16 i;

  if (count < 2)
    return;

  saved = colors[0];
  for (i = 0; i < count - 1; i++) {
    colors[i] = colors[i + 1];
  }
  colors[count - 1] = saved;
}
