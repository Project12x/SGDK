# Changelog

All notable changes to this SGDK fork will be documented in this file.
See upstream [changelog.txt](changelog.txt) for official SGDK release history.

Format based on [Keep a Changelog](https://keepachangelog.com/).

## [Unreleased]

### Added
- Standard project documentation: ARCHITECTURE, CHANGELOG, HOWTO, ROADMAP, STATE
- Open issue analysis for #326, #363, #436, #461, #466
- `VDP_setTileMapDataRectFlipped()` and `VDP_setTileMapExFlipped()` for HFlip/VFlip tilemap drawing (#461)
- `JOY_justPressed()`, `JOY_justReleased()`, `JOY_changed()` polling-style input edge detection
- Frame timer system (`frame_timer.h`) — 8-slot one-shot/repeating alarm callbacks
- Debug overlay (`debug_overlay.h`) — compile-gated on-screen CPU%, free RAM, custom stats

### Fixed
- Rescomp now fully supports Tiled object templates (.tx files) with attribute and property merging (#466)
- Team Player and Mouse peripherals now auto-detected independently per port (#326)

### Planned
- Phase 0: Bug fixes (#466 rescomp templates, #326 Team Player, #461 tilemap flip, #363 Retro-Bit timing)
- Phase 1: Entity Pool system
- Phase 2A: Collision system (spatial grid + tilemap)
- Phase 2B: Platformer physics module (optional)
- Phase 3: Camera system
- Phase 4: MAP trigger system
- Phase 5: Raster effects framework
- Phase 6: Interactive music (XGM2 extension)
