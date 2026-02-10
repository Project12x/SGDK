/**
 *  \file debug_overlay.h
 *  \brief On-screen debug overlay for development
 *  \author Antigravity
 *  \date 02/2026
 *
 * Provides on-screen display of CPU usage, free memory, and up to 4 custom
 * stat lines during development. All functions compile to nothing when
 * ENABLE_DEBUG_OVERLAY is not defined or set to 0.
 *
 * Usage:
 *   1) Define ENABLE_DEBUG_OVERLAY=1 in your project config (or config.h)
 *   2) Call DBG_startFrame() at the beginning of your main loop
 *   3) Call DBG_endFrame() after all game logic (before VDP_waitVSync)
 *   4) Optionally call DBG_setStat() to display custom values
 *   5) Call DBG_draw() after game drawing to render the overlay
 *
 * The overlay draws text on BG_A (rows 0-5, columns 0-15). Plan your
 * game layout to avoid this region, or use WINDOW plane for the overlay
 * via DBG_setPlane().
 */

#ifndef _DEBUG_OVERLAY_H_
#define _DEBUG_OVERLAY_H_

#ifndef ENABLE_DEBUG_OVERLAY
#define ENABLE_DEBUG_OVERLAY 0
#endif

#if (ENABLE_DEBUG_OVERLAY != 0)

/**
 *  \brief
 *      Maximum number of custom stat lines.
 */
#define DBG_STAT_MAX 4

/**
 *  \brief
 *      Initialize the debug overlay. Call once at startup.
 */
void DBG_init(void);

/**
 *  \brief
 *      Set which VDP plane the overlay draws on.
 *
 *  \param plane
 *      BG_A, BG_B, or WINDOW. Default is BG_A.
 */
void DBG_setPlane(VDPPlane plane);

/**
 *  \brief
 *      Mark the start of frame processing. Call at top of main loop.
 *
 *  Captures the current subtick for CPU usage calculation.
 */
void DBG_startFrame(void);

/**
 *  \brief
 *      Mark the end of frame processing. Call after game logic, before VSync.
 *
 *  Computes CPU usage as percentage of frame time used.
 */
void DBG_endFrame(void);

/**
 *  \brief
 *      Set a custom stat line to display.
 *
 *  \param line
 *      Stat line index (0 to DBG_STAT_MAX-1).
 *  \param label
 *      Short label string (max 8 chars recommended).
 *  \param value
 *      Numeric value to display.
 */
void DBG_setStat(u16 line, const char *label, s16 value);

/**
 *  \brief
 *      Clear a custom stat line.
 *
 *  \param line
 *      Stat line index (0 to DBG_STAT_MAX-1).
 */
void DBG_clearStat(u16 line);

/**
 *  \brief
 *      Draw the debug overlay. Call after all game drawing.
 *
 *  Renders CPU%, free RAM, and any active custom stats as text.
 */
void DBG_draw(void);

#else // ENABLE_DEBUG_OVERLAY == 0

// Compile to nothing when disabled
#define DBG_init()
#define DBG_setPlane(plane)
#define DBG_startFrame()
#define DBG_endFrame()
#define DBG_setStat(line, label, value)
#define DBG_clearStat(line)
#define DBG_draw()

#endif // ENABLE_DEBUG_OVERLAY

#endif // _DEBUG_OVERLAY_H_
