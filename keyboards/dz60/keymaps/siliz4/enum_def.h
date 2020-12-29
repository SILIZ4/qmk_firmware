#ifndef ENUM_DEF_H
#define ENUM_DEF_H


enum preonic_layers {
    _DEFAULT,
    _FUNC,
    _NAV,
    _TMP_LAYER,
};

enum unicode_names {
    LEFT_QUOTE,
    RIGHT_QUOTE,
};

const uint32_t PROGMEM unicode_map[] = {
    [LEFT_QUOTE]  = 0x00AB,
    [RIGHT_QUOTE] = 0x00BB,
};

enum custom_keycodes {
    LGUI_TAP = SAFE_RANGE,
};


#endif
