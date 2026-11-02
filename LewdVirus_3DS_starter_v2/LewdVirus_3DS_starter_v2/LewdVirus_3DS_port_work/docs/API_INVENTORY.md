# Recovered script API inventory (static scan)

A scan of the 460 recovered Ruby files shows the main compatibility surface:

| API | Occurrences | Most-used members |
|---|---:|---|
| Graphics | 1,252 | width (513), height (397), update (266), transitions/freezes |
| Input | 885 | trigger (416), update (231), repeat (105), press (46) |
| Audio | 26 | BGM/BGS/ME/SE play, stop and fade |
| Bitmap | 81 | bitmap creation/drawing/loading |
| Sprite | 120 | sprite rendering |
| Viewport | 100 | clipping/layering |
| RPG::Cache | 76 | transition (53), retain (11), load_bitmap (7) |
| System | 366 | uptime (344), language, data directory, mounts, power state |

This is a textual occurrence scan, not a complete semantic dependency graph. The next runtime implementation should prioritize `Graphics`, `Input`, `Bitmap`, `Sprite`, `Viewport`, `RPG::Cache`, `Audio`, and the mkxp `System` methods. The especially high `System.uptime` count means a compatible monotonic timer is important.

## Display decision

The original logical canvas is 512x384 (4:3). The 3DS top screen is 400x240 (5:3). This port keeps the game's logical 512x384 coordinates and initially renders to a centered 320x240 viewport on the top screen, leaving 40-pixel side bars. This preserves aspect ratio rather than stretching the artwork. Touch coordinates need the inverse transform before being passed to RPG Maker scripts.

## Important limitation

This inventory does not mean the Ruby VM or RPG Maker renderer has been ported. It is the compatibility contract to implement and test in small increments. The native C input/display helpers in this work tree are a first step, not a runnable game engine.
