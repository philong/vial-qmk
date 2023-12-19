#pragma once

#include QMK_KEYBOARD_H

#include "quantum/keymap_extras/keymap_colemak.h"

// Left-hand home row mods
#define MT_A LGUI_T(KC_A)
#define MT_S LALT_T(KC_S)
#define MT_D LSFT_T(KC_D)
#define MT_F LCTL_T(KC_F)
#define MT_X RALT_T(KC_X)

// Right-hand home row mods
#define MT_J RCTL_T(KC_J)
#define MT_K RSFT_T(KC_K)
#define MT_L LALT_T(KC_L)
#define MT_SCLN RGUI_T(KC_SCLN)
#define MT_DOT RALT_T(KC_DOT)

enum layers {
    _BASE = 0,
    _NUM,
    _NUM2,
    _SYM,
    _SYM_RALT,
    _NAV,
    _FUN,
    _MOUSE,
};

enum user_keycode {
    U_LAYER_LOCK = QK_KB_0,
    U_CAPS_WORD_TOGGLE,
    U_NUM_WORD_TOGGLE, // remove?
    U_SEL_WORD,
    U_JOIN_LN,
    U_REPEAT,
    U_ALT_REPEAT,
    U_TURBO_CLICK,
    U_CURRENT_DIRECTORY,
    U_UP_DIRECTORY, // remove?
    U_DOT, // remove?
    U_THREE_DOTS,
    U_DOUBLE_COLON, // remove?
    U_EQUAL,
    U_STRICT_EQUAL, // remove?
    U_NOT_EQUAL,
    U_STRICT_NOT_EQUAL, // remove?
    U_LOWER_THAN_OR_EQUAL,
    U_GREATER_THAN_OR_EQUAL, // remove?
    U_ARROW,
    U_DOUBLE_ARROW, // remove?
    U_AND_OPERATOR,
    U_OR_OPERATOR, // remove?
    U_DOUBLE_MINUS,
    U_DOUBLE_PLUS, // remove?
    U_DOUBLE_SLASH,
    U_DOUBLE_QUESTION, // remove?
    U_LEFT_SHIFT,
    U_RIGHT_SHIFT, // remove?
    U_DOUBLE_QUOTE,
    U_USERNAME,
    U_CG_TOGG,
    U_CM_TOGG,
    U_AUTOCOMPLETE,
    U_OS_LCTL,
    U_OS_LSFT,
    U_OS_LALT,
    U_OS_LGUI,
    U_OS_RCTL,
    U_OS_RSFT,
    U_OS_RALT,
    U_OS_RGUI,
    U_AC_TOGG,
    U_QUOP,
};

#ifndef QK_REPEAT_KEY
    #define QK_REPEAT_KEY U_REPEAT
    #define QK_ALT_REPEAT_KEY U_ALT_REPEAT
#endif
