#ifndef PORT_DISPLAY_H
#define PORT_DISPLAY_H
#include <stdbool.h>
#include <stdint.h>

/* The original RPG Maker XP canvas is 512x384 (4:3).
 * Keep that logical coordinate system and render it into a 320x240 viewport
 * centered on the 3DS top screen (400x240). This avoids distorting UI/art.
 */
#define RPG_LOGICAL_W 512
#define RPG_LOGICAL_H 384
#define TOP_SCREEN_W  400
#define TOP_SCREEN_H  240
#define GAME_VIEW_W   320
#define GAME_VIEW_H   240
#define GAME_VIEW_X   40
#define GAME_VIEW_Y   0

/* Convert top-screen pixel coordinates to original game coordinates.
 * Returns false for the side bars or coordinates outside the viewport.
 */
static inline bool port_screen_to_game(int sx, int sy, int *gx, int *gy) {
    if (sx < GAME_VIEW_X || sx >= GAME_VIEW_X + GAME_VIEW_W ||
        sy < GAME_VIEW_Y || sy >= GAME_VIEW_Y + GAME_VIEW_H) return false;
    if (gx) *gx = ((sx - GAME_VIEW_X) * RPG_LOGICAL_W) / GAME_VIEW_W;
    if (gy) *gy = ((sy - GAME_VIEW_Y) * RPG_LOGICAL_H) / GAME_VIEW_H;
    return true;
}
#endif
