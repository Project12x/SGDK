#include "config.h"
#include "types.h"

#include "debug_overlay.h"

#if (ENABLE_DEBUG_OVERLAY != 0)

#include "memory.h"
#include "string.h"
#include "sys.h"
#include "vdp.h"
#include "vdp_bg.h"

// Internal state
typedef struct {
  const char *label; // NULL = inactive
  s16 value;
} DebugStat;

static VDPPlane dbgPlane;
static DebugStat stats[DBG_STAT_MAX];
static char lineBuf[32];

void DBG_init(void) {
  u16 i;

  dbgPlane = BG_A;

  for (i = 0; i < DBG_STAT_MAX; i++) {
    stats[i].label = NULL;
    stats[i].value = 0;
  }
}

void DBG_setPlane(VDPPlane plane) { dbgPlane = plane; }

void DBG_startFrame(void) {
  // No-op: CPU load is now read from SYS_getCPULoad()
}

void DBG_endFrame(void) {
  // No-op: CPU load is now read from SYS_getCPULoad()
}

void DBG_setStat(u16 line, const char *label, s16 value) {
  if (line >= DBG_STAT_MAX)
    return;

  stats[line].label = label;
  stats[line].value = value;
}

void DBG_clearStat(u16 line) {
  if (line >= DBG_STAT_MAX)
    return;

  stats[line].label = NULL;
  stats[line].value = 0;
}

void DBG_draw(void) {
  u16 row;
  u16 i;
  u16 freeMem;
  u16 cpuLoad;

  row = 0;

  // CPU usage (from SGDK's built-in measurement)
  cpuLoad = SYS_getCPULoad();
  sprintf(lineBuf, "CPU:%3d%%", cpuLoad);
  VDP_drawTextBG(dbgPlane, lineBuf, 0, row);
  row++;

  // Free memory
  freeMem = MEM_getFree();
  sprintf(lineBuf, "RAM:%5d", freeMem);
  VDP_drawTextBG(dbgPlane, lineBuf, 0, row);
  row++;

  // Custom stats
  for (i = 0; i < DBG_STAT_MAX; i++) {
    if (stats[i].label != NULL) {
      sprintf(lineBuf, "%-4s:%5d", stats[i].label, stats[i].value);
      VDP_drawTextBG(dbgPlane, lineBuf, 0, row);
    } else {
      // clear line if stat was removed
      VDP_clearTextAreaBG(dbgPlane, 0, row, 15, 1);
    }
    row++;
  }
}

#endif // ENABLE_DEBUG_OVERLAY
