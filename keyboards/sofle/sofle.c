// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef SWAP_HANDS_ENABLE

__attribute__((weak)) const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] =
    // The LAYOUT macro could work for this, but it was harder to figure out the
    // identity using it.

    // This is the identity layout.
    /*
    {
        { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0} },
        { {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1} },
        { {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2} },
        { {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3} },
        { {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4} },

        { {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5} },
        { {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6} },
        { {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7} },
        { {0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8} },
        { {0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9} },
    };
    */

    // This is the mirror, q <-> p, w <-> o, etc...
    {
        {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}}, {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}, {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}}, {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}}, {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}},

        {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}}, {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}}, {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}}, {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}, {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
};

#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {1, 0};
#    endif

#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

void print_status_narrow(void) {
    oled_write_P(PSTR("\n\n"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        default:
            oled_write_P(PSTR("Mod\n"), false);
            break;
    }
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
        case 1:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Raise"), false);
            break;
        case 3:
            oled_write_P(PSTR("Lower"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return true;
}

#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif
