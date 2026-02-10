# How To

## Prerequisites
- Windows (primary), Linux/macOS via Docker
- Java Runtime (for rescomp)
- GCC 13.2 m68k-elf (bundled in `bin/` for Windows)
- An emulator: [BlastEm](https://www.retrodev.com/blastem/), [Gens KMod](https://segaretro.org/Gens_KMod), or [Exodus](https://www.exodusemulator.com/)

## Environment Setup

Set `GDK` environment variable to the SGDK root:
```
set GDK=c:\Users\estee\Desktop\My Stuff\Code\Antigravity\SGDK\SGDK
```

Or add to system environment variables permanently.

## Build a Project

From a project directory containing `main.c` and `res/`:
```bash
%GDK%/bin/make -f %GDK%/makefile.gen
```

Output: `out/rom.bin`

## Create a New Project

Copy `project/template/` to a new directory:
```bash
xcopy /E /I "%GDK%\project\template" MyGame
```

Edit `src/main.c`, add resources to `res/`, build.

## Run in Emulator

```bash
blastem out/rom.bin
```

## Resource Compilation

Resources are declared in `.res` files and compiled by rescomp:
```
IMAGE title_bg "gfx/title.png" BEST
SPRITE player "gfx/player.png" 4 4 FAST 5
XGM2 bgm "music/stage1.xgm2"
```

See `bin/rescomp.txt` for full resource type reference.

## Debug Build

Add `-debug` flag or set `DEBUG=1`:
```bash
%GDK%/bin/make -f %GDK%/makefile.gen DEBUG=1
```

Enables KDebug output visible in emulators with debug console (Gens KMod, BlastEm).

## Common Tasks

### Add a new source file
Place `.c` files in `src/`. The makefile auto-discovers them.

### Add a new header
Place `.h` files in `inc/` or `src/`. Use `#include "myheader.h"`.

### Use the sprite engine
```c
#include "genesis.h"

SPR_init();
Sprite* s = SPR_addSprite(&my_sprite, x, y, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));
// In game loop:
SPR_update();
```

### Use the MAP engine
```c
MAP_create(&my_map, BG_B, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind));
// In game loop:
MAP_scrollTo(map, scrollX, scrollY);
```

## Upstream Docs
- Wiki: https://github.com/Stephane-D/SGDK/wiki
- API Docs: http://stephane-d.github.io/SGDK/
- Resource format: `bin/rescomp.txt`
