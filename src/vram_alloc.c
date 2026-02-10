#include "config.h"
#include "types.h"

#include "vdp.h"
#include "vram_alloc.h"

static u16 nextFreeIndex;

void VRAM_init(void) { nextFreeIndex = TILE_USER_INDEX; }

s16 VRAM_alloc(u16 numTiles) {
  u16 result;

  if (numTiles == 0)
    return -1;
  if ((nextFreeIndex + numTiles - 1) > TILE_USER_MAX_INDEX)
    return -1;

  result = nextFreeIndex;
  nextFreeIndex += numTiles;

  return (s16)result;
}

void VRAM_free(u16 index, u16 numTiles) {
  // simple top-of-stack free: if freeing the most recent allocation,
  // reclaim the space
  if ((index + numTiles) == nextFreeIndex) {
    nextFreeIndex = index;
  }
  // otherwise: no-op (a full free-list allocator would be needed
  // for general-purpose free, but that adds complexity)
}

void VRAM_reset(void) { nextFreeIndex = TILE_USER_INDEX; }

u16 VRAM_getUsed(void) { return nextFreeIndex - TILE_USER_INDEX; }

u16 VRAM_getFree(void) { return (TILE_USER_MAX_INDEX - nextFreeIndex) + 1; }
