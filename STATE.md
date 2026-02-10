# Project State

## Current Phase
**Phase 0 — Planning & Research**

## Build Status
- SGDK 2.11 (upstream, April 2025)
- GCC 13.2 (m68k-elf)
- Java required for rescomp

## Fork Status
No code changes yet. Currently in analysis/planning phase.

## Open Issue Analysis Complete
| Issue | Root Cause | Status |
|-------|-----------|--------|
| #466 Rescomp templates | No `template` attr handling in TMX parser | Analyzed, fix designed |
| #326 Team Player JOY_2 | `JOY_reset()` skips TP when pad on other port | Analyzed, fix designed |
| #461 Tilemap flip | No reverse iteration in `VDP_setTileMapDataRectEx` | Analyzed, fix designed |
| #363 Retro-Bit timing | Insufficient NOP delays in `TH_CONTROL_PHASE` | Analyzed, needs hardware |

## Key Source Files
- `src/joy.c` — Joypad input (1363 lines)
- `src/vdp_tile.c` — Tilemap rendering (1006 lines)
- `tools/rescomp/src/sgdk/rescomp/type/TMX.java` — TMX parsing (1063 lines)
- `inc/joy.h` — Joypad API (483 lines)

## Enhancement Roadmap
See [ROADMAP.md](ROADMAP.md) for the 7-phase enhancement plan.
