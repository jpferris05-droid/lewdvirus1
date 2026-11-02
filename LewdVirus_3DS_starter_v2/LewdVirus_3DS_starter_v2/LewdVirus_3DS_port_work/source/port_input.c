#include "port_input.h"
#include <string.h>

static const u32 keymap[RPG_KEY_COUNT] = {
    [RPG_KEY_DOWN] = KEY_DUP, /* logical RPG down uses 3DS D-pad down below */
    [RPG_KEY_LEFT] = KEY_DLEFT,
    [RPG_KEY_RIGHT] = KEY_DRIGHT,
    [RPG_KEY_UP] = KEY_DUP,
    [RPG_KEY_A] = KEY_A,
    [RPG_KEY_B] = KEY_B,
    [RPG_KEY_C] = KEY_X,
    [RPG_KEY_X] = KEY_Y,
    [RPG_KEY_Y] = KEY_X,
    [RPG_KEY_Z] = KEY_START,
    [RPG_KEY_L] = KEY_L,
    [RPG_KEY_R] = KEY_R,
    [RPG_KEY_SHIFT] = KEY_R,
    [RPG_KEY_CTRL] = KEY_L,
    [RPG_KEY_ALT] = KEY_SELECT
};

void port_input_update(RpgInputState *s) {
    static bool previous[RPG_KEY_COUNT];
    hidScanInput();
    u32 held = hidKeysHeld(), down = hidKeysDown(), up = hidKeysUp();
    (void)down; (void)up;
    for (int i = 0; i < RPG_KEY_COUNT; ++i) {
        /* Directional down is mapped to the D-pad down key. */
        u32 mask = keymap[i];
        if (i == RPG_KEY_DOWN) mask = KEY_DDOWN;
        bool now = (held & mask) != 0;
        s->down[i] = now;
        s->pressed[i] = now && !previous[i];
        s->released[i] = !now && previous[i];
        previous[i] = now;
    }
    circlePosition cp = {0, 0};
    hidCircleRead(&cp);
    int dx = cp.dx, dy = cp.dy;
    if (held & KEY_DLEFT) dx = -160;
    if (held & KEY_DRIGHT) dx = 160;
    if (held & KEY_DUP) dy = 160;
    if (held & KEY_DDOWN) dy = -160;
    const int dead = 60;
    int hx = dx > dead ? 1 : (dx < -dead ? -1 : 0);
    int hy = dy > dead ? 1 : (dy < -dead ? -1 : 0);
    s->dir8 = (hy > 0 ? 8 : hy < 0 ? 2 : 5) + (hx > 0 ? 1 : hx < 0 ? -1 : 0);
    s->dir4 = hx ? (hx < 0 ? 4 : 6) : (hy ? (hy > 0 ? 8 : 2) : 0);
    s->touch_down = (held & KEY_TOUCH) != 0;
    if (s->touch_down) {
        touchPosition tp;
        hidTouchRead(&tp);
        s->touch_x = tp.px;
        s->touch_y = tp.py;
    }
}
