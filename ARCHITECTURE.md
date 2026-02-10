# Architecture

## Hardware Target
Sega Mega Drive / Genesis
- **68000** @ 7.67 MHz — main CPU (game logic, VDP control)
- **Z80** @ 3.58 MHz — sound CPU (XGM2 driver)
- **VDP** — 2 scroll planes (A, B), window plane, 80 sprites, 64KB VRAM
- **RAM** — 64KB main, 8KB Z80, 64 colors from 512 palette
- **Sound** — YM2612 (FM) + SN76489 (PSG)

## SGDK Layer Diagram

```
+------------------------------------------+
|              Game Code (C)               |
+------------------------------------------+
|         SGDK Library (src/, inc/)         |
|  VDP  | Sprite | MAP | Joy | Sound | Sys |
+-------+--------+-----+-----+-------+-----+
|          Hardware Abstraction             |
|  DMA  | Timer | Memory | Z80 Ctrl | IO  |
+------------------------------------------+
|        68000 / VDP / Z80 Hardware        |
+------------------------------------------+
```

## Key Source Modules

| Module | Source | Header | Purpose |
|--------|--------|--------|---------|
| VDP Tile | `src/vdp_tile.c` | `inc/vdp_tile.h` | Tilemap loading, drawing, scrolling |
| VDP Sprite | `src/vdp_spr.c` | `inc/vdp_spr.h` | Hardware sprite management |
| Sprite Engine | `src/sprite_eng.c` | `inc/sprite_eng.h` | High-level sprite system with VRAM management |
| MAP | `src/map.c` | `inc/map.h` | Large world scrolling engine |
| Joy | `src/joy.c` | `inc/joy.h` | Controller input (pads, mice, multitaps, guns) |
| Sound | `src/xgm2.c` | `inc/xgm2.h` | XGM2 music/SFX driver interface |
| DMA | `src/dma.c` | `inc/dma.h` | DMA queue for VRAM transfers |
| Sys | `src/sys.c` | `inc/sys.h` | Interrupts, VBlank, system init |
| Memory | `src/memory.c` | `inc/memory.h` | Heap allocator |
| Math | `src/maths.c` | `inc/maths.h` | fix16 math, trig, random |

## Build Pipeline

```
.res files --> rescomp.jar --> .s/.h (resources as ASM data)
.c files  --> m68k-elf-gcc --> .o (object files)
.s files  --> m68k-elf-as  --> .o (object files)
                  |
            m68k-elf-ld (md.ld linker script)
                  |
              rom.bin (final ROM)
```

## Planned Enhancement Modules

See [ROADMAP.md](ROADMAP.md). New modules will live in `src/` and `inc/` following existing conventions:
- `entity.c` / `entity.h` — Entity Pool (Phase 1)
- `collision.c` / `collision.h` — Collision system (Phase 2A)
- `plat_physics.c` / `plat_physics.h` — Platformer physics (Phase 2B, optional)
- `camera.c` / `camera.h` — Camera system (Phase 3)
- `map_trigger.c` / `map_trigger.h` — MAP triggers (Phase 4)
- `raster.c` / `raster.h` — Raster effects (Phase 5)
