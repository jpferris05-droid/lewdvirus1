# Lewd Virus — 3DS port work tree (early prototype)

This is the next engineering iteration after recovering the RPG Maker XP data. It is not a complete port, `.3dsx`, or `.cia` yet.

## Current work
- A fixed 4:3 logical display policy: render 512x384 game coordinates into a centered 320x240 area on the 400x240 3DS top screen.
- Coordinate conversion helper for touch/cursor input.
- Initial libctru input adapter mapping D-pad, Circle Pad, face buttons, shoulders and touchscreen into RPG Maker-style key states.
- Asset inventory/preview tool.
- Static API usage inventory from the recovered Ruby scripts.

## Why the game is not running yet
The Windows mkxp-z executable and RGSS DLL are not usable on the 3DS. A compatible Ruby runtime and RPG Maker XP API implementation are still missing. The scripts call the `Graphics`, `Input`, `Bitmap`, `Sprite`, `Viewport`, `RPG::Cache`, `Audio`, and mkxp `System` APIs. The API inventory in `docs/API_INVENTORY.md` gives a starting implementation order.

## Build
Requires devkitPro with devkitARM and libctru. The existing minimal app scaffold is separate; merge `include/port_display.h`, `include/port_input.h`, and `source/port_input.c` into a libctru project and add `-Iinclude` to its compiler flags. No build was run in this workspace because devkitARM/libctru are absent.

## Next milestone
Build a top-screen bitmap renderer and PNG loader, then add filesystem access and audio. After these native subsystems work, evaluate a small Ruby VM port and implement the RPG Maker API compatibility layer. A working title-screen/map slice is the first meaningful game milestone.


## New milestone: native title-image framebuffer test
- Converted recovered `Graphics/Titles/title.png` (512x384) to `assets/title.rgb565` (320x240 RGB565).
- Added a native libctru framebuffer blitter and a 3DSX test app that reads `sdmc:/3ds/LewdVirus/title.rgb565`.
- Added `tools/png_to_rgb565.py` for converting additional artwork.
- Added GitHub Actions cloud-build workflow using the devkitPro devkitARM container. This avoids installing devkitPro on your PC, but requires a GitHub repository with Actions enabled.

### SD-card setup
Copy `assets/title.rgb565` to `SD:/3ds/LewdVirus/title.rgb565`. It must be 153,600 bytes.

### Scope
This milestone tests native graphics/input only. It does not yet execute Ruby scripts, load RPG Maker maps, or implement gameplay.
