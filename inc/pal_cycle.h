/**
 *  \file pal_cycle.h
 *  \brief Palette cycling utilities for classic retro effects
 *  \author Antigravity
 *  \date 02/2026
 *
 * Provides palette color rotation for water, fire, lava, and other
 * classic Genesis effects. Works with SGDK's PAL_getColor/PAL_setColor
 * and handles CRAM updates automatically.
 *
 * Usage:
 *   // Rotate colors 1-3 of palette 2 forward each frame:
 *   PAL_cycleUp(PAL2, 1, 3);
 *
 *   // Or rotate a RAM buffer and apply it yourself:
 *   PAL_cycleColorsUp(myColors, 4);
 *   PAL_setColors(startIndex, myColors, 4);
 */

#ifndef _PAL_CYCLE_H_
#define _PAL_CYCLE_H_

/**
 *  \brief
 *      Rotate palette colors forward (toward higher index) within a range.
 *      The last color wraps to the first position.
 *
 *  \param palIndex
 *      Palette number (PAL0-PAL3, i.e. 0-3).
 *  \param startColor
 *      First color index within the palette (0-15).
 *  \param endColor
 *      Last color index within the palette (0-15, must be > startColor).
 */
void PAL_cycleUp(u16 palIndex, u16 startColor, u16 endColor);

/**
 *  \brief
 *      Rotate palette colors backward (toward lower index) within a range.
 *      The first color wraps to the last position.
 *
 *  \param palIndex
 *      Palette number (PAL0-PAL3, i.e. 0-3).
 *  \param startColor
 *      First color index within the palette (0-15).
 *  \param endColor
 *      Last color index within the palette (0-15, must be > startColor).
 */
void PAL_cycleDown(u16 palIndex, u16 startColor, u16 endColor);

/**
 *  \brief
 *      Rotate colors forward in a RAM buffer (does NOT write to CRAM).
 *
 *  \param colors
 *      Array of u16 color values to rotate in-place.
 *  \param count
 *      Number of colors in the array (must be >= 2).
 */
void PAL_cycleColorsUp(u16 *colors, u16 count);

/**
 *  \brief
 *      Rotate colors backward in a RAM buffer (does NOT write to CRAM).
 *
 *  \param colors
 *      Array of u16 color values to rotate in-place.
 *  \param count
 *      Number of colors in the array (must be >= 2).
 */
void PAL_cycleColorsDown(u16 *colors, u16 count);

#endif // _PAL_CYCLE_H_
