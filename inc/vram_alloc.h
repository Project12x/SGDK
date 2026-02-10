/**
 *  \file vram_alloc.h
 *  \brief Simple VRAM tile index allocator
 *  \author Antigravity
 *  \date 02/2026
 *
 * Provides a bump allocator for VRAM tile indices in the user region
 * (TILE_USER_INDEX to TILE_USER_MAX_INDEX). Use this instead of manually
 * tracking curTileInd to avoid tile index collisions when loading and
 * unloading tilesets dynamically.
 *
 * Usage:
 *   VRAM_init();                        // reset allocator
 *   u16 idx = VRAM_alloc(numTiles);     // get tile index for your tileset
 *   VDP_loadTileData(data, idx, num, DMA);
 *   // ... later ...
 *   VRAM_free(idx, numTiles);           // mark region as free (no compaction)
 */

#ifndef _VRAM_ALLOC_H_
#define _VRAM_ALLOC_H_

/**
 *  \brief
 *      Initialize the VRAM tile allocator.
 *      Resets the allocation pointer to TILE_USER_INDEX.
 */
void VRAM_init(void);

/**
 *  \brief
 *      Allocate a contiguous block of VRAM tile indices.
 *
 *  \param numTiles
 *      Number of tiles to allocate.
 *  \return
 *      Starting tile index, or -1 if not enough space.
 */
s16 VRAM_alloc(u16 numTiles);

/**
 *  \brief
 *      Release a previously allocated tile region.
 *
 *  \param index
 *      Starting tile index returned by VRAM_alloc().
 *  \param numTiles
 *      Number of tiles to free.
 *
 *  Note: This is a simple bump allocator. Free merely updates
 *  the high-water mark if the freed region is at the top.
 *  For full free-list management, use the Sprite Engine's VRAM system.
 */
void VRAM_free(u16 index, u16 numTiles);

/**
 *  \brief
 *      Reset the allocator completely. All previous allocations are lost.
 */
void VRAM_reset(void);

/**
 *  \brief
 *      Returns number of tile indices currently allocated.
 */
u16 VRAM_getUsed(void);

/**
 *  \brief
 *      Returns number of tile indices available.
 */
u16 VRAM_getFree(void);

#endif // _VRAM_ALLOC_H_
