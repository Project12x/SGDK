#include "config.h"
#include "types.h"

#include "frame_timer.h"

typedef struct {
  FrameTimerCallback *cb; // callback (NULL = inactive)
  u16 remaining;          // frames until next fire
  u16 interval;           // 0 = one-shot, >0 = repeat interval
} FrameTimer;

static FrameTimer timers[FTIMER_MAX];

void FTIMER_init(void) {
  u16 i;
  for (i = 0; i < FTIMER_MAX; i++) {
    timers[i].cb = NULL;
    timers[i].remaining = 0;
    timers[i].interval = 0;
  }
}

void FTIMER_set(u16 id, u16 frames, FrameTimerCallback *cb) {
  if (id >= FTIMER_MAX)
    return;

  timers[id].cb = cb;
  timers[id].remaining = frames;
  timers[id].interval = 0; // one-shot
}

void FTIMER_setRepeat(u16 id, u16 frames, FrameTimerCallback *cb) {
  if (id >= FTIMER_MAX)
    return;

  timers[id].cb = cb;
  timers[id].remaining = frames;
  timers[id].interval = frames; // repeating
}

void FTIMER_cancel(u16 id) {
  if (id >= FTIMER_MAX)
    return;

  timers[id].cb = NULL;
  timers[id].remaining = 0;
  timers[id].interval = 0;
}

u16 FTIMER_remaining(u16 id) {
  if (id >= FTIMER_MAX)
    return 0;
  if (timers[id].cb == NULL)
    return 0;

  return timers[id].remaining;
}

void FTIMER_update(void) {
  u16 i;
  for (i = 0; i < FTIMER_MAX; i++) {
    FrameTimer *t = &timers[i];

    if (t->cb == NULL)
      continue;

    if (t->remaining > 0)
      t->remaining--;

    if (t->remaining == 0) {
      // fire callback
      t->cb(i);

      if (t->interval > 0) {
        // repeating: reset counter
        t->remaining = t->interval;
      } else {
        // one-shot: deactivate
        t->cb = NULL;
      }
    }
  }
}
