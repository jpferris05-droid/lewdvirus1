#ifndef PORT_INPUT_H
#define PORT_INPUT_H
#include <3ds.h>
#include <stdbool.h>

typedef enum {
    RPG_KEY_DOWN, RPG_KEY_LEFT, RPG_KEY_RIGHT, RPG_KEY_UP,
    RPG_KEY_A, RPG_KEY_B, RPG_KEY_C, RPG_KEY_X, RPG_KEY_Y, RPG_KEY_Z,
    RPG_KEY_L, RPG_KEY_R, RPG_KEY_SHIFT, RPG_KEY_CTRL, RPG_KEY_ALT,
    RPG_KEY_COUNT
} RpgKey;

typedef struct {
    bool down[RPG_KEY_COUNT];
    bool pressed[RPG_KEY_COUNT];
    bool released[RPG_KEY_COUNT];
    int dir4; /* RPG Maker convention: 2,4,6,8 or 0 */
    int dir8; /* 1..9 keypad directions, 5 means neutral */
    int touch_x, touch_y;
    bool touch_down;
} RpgInputState;

void port_input_update(RpgInputState *state);
#endif
