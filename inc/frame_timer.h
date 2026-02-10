/**
 *  \file frame_timer.h
 *  \brief Frame-based timer/alarm system
 *  \author Antigravity
 *  \date 02/2026
 *
 * Lightweight frame-counting alarm system built on top of the V-blank counter.
 * Provides one-shot and repeating alarms with callback dispatch.
 *
 * Call FTIMER_update() once per frame in your main loop to tick all active
 * alarms. This is NOT auto-ticked from V-blank — the game controls when
 * timers fire.
 *
 * Cost: ~80 bytes RAM for FTIMER_MAX timers. Zero CPU when no timers active.
 */

#ifndef _FRAME_TIMER_H_
#define _FRAME_TIMER_H_

/**
 *  \brief
 *      Maximum number of frame timers available.
 */
#define FTIMER_MAX 8

/**
 *  \brief
 *      Frame timer callback function type.
 *
 *  \param id
 *      Timer ID that fired (0 to FTIMER_MAX-1).
 */
typedef void FrameTimerCallback(u16 id);

/**
 *  \brief
 *      Initialize the frame timer system. Clears all timers.
 *
 *  Called automatically at SGDK init. Call manually only if you need
 *  to reset all timers mid-game.
 */
void FTIMER_init(void);

/**
 *  \brief
 *      Set a one-shot frame timer.
 *
 *  \param id
 *      Timer slot (0 to FTIMER_MAX-1).
 *  \param frames
 *      Number of frames to wait before firing.
 *  \param cb
 *      Callback to invoke when the timer fires. NULL to cancel.
 *
 *  The timer fires once after the specified number of FTIMER_update() calls,
 *  then automatically deactivates.
 */
void FTIMER_set(u16 id, u16 frames, FrameTimerCallback *cb);

/**
 *  \brief
 *      Set a repeating frame timer.
 *
 *  \param id
 *      Timer slot (0 to FTIMER_MAX-1).
 *  \param frames
 *      Interval in frames between each firing.
 *  \param cb
 *      Callback to invoke on each firing. NULL to cancel.
 *
 *  The timer fires repeatedly at the specified interval until cancelled.
 */
void FTIMER_setRepeat(u16 id, u16 frames, FrameTimerCallback *cb);

/**
 *  \brief
 *      Cancel a frame timer.
 *
 *  \param id
 *      Timer slot to cancel (0 to FTIMER_MAX-1).
 */
void FTIMER_cancel(u16 id);

/**
 *  \brief
 *      Get remaining frames before a timer fires.
 *
 *  \param id
 *      Timer slot to query (0 to FTIMER_MAX-1).
 *  \return
 *      Frames remaining, or 0 if inactive or expired.
 */
u16 FTIMER_remaining(u16 id);

/**
 *  \brief
 *      Tick all active frame timers. Call once per frame in your main loop.
 *
 *  Decrements counters and fires callbacks for any timers that reach zero.
 *  One-shot timers auto-cancel after firing. Repeating timers reset.
 */
void FTIMER_update(void);

#endif // _FRAME_TIMER_H_
