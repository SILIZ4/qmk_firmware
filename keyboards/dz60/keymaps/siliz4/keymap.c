#include QMK_KEYBOARD_H
#include "enum_def.h"


#define ___pass KC_TRNS


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_GESC, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, XXXXXXX,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, XXXXXXX,
        KC_LCTL, LGUI_TAP, KC_LALT,                   KC_SPC,  KC_SPC,  KC_SPC,           KC_RALT, KC_RGUI, XXXXXXX, MO(3),   KC_RCTL
    ),

    [_FUNC] = LAYOUT(
        TO(_DEFAULT), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  ___pass, ___pass,
        ___pass,      ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass,  ___pass, ___pass, ___pass,
        ___pass,      ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass,  ___pass,          ___pass,
        ___pass,      ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass, ___pass,  ___pass, ___pass, ___pass,
        ___pass,      ___pass, ___pass,                   ___pass, ___pass, ___pass,          ___pass, ___pass,  ___pass, ___pass, ___pass
    ),

    // Based on vim commands, Shift+4 is set manually to KC_END
    [_NAV] = LAYOUT(
        TO(_DEFAULT), ___pass, ___pass, ___pass,   KC_4,    ___pass, ___pass, ___pass, ___pass, ___pass,  KC_HOME, ___pass, ___pass, ___pass, ___pass,
        ___pass,      ___pass, ___pass, ___pass,   ___pass, ___pass, ___pass, KC_PGUP, ___pass, _______,  ___pass, ___pass, ___pass, ___pass,
        ___pass,      ___pass, ___pass, KC_PGDOWN, ___pass, ___pass, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, ___pass, ___pass,          ___pass,
        ___pass,      ___pass, ___pass, ___pass,   ___pass, ___pass, ___pass, ___pass, ___pass, ___pass,  ___pass, ___pass, ___pass, ___pass,
        ___pass,      ___pass, ___pass,                     ___pass, ___pass, ___pass,          ___pass,  ___pass, ___pass, ___pass, ___pass
    ),

    [_TMP_LAYER] = LAYOUT(
        KC_GRAVE,  TG(_NAV), TG(_FUNC), _______,   _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        _______,   RGB_TOG,  RGB_HUI,   RGB_SAI,   RGB_VAI,     RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   KC_BRIU,  KC_BRID,   KC__VOLUP, KC__VOLDOWN, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,   _______,  _______,   _______,   BL_DEC,      BL_TOGG, BL_INC,  BL_STEP, _______, X(LEFT_QUOTE), X(RIGHT_QUOTE), _______, _______, _______,
        //_______,   _______,  _______,   _______,   BL_DEC,      BL_TOGG, BL_INC,  BL_STEP, _______, UC(0x00AB), UC(0x00BB), _______, _______, _______,
        RESET,     _______,  _______,                           KC_PSCR, KC_PSCR, KC_PSCR,          _______, _______, _______, _______, _______
    )

};

void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t lgui_tapTimer;
    static bool altGRHeld = false;

    switch (keycode) {

    // Quick tap on left Win key toggles _NAV layer
    case LGUI_TAP:
        if(record->event.pressed){
            lgui_tapTimer = timer_read();
            register_mods(MOD_LGUI);
        } 
        else {
            unregister_mods(MOD_LGUI);
            if (timer_elapsed(lgui_tapTimer) < TAPPING_TERM)
                layer_invert(_NAV);
        }
        break;

    case KC_RALT:
        altGRHeld = record->event.pressed;
        break;

    // Send KC_GRV when RALT is held and KC_GESC pressed
    case KC_GESC:
        if (record->event.pressed) {
            if (altGRHeld) {
                tap_code16(KC_GRV);
                return false;
            }
        }
        break;

    // Send KC_END when Shift+4 and _NAV layer activated
    case KC_4:
        if (record->event.pressed) {
            if (IS_LAYER_ON(_NAV)) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    uint16_t current_mods = get_mods();
                    clear_mods();
                    tap_code16(KC_END);
                    set_mods(current_mods);
                    return false;
                }
            }
        }
        break;

    }

    return true;
};
