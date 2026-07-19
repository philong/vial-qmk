// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

// Shared philong-eurkey keymap: EurKEY host variant of users/philong
// (host runs the QWERTY-based EurKEY layout instead of the custom French
// Colemak). Layers are defined with the keyboard-agnostic
// LAYOUT_LR macro (4x12 + 6 thumbs, the silakka54 superset); each keyboard's
// keymap.c defines LAYOUT_LR in terms of its own layout macro - dropping the
// rows/columns it does not have - and then #includes this file. Everything a
// layout may drop (number row, outer columns) is non-essential: all vital
// functions live within the 3x5+3 core anchored by the Q and P keys.

#include QMK_KEYBOARD_H

#include "qmk_settings.h"
#include "vial.h"
#include "via.h"
#include "dynamic_keymap.h"


enum layers {
    LAYER_BASE = 0,
    LAYER_NUM,
    LAYER_NAV,
    LAYER_SYM,
    LAYER_FUN,
    LAYER_SYM2,
    LAYER_MOUSE,
    LAYER_NAV_NUM,
    LAYER_GUI_NUM,
    LAYER_GUI_NAV,
    LAYER_ADJUST,
    LAYER_GAME,
};

enum user_keycode {
    U_SELECT_WORD = QK_KB_0,
    U_SELECT_WORD_BACK,
    U_SELECT_LINE,
    U_JOIN_LN,
    U_SRCHSEL,
    U_USERNAME,

    U_CURRENT_DIRECTORY,
    U_UP_DIRECTORY,
    U_DOT,
    U_THREE_DOTS,
    U_DOUBLE_COLON,
    U_EQUAL,
    U_STRICT_EQUAL,
    U_NOT_EQUAL,
    U_STRICT_NOT_EQUAL,
    U_LOWER_THAN_OR_EQUAL,
    U_GREATER_THAN_OR_EQUAL,
    U_ARROW,
    U_DOUBLE_ARROW,
    U_AND_OPERATOR,
    U_OR_OPERATOR,
    U_DOUBLE_MINUS,
    U_DOUBLE_PLUS,
    U_DOUBLE_SLASH,
    U_DOUBLE_QUESTION,
    U_LEFT_SHIFT,
    U_RIGHT_SHIFT,
    U_DOUBLE_QUOTE,
    U_DOUBLE_BACKTICK,
    U_ELEMENT,
    U_DOUBLE_UNDERSCORE,
    U_ADD_ASSIGN,
    U_SUB_ASSIGN,
    U_PARENTHESES,
    U_BRACKETS,
    U_BRACES,

    U_EURKEY_FR_TOGG,
    U_PUNCTUATION_MOD_TOGG,

    U_LOGIN_ADMIN,
    U_LOGIN_DEMO,

    U_QUOPOSTROKEY,
    U_QUOPOSTROKEY_TOGG,
};

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [LAYER_BASE] = LAYOUT_LR(
        TD(16),          TD(11),          TD(12),          TD(13),          TD(14),          TD(15),          KC_LEFT,         KC_DOWN,         KC_UP,           KC_RGHT,         TD(2),           TD(3),
        TD(4),           KC_Q,            LT(LAYER_GUI_NUM, KC_W), LT(LAYER_GUI_NUM, KC_E), LT(LAYER_GUI_NUM, KC_R), KC_T, KC_Y,     LT(LAYER_GUI_NAV, KC_U), LT(LAYER_GUI_NAV, KC_I), LT(LAYER_GUI_NAV, KC_O), KC_P,  TD(0),
        TD(1),           LGUI_T(KC_A),    LALT_T(KC_S),    LSFT_T(KC_D),    LCTL_T(KC_F),    LT(LAYER_GUI_NUM, KC_G), LT(LAYER_GUI_NAV, KC_H), RCTL_T(KC_J), RSFT_T(KC_K), LALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
        LSFT_T(KC_MINS), KC_Z,            KC_X,            LSFT_T(KC_C),    RALT_T(KC_V),    KC_B,            KC_N,            RALT_T(KC_M),    RSFT_T(KC_COMM), KC_DOT,          KC_SLSH,         LT(0, KC_MINS),
                                                           LT(5, KC_ESC),   LT(1, KC_SPC),   LT(3, KC_TAB),   LT(4, KC_ENT),   LT(2, KC_BSPC),  LT(6, KC_DEL)
    ),

    [LAYER_NUM] = LAYOUT_LR(
        _______,         LGUI(KC_6),      LGUI(KC_7),      LGUI(KC_8),      LGUI(KC_9),      LGUI(KC_0),      KC_H,            KC_J,            KC_K,            KC_L,            KC_E,            KC_D,
        _______,         KC_INS,          KC_HOME,         KC_UP,           KC_END,          KC_PGUP,         KC_EQL,          KC_7,            KC_8,            KC_9,            KC_QUOT,         KC_PPLS,
        _______,         LGUI_T(KC_CAPS), LALT_T(KC_LEFT), LSFT_T(KC_DOWN), LCTL_T(KC_RGHT), KC_PGDN,         KC_MINS,         KC_4,            KC_5,            KC_6,            LT(0, KC_DOT),   S(KC_9),
        _______,         LT(0, KC_Z),     LT(0, KC_X),     LT(0, KC_C),     LT(0, KC_V),     LT(0, KC_B),     KC_0,            KC_1,            KC_2,            KC_3,            KC_BSLS,         S(KC_0),
                                                           U_LOGIN_DEMO,    _______,         U_LOGIN_ADMIN,   _______,         _______,         _______
    ),

    [LAYER_NAV] = LAYOUT_LR(
        S(KC_GRV),       S(KC_1),         S(KC_2),         S(KC_3),         S(KC_4),         S(KC_5),         S(KC_6),         S(KC_7),         S(KC_8),         S(KC_9),         S(KC_0),         S(KC_MINS),
        _______,         KC_INS,          KC_HOME,         KC_UP,           KC_END,          KC_PGUP,         KC_VOLU,         KC_MPLY,         KC_MPRV,         KC_MNXT,         KC_BRIU,         _______,
        _______,         CW_TOGG,         KC_LEFT,         KC_DOWN,         KC_RGHT,         KC_PGDN,         KC_VOLD,         KC_RCTL,         KC_RSFT,         KC_LALT,         RGUI_T(KC_BRID), _______,
        _______,         LT(0, KC_Z),     LT(0, KC_X),     LT(0, KC_C),     LT(0, KC_V),     LT(0, KC_B),     KC_MUTE,         KC_RALT,         QK_REPEAT_KEY,   QK_ALT_REPEAT_KEY, KC_SLEP,       _______,
                                                           _______,         _______,         _______,         _______,         _______,         _______
    ),

    [LAYER_SYM] = LAYOUT_LR(
        RALT(KC_GRV),    RALT(KC_1),      RALT(KC_2),      RALT(KC_3),      RALT(KC_4),      RALT(KC_5),      RALT(KC_6),      RALT(KC_7),      RALT(KC_8),      RALT(KC_9),      RALT(KC_0),      RALT(KC_MINS),
        _______,         KC_PSCR,         KC_F7,           KC_F8,           KC_F9,           KC_F12,          S(KC_EQL),       S(KC_7),         S(KC_8),         S(KC_9),         S(KC_QUOT),      _______,
        _______,         LGUI_T(KC_SCRL), LALT_T(KC_F4),   LSFT_T(KC_F5),   LCTL_T(KC_F6),   KC_F11,          S(KC_MINS),      S(KC_4),         S(KC_5),         S(KC_6),         LT(0, KC_DOT),   _______,
        _______,         KC_PAUS,         KC_F1,           LSFT_T(KC_F2),   RALT_T(KC_F3),   KC_F10,          S(KC_0),         S(KC_1),         S(KC_2),         S(KC_3),         S(KC_BSLS),      _______,
                                                           _______,         _______,         _______,         KC_ENT,          KC_BSPC,         KC_DEL
    ),

    [LAYER_FUN] = LAYOUT_LR(
        RALT(KC_GRV),    RALT(KC_1),      RALT(KC_2),      RALT(KC_3),      RALT(KC_4),      RALT(KC_5),      RALT(KC_6),      RALT(KC_7),      RALT(KC_8),      RALT(KC_9),      RALT(KC_0),      RALT(KC_MINS),
        _______,         KC_PSCR,         KC_F7,           KC_F8,           KC_F9,           KC_F12,          _______,         _______,         _______,         _______,         _______,         _______,
        _______,         KC_SCRL,         KC_F4,           KC_F5,           KC_F6,           KC_F11,          _______,         KC_RCTL,         KC_RSFT,         KC_LALT,         KC_RGUI,         _______,
        _______,         KC_PAUS,         KC_F1,           KC_F2,           KC_F3,           KC_F10,          _______,         KC_RALT,         _______,         _______,         _______,         _______,
                                                           KC_ESC,          KC_SPC,          KC_TAB,          _______,         _______,         _______
    ),

    [LAYER_SYM2] = LAYOUT_LR(
        S(ALGR(KC_GRV)), S(ALGR(KC_1)),   S(ALGR(KC_2)),   S(ALGR(KC_3)),   S(ALGR(KC_4)),   S(ALGR(KC_5)),   S(ALGR(KC_6)),   S(ALGR(KC_7)),   S(ALGR(KC_8)),   S(ALGR(KC_9)),   S(ALGR(KC_0)),   S(ALGR(KC_MINS)),
        _______,         KC_PEQL,         KC_P7,           KC_P8,           KC_P9,           KC_PPLS,         RALT(KC_EQL),    RALT(KC_7),      RALT(KC_8),      RALT(KC_9),      RALT(KC_QUOT),   _______,
        _______,         LGUI_T(KC_NUM),  LALT_T(KC_P4),   LSFT_T(KC_P5),   LCTL_T(KC_P6),   KC_PMNS,         RALT(KC_MINS),   RALT(KC_4),      RALT(KC_5),      RALT(KC_6),      LT(0, KC_DOT),   _______,
        _______,         KC_PDOT,         KC_P1,           KC_P2,           RALT_T(KC_P3),   KC_P0,           RALT(KC_0),      RALT(KC_1),      RALT(KC_2),      RALT(KC_3),      RALT(KC_BSLS),   _______,
                                                           _______,         _______,         _______,         KC_PENT,         _______,         KC_APP
    ),

    [LAYER_MOUSE] = LAYOUT_LR(
        S(ALGR(KC_GRV)), S(ALGR(KC_1)),   S(ALGR(KC_2)),   S(ALGR(KC_3)),   S(ALGR(KC_4)),   S(ALGR(KC_5)),   S(ALGR(KC_6)),   S(ALGR(KC_7)),   S(ALGR(KC_8)),   S(ALGR(KC_9)),   S(ALGR(KC_0)),   S(ALGR(KC_MINS)),
        _______,         KC_WFWD,         KC_WH_L,         KC_MS_U,         KC_WH_R,         KC_WH_U,         _______,         _______,         _______,         _______,         _______,         _______,
        _______,         KC_WBAK,         KC_MS_L,         KC_MS_D,         KC_MS_R,         KC_WH_D,         _______,         KC_RCTL,         KC_RSFT,         KC_LALT,         KC_LGUI,         _______,
        _______,         KC_WREF,         KC_BTN4,         KC_BTN5,         KC_BTN1,         KC_BTN2,         _______,         KC_RALT,         KC_ACL0,         KC_ACL1,         KC_ACL2,         _______,
                                                           KC_BTN3,         KC_BTN1,         KC_BTN2,         _______,         _______,         _______
    ),

    [LAYER_NAV_NUM] = LAYOUT_LR(
        S(KC_GRV),       S(KC_1),         S(KC_2),         S(KC_3),         S(KC_4),         S(KC_5),         S(KC_6),         S(KC_7),         S(KC_8),         S(KC_9),         S(KC_0),         S(KC_MINS),
        _______,         KC_INS,          KC_HOME,         KC_UP,           KC_END,          KC_PGUP,         KC_EQL,          KC_7,            KC_8,            KC_9,            KC_QUOT,         KC_PPLS,
        _______,         LGUI_T(KC_CAPS), KC_LEFT,         KC_DOWN,         KC_RGHT,         KC_PGDN,         KC_MINS,         KC_4,            KC_5,            KC_6,            LT(0, KC_DOT),   S(KC_9),
        _______,         LT(0, KC_Z),     LT(0, KC_X),     LT(0, KC_C),     LT(0, KC_V),     LT(0, KC_B),     KC_0,            KC_1,            KC_2,            KC_3,            KC_BSLS,         S(KC_0),
                                                           U_LOGIN_DEMO,    _______,         U_LOGIN_ADMIN,   KC_PENT,         KC_BSPC,         KC_DEL
    ),

    // Held via W/E/R/G: GUI (+Alt/Shift/Ctrl for W/E/R) is registered as real
    // mods by process_gui_layers(), so the plain keys below combine with them.
    [LAYER_GUI_NUM] = LAYOUT_LR(
        _______,         _______,         _______,         _______,         _______,         _______,         KC_6,            KC_7,            KC_8,            KC_9,            KC_0,            KC_MINS,
        _______,         _______,         _______,         _______,         _______,         _______,         KC_EQL,          KC_7,            KC_8,            KC_9,            KC_QUOT,         KC_PPLS,
        _______,         _______,         _______,         _______,         _______,         _______,         KC_MINS,         KC_4,            KC_5,            KC_6,            KC_PDOT,         S(KC_9),
        _______,         _______,         _______,         _______,         _______,         _______,         KC_0,            KC_1,            KC_2,            KC_3,            KC_BSLS,         S(KC_0),
                                                           _______,         _______,         _______,         KC_PENT,         KC_BSPC,         KC_DEL
    ),

    // Held via U/I/O/H: GUI (+Ctrl/Shift/Alt for U/I/O) is registered as real
    // mods by process_gui_layers(), so the plain keys below combine with them.
    [LAYER_GUI_NAV] = LAYOUT_LR(
        KC_GRV,          KC_1,            KC_2,            KC_3,            KC_4,            KC_5,            _______,         _______,         _______,         _______,         _______,         _______,
        _______,         KC_INS,          KC_HOME,         KC_UP,           KC_END,          KC_PGUP,         _______,         _______,         _______,         _______,         _______,         _______,
        _______,         CW_TOGG,         KC_LEFT,         KC_DOWN,         KC_RGHT,         KC_PGDN,         _______,         _______,         _______,         _______,         _______,         _______,
        _______,         KC_Z,            KC_X,            KC_C,            KC_V,            KC_B,            _______,         _______,         _______,         _______,         _______,         _______,
                                                           KC_ESC,          KC_SPC,          KC_TAB,          _______,         _______,         _______
    ),

    [LAYER_ADJUST] = LAYOUT_LR(
        _______,         _______,         _______,         _______,         _______,         _______,         _______,         _______,         _______,         _______,         _______,         _______,
        _______,         QK_BOOT,         _______,         _______,         _______,         _______,         _______,         _______,         _______,         _______,         U_QUOPOSTROKEY_TOGG, _______,
        _______,         QK_REBOOT,       _______,         _______,         _______,         _______,         _______,         CG_TOGG,         AC_TOGG,         _______,         _______,         _______,
        _______,         QK_CLEAR_EEPROM, _______,         _______,         _______,         TG(LAYER_GAME),  _______,         U_EURKEY_FR_TOGG,       U_PUNCTUATION_MOD_TOGG, _______,         _______,         _______,
                                                           _______,         _______,         _______,         _______,         _______,         _______
    ),

    [LAYER_GAME] = LAYOUT_LR(
        KC_GRV,          KC_1,            KC_2,            KC_3,            KC_4,            KC_5,            KC_6,            KC_7,            KC_8,            KC_9,            KC_0,            KC_MINS,
        KC_TAB,          KC_Q,            KC_W,            KC_E,            KC_R,            KC_T,            KC_Y,            KC_U,            KC_I,            KC_O,            KC_P,            KC_EQL,
        KC_CAPS,         KC_A,            KC_S,            KC_D,            KC_F,            KC_G,            KC_H,            KC_J,            KC_K,            KC_L,            KC_SCLN,         KC_QUOT,
        KC_LSFT,         KC_Z,            KC_X,            KC_C,            KC_V,            KC_B,            KC_N,            KC_M,            KC_COMM,         KC_DOT,          KC_SLSH,         KC_RSFT,
                                                           KC_ESC,          KC_SPC,          KC_LCTL,         KC_ENT,          KC_BSPC,         KC_DEL
    )
};

// Hardcoded defaults for Vial's dynamic features. Vial stores tap dances and
// combos in EEPROM only, and the EEPROM is invalidated on every flash (the
// Vial magic is derived from BUILD_ID, which is random per build). These
// tables are written back to the dynamic keymap after each reset so the
// keyboard is fully functional without loading a .vil file.

// {on_tap, on_hold, on_double_tap, on_tap_hold, tapping_term}
static const vial_tap_dance_entry_t default_tap_dances[] = {
    [0]  = {KC_LBRC,     KC_RBRC,       U_BRACKETS,      KC_NO, 200},
    [1]  = {S(KC_QUOT),  LCTL(KC_LALT), U_DOUBLE_QUOTE,  KC_NO, 200},
    [2]  = {KC_HOME,     KC_PGUP,       KC_NO,           KC_NO, 200},
    [3]  = {KC_END,      KC_PGDN,       KC_NO,           KC_NO, 200},
    [4]  = {S(KC_9),     S(KC_0),       U_PARENTHESES,   KC_NO, 200},
    [11] = {LGUI(KC_1),  LGUI(KC_6),    KC_NO,           KC_NO, 200},
    [12] = {LGUI(KC_2),  LGUI(KC_7),    KC_NO,           KC_NO, 200},
    [13] = {LGUI(KC_3),  LGUI(KC_8),    KC_NO,           KC_NO, 200},
    [14] = {LGUI(KC_4),  LGUI(KC_9),    KC_NO,           KC_NO, 200},
    [15] = {LGUI(KC_5),  LGUI(KC_0),    KC_NO,           KC_NO, 200},
    [16] = {LGUI(KC_Q),  KC_LGUI,       KC_NO,           KC_NO, 200},
};

// {{up to 4 input keycodes as on the base layer}, output}
static const vial_combo_entry_t default_combos[] = {
    {{LCTL_T(KC_F), LT(LAYER_GUI_NUM, KC_G), KC_NO, KC_NO}, U_SELECT_WORD},
    {{LT(LAYER_GUI_NUM, KC_R), KC_T, KC_NO, KC_NO}, U_SELECT_WORD_BACK},
    {{RALT_T(KC_V), KC_B, KC_NO, KC_NO}, U_JOIN_LN},
    {{KC_N, RALT_T(KC_M), KC_NO, KC_NO}, KC_0},
    {{LT(LAYER_GUI_NAV, KC_H), RCTL_T(KC_J), KC_NO, KC_NO}, KC_MINS},
    {{KC_Y, LT(LAYER_GUI_NAV, KC_U), KC_NO, KC_NO}, KC_EQL},
    {{LT(LAYER_GUI_NUM, KC_R), LCTL_T(KC_F), KC_NO, KC_NO}, KC_GRV},
    {{LT(LAYER_GUI_NAV, KC_U), RCTL_T(KC_J), KC_NO, KC_NO}, KC_SCLN},
    {{LT(LAYER_GUI_NUM, KC_W), LALT_T(KC_S), KC_NO, KC_NO}, S(KC_9)},
    {{LT(LAYER_GUI_NUM, KC_E), LSFT_T(KC_D), KC_NO, KC_NO}, S(KC_0)},
    {{LT(LAYER_GUI_NAV, KC_I), RSFT_T(KC_K), KC_NO, KC_NO}, KC_LBRC},
    {{LT(LAYER_GUI_NAV, KC_O), LALT_T(KC_L), KC_NO, KC_NO}, KC_RBRC},
    {{LT(1, KC_SPC), LT(3, KC_TAB), KC_NO, KC_NO}, KC_ENT},
    {{LT(5, KC_ESC), LT(1, KC_SPC), KC_NO, KC_NO}, KC_BSPC},
    {{LT(LAYER_GUI_NUM, KC_W), LT(LAYER_GUI_NUM, KC_E), LT(LAYER_GUI_NUM, KC_R), KC_NO}, U_SRCHSEL},
    {{KC_X, LSFT_T(KC_C), RALT_T(KC_V), KC_NO}, U_USERNAME},
    {{LT(LAYER_GUI_NAV, KC_U), LT(LAYER_GUI_NAV, KC_I), LT(LAYER_GUI_NAV, KC_O), KC_NO}, U_AND_OPERATOR},
    {{RALT_T(KC_M), RSFT_T(KC_COMM), KC_DOT, KC_NO}, U_ARROW},
    {{KC_N, RALT_T(KC_M), RSFT_T(KC_COMM), KC_NO}, U_NOT_EQUAL},
    {{LT(LAYER_GUI_NAV, KC_H), RCTL_T(KC_J), RSFT_T(KC_K), KC_NO}, U_DOUBLE_MINUS},
    {{KC_Y, LT(LAYER_GUI_NAV, KC_U), LT(LAYER_GUI_NAV, KC_I), KC_NO}, U_EQUAL},
    {{LALT_T(KC_S), KC_X, KC_NO, KC_NO}, U_UP_DIRECTORY},
    {{LALT_T(KC_L), KC_DOT, KC_NO, KC_NO}, U_THREE_DOTS},
    {{LGUI_T(KC_A), KC_Z, KC_NO, KC_NO}, QK_LAYER_LOCK},
    {{RGUI_T(KC_SCLN), KC_SLSH, KC_NO, KC_NO}, U_DOUBLE_SLASH},
    {{LSFT_T(KC_D), LSFT_T(KC_C), KC_NO, KC_NO}, OSM(MOD_LSFT)},
    {{LCTL_T(KC_F), RALT_T(KC_V), KC_NO, KC_NO}, OSM(MOD_RALT)},
    {{RCTL_T(KC_J), RALT_T(KC_M), KC_NO, KC_NO}, OSM(MOD_RALT)},
    {{RSFT_T(KC_K), RSFT_T(KC_COMM), KC_NO, KC_NO}, OSM(MOD_RSFT)},
    {{LT(LAYER_GUI_NUM, KC_W), LALT_T(KC_S), LT(LAYER_GUI_NUM, KC_E), LSFT_T(KC_D)}, U_PARENTHESES},
    {{LT(LAYER_GUI_NAV, KC_I), RSFT_T(KC_K), LT(LAYER_GUI_NAV, KC_O), LALT_T(KC_L)}, U_BRACKETS},
    {{LT(4, KC_ENT), LT(2, KC_BSPC), KC_NO, KC_NO}, QK_ALT_REPEAT_KEY},
    {{LT(2, KC_BSPC), LT(6, KC_DEL), KC_NO, KC_NO}, QK_REPEAT_KEY},
    {{KC_T, LT(LAYER_GUI_NUM, KC_G), KC_NO, KC_NO}, S(KC_GRV)},
    {{KC_Y, LT(LAYER_GUI_NAV, KC_H), KC_NO, KC_NO}, S(KC_SCLN)},
    {{KC_Q, LGUI_T(KC_A), KC_NO, KC_NO}, U_DOUBLE_BACKTICK},
    {{KC_P, RGUI_T(KC_SCLN), KC_NO, KC_NO}, KC_QUOT},
    {{LT(LAYER_GUI_NUM, KC_G), KC_B, KC_NO, KC_NO}, S(KC_LBRC)},
    {{LT(LAYER_GUI_NAV, KC_H), KC_N, KC_NO, KC_NO}, S(KC_RBRC)},
    {{LT(LAYER_GUI_NUM, KC_G), KC_B, LT(LAYER_GUI_NAV, KC_H), KC_N}, U_BRACES},
    {{LSFT_T(KC_C), RALT_T(KC_V), KC_B, KC_NO}, U_LOWER_THAN_OR_EQUAL},
    {{LT(LAYER_GUI_NUM, KC_E), LT(LAYER_GUI_NUM, KC_R), KC_T, KC_NO}, U_LEFT_SHIFT},
    {{OSM(MOD_LSFT), OSM(MOD_RALT), KC_NO, KC_NO}, OSM(MOD_RSFT | MOD_RALT)},
    {{RCTL_T(KC_J), RALT_T(KC_M), RSFT_T(KC_K), RSFT_T(KC_COMM)}, OSM(MOD_RSFT | MOD_RALT)},
    {{KC_DOT, KC_SLSH, KC_NO, KC_NO}, U_CURRENT_DIRECTORY},
    {{LT(5, KC_ESC), LT(6, KC_DEL), KC_NO, KC_NO}, MO(LAYER_ADJUST)},
    {{LSFT_T(KC_D), LCTL_T(KC_F), LT(LAYER_GUI_NUM, KC_G), KC_NO}, U_SELECT_LINE},
    {{KC_ESC, KC_DEL, KC_NO, KC_NO}, TG(LAYER_GAME)},
};

static void write_vial_default_tap_dances(void) {
    for (size_t i = 0; i < ARRAY_SIZE(default_tap_dances); ++i) {
        const vial_tap_dance_entry_t *entry = &default_tap_dances[i];
        if (entry->on_tap == KC_NO && entry->on_hold == KC_NO && entry->on_double_tap == KC_NO && entry->on_tap_hold == KC_NO) {
            continue;
        }
        dynamic_keymap_set_tap_dance(i, entry);
    }
}

static void write_vial_default_combos(void) {
    for (size_t i = 0; i < ARRAY_SIZE(default_combos); ++i) {
        dynamic_keymap_set_combo(i, &default_combos[i]);
    }
}

// Settings that qmk_settings_reset() does not restore to the wanted values.
// The rest (tapping term, combo term, oneshot, ...) come from config.h.
static void write_qmk_settings_defaults(void) {
    const uint8_t  enabled        = 1;
    const uint16_t quick_tap_term = 0;
    const uint16_t flow_tap_term  = 10;
    const uint32_t magic          = 1 << 7; // NKRO

    qmk_settings_set(22, &enabled, sizeof(enabled));               // permissive hold
    qmk_settings_set(26, &enabled, sizeof(enabled));               // chordal hold
    qmk_settings_set(25, &quick_tap_term, sizeof(quick_tap_term));
    qmk_settings_set(27, &flow_tap_term, sizeof(flow_tap_term));
    qmk_settings_set(21, &magic, sizeof(magic));
}

static bool vial_eeprom_was_reset = false;

// Runs at the start of via_init(), before the EEPROM validity check: when the
// magic is stale (every new build), via_init() resets the dynamic keymap, so
// our defaults must be written back afterwards (see keyboard_post_init_user).
void via_init_kb(void) {
    if (!via_eeprom_is_valid()) {
        vial_eeprom_was_reset = true;
    }
}

static void restore_vial_defaults(void) {
    write_vial_default_tap_dances();
    write_vial_default_combos();
    write_qmk_settings_defaults();
    // Reload Vial's RAM caches (combos, key overrides, ...) from EEPROM.
    vial_init();
}

// Alt Repeat Key: make hjkl repeat
// themselves so alternating navigation does not produce magic alternates.
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    switch (get_tap_keycode(keycode)) {
        case KC_H:
        case KC_J:
        case KC_K:
        case KC_L:
            if (mods == 0) {
                return get_tap_keycode(keycode);
            }
            break;
    }
    return KC_TRNS;
}

// Combos are defined with base layer keycodes, except on the game layer where
// grave+minus toggles back to the base layer.
uint8_t combo_ref_from_layer(uint8_t layer) {
    return layer == LAYER_GAME ? LAYER_GAME : COMBO_ONLY_FROM_LAYER;
}

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_LR(
        '*', '*', '*', '*', '*', '*',  '*', '*', '*', '*', '*', '*',
        '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
        '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
        '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
                       '*', '*', '*',  '*', '*', '*'
    );

typedef union {
    uint32_t raw;
    struct {
        // Set by eeconfig_init_user(): distinguishes initialized defaults
        // from a zeroed user datablock (raw == 0 must read as uninitialized).
        bool initialized : 1;
        bool eurkey_fr : 1;
        bool punctuation_mod: 1;
        bool quopostrokey : 1;
    };
} user_config_t;

user_config_t user_config;

// EurKEY is QWERTY-based: scancodes map straight to their legends.
bool is_alpha(const uint16_t keycode) {
    return KC_A <= keycode && keycode <= KC_Z;
}

void clear_all_mods(void) {
    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();
}

layer_state_t get_current_layer(void) {
    return get_highest_layer(layer_state);
}

bool is_layer(layer_state_t state) {
    return get_current_layer() == state;
}

bool is_nav_layer(void) {
    return is_layer(LAYER_NAV);
}

bool on_left_hand(keypos_t pos) {
#ifdef SPLIT_KEYBOARD
    return pos.row < MATRIX_ROWS / 2;
#else
    return (MATRIX_COLS > MATRIX_ROWS) ? pos.col < MATRIX_COLS / 2 : pos.row < MATRIX_ROWS / 2;
#endif
}

bool is_flow_tap_key(uint16_t keycode) {
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return false; // Disable Flow Tap on hotkeys.
    }

    const uint16_t tap_keycode = get_tap_keycode(keycode);

    if (is_alpha(tap_keycode)) {
        return true;
    }

    switch (tap_keycode) {
        // case KC_SPC:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
            return true;
    }

    return false;
}

uint16_t get_flow_tap_term(
    uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {

    const uint16_t tap_keycode = get_tap_keycode(keycode);

    // home-row-mods
    switch (tap_keycode) {
        case KC_A:
        case KC_S:
        case KC_D:
        case KC_F:
        case KC_J:
        case KC_K:
        case KC_L:
        case KC_SCLN:
            return 0;  // Disable filter for these keys.
    }

    // AltGr producing accented characters
    switch (prev_keycode) {
        case RALT_T(KC_X):
        case RALT_T(KC_V):
            switch (tap_keycode) {
                case KC_U: // ù
                case KC_I: // î
                case KC_O: // ô
                case KC_P: // ü
                case KC_J: // û
                case KC_K: // ï
                    return 0;
            }
            break;
        case RALT_T(KC_DOT):
        case RALT_T(KC_M):
            switch (tap_keycode) {
                case KC_A: // à
                case KC_Q: // â
                case KC_W: // ë
                case KC_E: // é
                case KC_R: // ê
                case KC_D: // è
                case KC_Z: // à (EurKEY native)
                case KC_C: // ç (EurKEY native)
                    return 0;
            }
            break;
        case LSFT_T(KC_C):
            if (tap_keycode == KC_V || tap_keycode == KC_X) {
                return 0;
            }
            break;
        case RSFT_T(KC_COMM):
            if (tap_keycode == KC_M || tap_keycode == KC_DOT) {
                return 0;
            }
            break;
    }

    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        return QS.flow_tap_term;
    }

    return 0;  // Disable Tap Flow.
}

#ifdef CHORDAL_HOLD
bool get_chordal_hold(
    uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
    uint16_t other_keycode, keyrecord_t* other_record) {

    // LGui+L screen lock protection: force LGUI_T(KC_A) to tap when L is pressed
    if (tap_hold_keycode == LGUI_T(KC_A) && get_tap_keycode(other_keycode) == KC_L) {
        return false;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}
#endif


bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_MOD_TAP(keycode)) {
        const uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(keycode));
        if (mod & MOD_LGUI) {
            return false;
        }
    }

    return QS_tapping_permissive_hold;
}

bool caps_word_press_user(uint16_t keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    if (is_alpha(keycode) || keycode == KC_MINS) {
        add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
        return true;
    }

    switch (keycode) {
        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

bool process_tap_or_hold_press_key(keyrecord_t* record, const char *tap_string, uint16_t hold_keycode) {
    if (record->tap.count == 0) {  // Key is being held.
        if (record->event.pressed) {
            register_code16(hold_keycode);
        } else {
            unregister_code16(hold_keycode);
        }
    } else if (record->event.pressed) {
        SEND_STRING(tap_string);
    }
    return false;
}

#define U_UNDO  LT(0, KC_Z)
#define U_CUT   LT(0, KC_X)
#define U_COPY  LT(0, KC_C)
#define U_PASTE LT(0, KC_V)
#define U_REDO  LT(0, KC_B)

bool process_clipboard_shortcuts(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case U_UNDO:
            return process_tap_or_hold_press_key(record, SS_LCTL("z"), KC_LGUI);
        case U_CUT:
            return process_tap_or_hold_press_key(record, SS_LCTL("x"), KC_RALT);
        case U_COPY:
            return process_tap_or_hold_press_key(record, SS_LCTL("c"), KC_LSFT);
        case U_PASTE:
            return process_tap_or_hold_press_key(record, SS_LCTL("v"), KC_RALT);
        case U_REDO:
            return process_tap_or_hold_press_key(record, SS_LCTL(SS_LSFT("z")), KC_RCTL);
    }
    return true;
}

bool process_custom_tap_holds(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0, KC_MINS):
            return process_tap_or_hold_press_key(record, "_", KC_RSFT);
        case LT(0, KC_DOT):
            return process_tap_or_hold_press_key(record, ".", KC_COMM);
    }
    return true;
}

// https://getreuer.info/posts/keyboards/macros3/index.html#shift-backspace-delete
bool process_shift_backspace_delete(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_LAYER_TAP(keycode)) {
        if (record->tap.count == 0) { return true; }
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count == 0) { return true; }
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }

    if (keycode != KC_BSPC) {
        return true;
    }

    static uint16_t registered_key = KC_NO;

    if (record->event.pressed) { // On key press.
        const uint8_t mods       = get_mods();
        uint8_t       shift_mods = (mods | get_oneshot_mods()) & MOD_MASK_SHIFT;

        if (shift_mods) { // At least one shift key is held.
            // If one shift is held, clear it from the mods.
            // But if both shifts are held, leave as is to send Shift + Del.
            if (shift_mods != MOD_MASK_SHIFT) {
                del_oneshot_mods(MOD_MASK_SHIFT);
                unregister_mods(MOD_MASK_SHIFT);
            }

            registered_key = KC_DEL;
            register_code(registered_key);
            set_mods(mods);
            return false;
        }
    } else { // On key release.
        if (registered_key != KC_NO) {
            unregister_code(registered_key);
            registered_key = KC_NO;
            return false;
        }
    }

    return true;
}

// Join lines like Vim's `J` command.
// https://getreuer.info/posts/keyboards/macros/index.html
bool process_joinln(uint16_t keycode, keyrecord_t *record, uint16_t joinln_keycode) {
    if (keycode != joinln_keycode || !record->event.pressed) {
        return true;
    }

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if (all_mods & MOD_MASK_SHIFT || all_mods & MOD_MASK_CTRL) {
        clear_all_mods();

        // Split current line
        SEND_STRING(SS_LCTL(SS_TAP(X_RGHT) SS_TAP(X_LEFT) SS_TAP(X_RGHT)) SS_TAP(X_ENTER));

        set_mods(mods);
    } else {
        // Join current line with next line
        SEND_STRING(
            // Select any trailing spaces.
            SS_TAP(X_END) SS_LSFT(SS_TAP(X_END))
            // Delete any trailing spaces.
            SS_TAP(X_SPC) SS_TAP(X_BSPC)
            // Go to start of next line.
            SS_TAP(X_RGHT)
            // Go to first word if there is any indentation.
            SS_TAP(X_HOME)
            // Select indentation (if any) and end-of-line.
            SS_LSFT(SS_TAP(X_HOME) SS_TAP(X_LEFT))
            // Replace selection with a space.
            SS_TAP(X_SPC));
    }

    return false;
}

// User select word keycodes because of currently unsupported keycodes in GUI.
bool process_select_word_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == U_SELECT_WORD) {
        if (record->event.pressed) {
            const bool shifted = MOD_MASK_SHIFT & (get_mods() | get_weak_mods() | get_oneshot_mods());
            select_word_register(shifted ? 'L' : 'W');
        } else {
            select_word_unregister();
        }
    } else  if (keycode == U_SELECT_WORD_BACK) {
        if (record->event.pressed) {
            select_word_register('B');
        } else {
            select_word_unregister();
        }
    } else  if (keycode == U_SELECT_LINE) {
        if (record->event.pressed) {
            select_word_register('L');
        } else {
            select_word_unregister();
        }
    }
    return true;
}

// Select the current line and replace it with the login, then move to the
// password field and submit. Replaces the Vial dynamic macros M0/M1.
bool process_login_macros(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case U_LOGIN_ADMIN:
            SEND_STRING(SS_TAP(X_END) SS_LSFT(SS_TAP(X_HOME)) "admin\tadmin" SS_TAP(X_ENTER));
            return false;
        case U_LOGIN_DEMO:
            SEND_STRING(SS_TAP(X_END) SS_LSFT(SS_TAP(X_HOME)) "demo\tdemo" SS_TAP(X_ENTER));
            return false;
    }

    return true;
}

struct user_macro {
    const enum user_keycode keycode;
    const char             *string;
    const char             *shifted_string;
    const char             *controlled_string;
    const char             *shifted_controlled_string;
};

const char CURRENT_DIRECTORY[] PROGMEM     = "./";
const char UP_DIRECTORY[] PROGMEM          = "../";
const char DOT[] PROGMEM                   = ".";
const char THREE_DOTS[] PROGMEM            = "...";
const char DOUBLE_COLON[] PROGMEM          = "::";
const char EQUAL[] PROGMEM                 = "==";
const char STRICT_EQUAL[] PROGMEM          = "===";
const char NOT_EQUAL[] PROGMEM             = "!=";
const char STRICT_NOT_EQUAL[] PROGMEM      = "!==";
const char LOWER_THAN_OR_EQUAL[] PROGMEM   = "<=";
const char GREATER_THAN_OR_EQUAL[] PROGMEM = ">=";
const char ARROW[] PROGMEM                 = "->";
const char DOUBLE_ARROW[] PROGMEM          = "=>";
const char LEFT_ARROW[] PROGMEM            = "<-";
const char DOUBLE_LEFT_ARROW[] PROGMEM     = "<==";
const char AND_OPERATOR[] PROGMEM          = "&&";
const char OR_OPERATOR[] PROGMEM           = "||";
const char DOUBLE_MINUS[] PROGMEM          = "--";
const char DOUBLE_PLUS[] PROGMEM           = "++";
const char DOUBLE_SLASH[] PROGMEM          = "//";
const char DOUBLE_QUESTION[] PROGMEM       = "??";
const char LEFT_SHIFT[] PROGMEM            = "<<";
const char RIGHT_SHIFT[] PROGMEM           = ">>";
const char DOUBLE_QUOTE[] PROGMEM          = "\"\"" SS_TAP(X_LEFT);
const char SINGLE_QUOTE[] PROGMEM          = "''" SS_TAP(X_LEFT);
const char BACKTICK[] PROGMEM              = "``" SS_TAP(X_LEFT);
const char FSTRING[] PROGMEM               = "f\"\"" SS_TAP(X_LEFT);
const char DIAMOND[] PROGMEM               = "<>";
const char ADD_ASSIGN[] PROGMEM            = "+=";
const char SUB_ASSIGN[] PROGMEM            = "-=";
const char MUL_ASSIGN[] PROGMEM            = "*=";
const char DIV_ASSIGN[] PROGMEM            = "/=";
const char MOD_ASSIGN[] PROGMEM            = "%=";
const char AND_ASSIGN[] PROGMEM            = "&=";
const char OR_ASSIGN[] PROGMEM             = "|=";
const char XOR_ASSIGN[] PROGMEM            = "^=";
const char DOUBLE_UNDERSCORE[] PROGMEM     = "__";
const char IN_UNDERSCORES[] PROGMEM        = SS_LCTL(SS_TAP(X_LEFT)) "__" SS_LCTL(SS_TAP(X_RGHT)) "__";
const char DOUBLE_BACKTICK[] PROGMEM       = "``" SS_TAP(X_LEFT);
const char TRIPLE_BACKTICK[] PROGMEM       = "```";
const char CODE_BLOCK[] PROGMEM            = "```" SS_LSFT(SS_TAP(X_ENT)) "```" SS_TAP(X_UP);
const char ELEMENT[] PROGMEM               = "<>" SS_TAP(X_LEFT);
const char ELEMENT_SELF_CLOSED[] PROGMEM   = "</>" SS_TAP(X_LEFT) SS_TAP(X_LEFT);
const char ELEMENT_WITH_CLOSE[] PROGMEM    = "<></>" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT);
const char SRCHSEL[] PROGMEM               = SS_LCTL("c") SS_TAP_CODE_DELAY SS_LCTL("t") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER);
const char PARENTHESES[] PROGMEM           = "()" SS_TAP(X_LEFT);
const char BRACKETS[] PROGMEM              = "[]" SS_TAP(X_LEFT);
const char BRACES[] PROGMEM                = "{}" SS_TAP(X_LEFT);

// keycode, normal, shift, control, control+shift
const struct user_macro USER_MACROS[] PROGMEM = {
    {U_CURRENT_DIRECTORY, CURRENT_DIRECTORY, UP_DIRECTORY, THREE_DOTS, DOUBLE_COLON},
    {U_UP_DIRECTORY, UP_DIRECTORY, CURRENT_DIRECTORY, THREE_DOTS, DOUBLE_COLON},
    {U_DOT, DOT, THREE_DOTS, NULL, NULL},
    {U_THREE_DOTS, THREE_DOTS, DOUBLE_COLON, CURRENT_DIRECTORY, UP_DIRECTORY},
    {U_DOUBLE_COLON, DOUBLE_COLON, THREE_DOTS, CURRENT_DIRECTORY, UP_DIRECTORY},
    {U_EQUAL, EQUAL, DOUBLE_PLUS, STRICT_EQUAL, ADD_ASSIGN},
    {U_STRICT_EQUAL, STRICT_EQUAL, EQUAL, NULL, NULL},
    {U_NOT_EQUAL, NOT_EQUAL, STRICT_NOT_EQUAL, STRICT_NOT_EQUAL, NULL},
    {U_STRICT_NOT_EQUAL, STRICT_NOT_EQUAL, NOT_EQUAL, NULL, NULL},
    {U_LOWER_THAN_OR_EQUAL, LOWER_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, NULL, NULL},
    {U_GREATER_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, LOWER_THAN_OR_EQUAL, NULL, NULL},
    {U_ARROW, ARROW, DOUBLE_ARROW, LEFT_ARROW, DOUBLE_LEFT_ARROW},
    {U_DOUBLE_ARROW, DOUBLE_ARROW, ARROW, DOUBLE_LEFT_ARROW, LEFT_ARROW},
    {U_AND_OPERATOR, AND_OPERATOR, OR_OPERATOR, DOUBLE_QUESTION, NULL},
    {U_OR_OPERATOR, OR_OPERATOR, AND_OPERATOR, DOUBLE_QUESTION, NULL},
    {U_DOUBLE_MINUS, DOUBLE_MINUS, DOUBLE_UNDERSCORE, IN_UNDERSCORES, SUB_ASSIGN},
    {U_DOUBLE_UNDERSCORE, DOUBLE_UNDERSCORE, IN_UNDERSCORES, NULL, NULL},
    {U_DOUBLE_PLUS, DOUBLE_PLUS, DOUBLE_MINUS, STRICT_EQUAL, ADD_ASSIGN},
    {U_DOUBLE_SLASH, DOUBLE_SLASH, DOUBLE_QUESTION, NULL, NULL},
    {U_DOUBLE_QUESTION, DOUBLE_QUESTION, DOUBLE_SLASH, NULL, NULL},
    {U_LEFT_SHIFT, LEFT_SHIFT, RIGHT_SHIFT, NULL, NULL},
    {U_RIGHT_SHIFT, RIGHT_SHIFT, LEFT_SHIFT, NULL, NULL},
    {U_DOUBLE_QUOTE, DOUBLE_QUOTE, SINGLE_QUOTE, BACKTICK, FSTRING},
    {U_DOUBLE_BACKTICK, DOUBLE_BACKTICK, TRIPLE_BACKTICK, CODE_BLOCK, NULL},
    {U_ELEMENT, ELEMENT, ELEMENT_SELF_CLOSED, ELEMENT_WITH_CLOSE, NULL},
    {U_ADD_ASSIGN, ADD_ASSIGN, MUL_ASSIGN, AND_ASSIGN, XOR_ASSIGN}, // += *= &= ^=
    {U_SUB_ASSIGN, SUB_ASSIGN, DIV_ASSIGN, OR_ASSIGN, MOD_ASSIGN}, // -= /= |= %=
    {U_SRCHSEL, SRCHSEL, NULL, NULL, NULL},
    {U_PARENTHESES, PARENTHESES, BRACES, BRACKETS, NULL},
    {U_BRACKETS, BRACKETS, BRACES, PARENTHESES, NULL},
    {U_BRACES, BRACES, BRACKETS, PARENTHESES, NULL},
    {U_USERNAME, "philong", "Phi-Long", "philong.do@gmail.com", "p.do@axelor.com"},
};

const size_t NUM_USER_MACROS = sizeof(USER_MACROS) / sizeof(*USER_MACROS);

bool process_macros_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    const uint16_t tap_keycode = get_tap_keycode(keycode);

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    const bool is_shifted    = all_mods & MOD_MASK_SHIFT;
    const bool is_controlled = all_mods & MOD_MASK_CTRL;

    for (size_t i = 0; i < NUM_USER_MACROS; ++i) {
        const struct user_macro macro = USER_MACROS[i];
        if (macro.keycode != tap_keycode) {
            continue;
        }
        if (is_shifted && is_controlled && macro.shifted_controlled_string) {
            clear_all_mods();
            SEND_STRING(macro.shifted_controlled_string);
            set_mods(mods);
        } else if (is_controlled && macro.controlled_string) {
            clear_all_mods();
            SEND_STRING(macro.controlled_string);
            set_mods(mods);
        } else if (is_shifted && macro.shifted_string) {
            clear_all_mods();
            SEND_STRING(macro.shifted_string);
            set_mods(mods);
        } else {
            clear_all_mods();
            SEND_STRING(macro.string);
            set_mods(mods);
        }
        return false;
    }

    return true;
}

bool process_caps_word_escape(uint16_t keycode, keyrecord_t *record) {
    if ((IS_QK_LAYER_TAP(keycode) || IS_QK_MOD_TAP(keycode)) && record->tap.count == 0) {
        return true; // Key is being held.
    }

    if (record->event.pressed && get_tap_keycode(keycode) == KC_ESCAPE && is_caps_word_on()) {
        caps_word_off();
        return false;
    }

    return true;
}

bool process_layer_lock_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t current_layer = get_current_layer();

    if (keycode == QK_LAYER_LOCK) {
        // Alt repeat on base layer
        if (current_layer == LAYER_BASE) {
            return process_repeat_key(QK_ALT_REPEAT_KEY, record);
        }

        // Layer overrides
        if (record->event.pressed) {
            switch (current_layer) {
                case LAYER_NUM:
                    layer_off(LAYER_NUM);
                    layer_on(LAYER_NAV_NUM);
                    break;
            }
        }
    }

    return true;
}

// Keycode sent instead of `keycode` while `layer` is the highest layer, or
// KC_NO when there is no override.
static uint16_t num_layer_override_keycode(uint8_t layer, uint16_t keycode) {
    if (layer == LAYER_NUM) {
        switch (keycode) {
            case OSM(MOD_RALT):  return KC_0;           // Zero
            case OSM(MOD_RSFT):  return KC_COMM;        // Comma
            case U_THREE_DOTS:   return KC_DOT;         // Dot
            case U_DOUBLE_SLASH: return KC_KP_PLUS;     // Plus
            case KC_LBRC:        return KC_KP_SLASH;    // Slash
            case KC_RBRC:        return KC_KP_ASTERISK; // Asterisk
            // case KC_QUOT:        return KC_KP_MINUS;    // Minus
        }
    } else if (layer == LAYER_SYM2) {
        switch (keycode) {
            case U_UP_DIRECTORY:     return KC_KP_0;        // Zero
            case OSM(MOD_LSFT):      return KC_KP_COMMA;    // Comma
            case OSM(MOD_RALT):      return KC_KP_DOT;      // Dot
            case U_SELECT_WORD:      return KC_KP_PLUS;     // Plus
            case S(KC_0):            return KC_KP_SLASH;    // Slash
            case KC_GRV:             return KC_KP_ASTERISK; // Asterisk
            case U_SELECT_WORD_BACK: return KC_KP_MINUS;    // Minus
            case U_JOIN_LN:          return KC_KP_ENTER;    // Enter
        }
    }
    return KC_NO;
}

bool process_num_layer_override(uint16_t keycode, keyrecord_t *record) {
    // Overrides registered on press: their release must be matched even after
    // the layer was left (e.g. layer key released first), otherwise the
    // override keycode gets stuck.
    static uint16_t held_inputs[4];
    static uint16_t held_outputs[4];

    if (!record->event.pressed) {
        for (size_t i = 0; i < ARRAY_SIZE(held_inputs); ++i) {
            if (held_inputs[i] == keycode) {
                unregister_code16(held_outputs[i]);
                held_inputs[i] = KC_NO;
                return false;
            }
        }
        return true;
    }

    const uint8_t current_layer = get_highest_layer(layer_state);

    // Triple zero
    if (current_layer == LAYER_NUM && keycode == KC_SCLN) {
        SEND_STRING(SS_TAP(X_0) SS_TAP(X_0) SS_TAP(X_0));
        return false;
    }
    if (current_layer == LAYER_SYM2 && keycode == S(KC_9)) {
        SEND_STRING(SS_TAP(X_KP_0) SS_TAP(X_KP_0) SS_TAP(X_KP_0));
        return false;
    }

    const uint16_t override = num_layer_override_keycode(current_layer, keycode);
    if (override == KC_NO) {
        return true;
    }

    register_code16(override);
    for (size_t i = 0; i < ARRAY_SIZE(held_inputs); ++i) {
        if (held_inputs[i] == KC_NO) {
            held_inputs[i]  = keycode;
            held_outputs[i] = override;
            break;
        }
    }
    return false;
}

// Allow mod after releasing nav layer while not releasing a nav key.
bool process_nav_override(uint16_t keycode, keyrecord_t *record) {
    static bool right_pressed = false;
    static bool down_pressed  = false;
    static bool left_pressed  = false;

    static bool ctl_down = false;
    static bool sft_down = false;
    static bool alt_down = false;

    bool is_nav  = is_nav_layer();
    bool pressed = record->event.pressed;

    if (is_nav || !pressed) {
        switch (keycode) {
            case KC_RIGHT:
                right_pressed = pressed;
                if (!pressed && ctl_down) {
                    unregister_code16(KC_LCTL);
                    ctl_down = false;
                }
                break;
            case KC_DOWN:
                down_pressed = pressed;
                if (!pressed && sft_down) {
                    unregister_code16(KC_LSFT);
                    sft_down = false;
                }
                break;
            case KC_LEFT:
                left_pressed = pressed;
                if (!pressed && alt_down) {
                    unregister_code16(KC_LALT);
                    alt_down = false;
                }
                break;
        }
        return true;
    }

    if (!is_nav) {
        if (right_pressed) {
            unregister_code16(KC_RIGHT);
            register_code16(KC_LCTL);
            right_pressed = false;
            ctl_down      = true;
        }

        if (down_pressed) {
            unregister_code16(KC_DOWN);
            register_code16(KC_LSFT);
            down_pressed = false;
            sft_down     = true;
        }

        if (left_pressed) {
            unregister_code16(KC_LEFT);
            register_code16(KC_LALT);
            left_pressed = false;
            alt_down     = true;
        }
    }

    return true;
}

// Convert 8-bit mods to the 5-bit format used in keycodes. This is lossy: if
// left and right handed mods were mixed, they all become right handed.
uint8_t get_keycode_mods(uint8_t mods) {
    return ((mods & 0xf0) ? /* set right hand bit */ 0x10 : 0)
           // Combine right and left hand mods.
           | (((mods >> 4) | mods) & 0xf);
}

// Combine basic keycode with mods.
uint16_t combine_keycode(uint16_t keycode, uint8_t mods) {
    return (get_keycode_mods(mods) << 8) | keycode;
}

bool process_punctuation_mod(uint16_t keycode, keyrecord_t *record, uint16_t toggle_keycode) {
    if (!record->event.pressed) {
        return true;
    }

    if (keycode == toggle_keycode) {
        user_config.punctuation_mod ^= 1;
        eeconfig_update_user(user_config.raw);
        return false;
    }

    if (!user_config.punctuation_mod) {
        return true;
    }

    uint16_t tap_keycode;

    if (IS_QK_LAYER_TAP(keycode)) {
        if (record->tap.count == 0) {
            return true;
        } // Key is being held.
        tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count == 0) {
            return true;
        } // Key is being held.
        tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else {
        tap_keycode = keycode;
    }

    static short comma_count = 0;
    static short scln_count = 0;
    static uint16_t last_keycode = KC_NO;
    static fast_timer_t timer = 0;

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if (!all_mods && (is_alpha(tap_keycode) || tap_keycode == KC_QUOT || tap_keycode == KC_SLSH)) {
        last_keycode = KC_NO;

        const bool shifted_ralted = (comma_count == 0 && scln_count == 2) || (comma_count == 1 && scln_count == 1);
        const bool shifted = (comma_count == 1 && scln_count == 0) || shifted_ralted;
        const bool ralted = (comma_count == 0 && scln_count == 1) || shifted_ralted;

        if ((!shifted && !ralted) || timer_elapsed_fast(timer) > ONESHOT_TIMEOUT) {
            comma_count = 0;
            scln_count = 0;
            return true;
        }

        char backspace_str[4];
        const size_t total = comma_count + scln_count;
        memset(backspace_str, '\b', total);
        backspace_str[total] = '\0';
        SEND_STRING(backspace_str);
        comma_count = 0;
        scln_count = 0;

        if (shifted) {
            set_oneshot_mods(get_oneshot_mods() | MOD_BIT(KC_LSFT));
        }

        if (ralted) {
            set_oneshot_mods(get_oneshot_mods() | MOD_BIT(KC_RALT));
        }

        return true;
    }

    if (all_mods) {
        tap_keycode = combine_keycode(tap_keycode, all_mods);
    }

    switch (tap_keycode) {
        case KC_COMM:
            timer = timer_read_fast();
            ++comma_count;

            // ,, -> ,,
            if (last_keycode == KC_COMM && comma_count == 2 && scln_count == 0) {
                last_keycode = KC_NO;
                comma_count = 0;
                scln_count = 0;
                tap_code(KC_COMMA);
                return false;
            }
            break;
        case KC_SCLN:
            timer = timer_read_fast();
            ++scln_count;
            break;
        default:
            if (comma_count > 0) {
                comma_count = 0;
            }
            if (scln_count > 0) {
                scln_count = 0;
            }
    }

    last_keycode = tap_keycode;

    return true;
}

// The two GUI layers are shared by several layer-tap keys; which GUI+modifier
// combination gets held as real mods depends on the trigger's tap keycode.
uint8_t gui_layer_mods(uint16_t tap_keycode) {
    switch (tap_keycode) {
        case KC_W:
        case KC_O:
            return MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI);
        case KC_E:
        case KC_I:
            return MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI);
        case KC_R:
        case KC_U:
            return MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI);
        case KC_G:
            return MOD_BIT(KC_LGUI);
        case KC_H:
            return MOD_BIT(KC_RGUI);
        default:
            return 0;
    }
}

bool process_gui_layers(uint16_t keycode, keyrecord_t *record) {
    if (!IS_QK_LAYER_TAP(keycode) || record->tap.count != 0) {
        return true;
    }

    const uint8_t layer = QK_LAYER_TAP_GET_LAYER(keycode);
    if (layer != LAYER_GUI_NUM && layer != LAYER_GUI_NAV) {
        return true;
    }

    const uint8_t mods = gui_layer_mods(QK_LAYER_TAP_GET_TAP_KEYCODE(keycode));
    if (mods == 0) {
        return true;
    }

    if (record->event.pressed) {
        register_mods(mods);
    } else {
        unregister_mods(mods);
    }

    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    if (keycode == LT(2, KC_BSPC)) {
        return true;
    }

    return QS_tapping_hold_on_other_key_press;
}

void send_char_shifted(char key) {
    SEND_STRING(SS_DOWN(X_LSFT));
    send_char(key);
    SEND_STRING(SS_UP(X_LSFT));
}

bool send_key_with_ralt(char key, char dead_ralt_key, uint8_t mods, bool shifted) {
    clear_all_mods();
    SEND_STRING(SS_DOWN(X_RALT));
    send_char(dead_ralt_key);
    SEND_STRING(SS_UP(X_RALT) SS_TAP_CODE_DELAY);
    if (shifted) {
        send_char_shifted(key);
    } else {
        send_char(key);
    }
    set_mods(mods);
    return false;
}

bool send_ralt_key(char key, uint8_t mods, bool shifted) {
    clear_all_mods();
    SEND_STRING(SS_DOWN(X_RALT));
    if (shifted) {
        send_char_shifted(key);
    } else {
        send_char(key);
    }
    SEND_STRING(SS_UP(X_RALT));
    set_mods(mods);
    return false;
}

// French accents by default on AltGr+letter. Each vowel carries its most-used
// French accent (E=é, A=à, I=î, O=ô, U=ù); the remaining accents sit on
// neighbors by frequency: è (2nd most frequent) on home-row D, then R=ê,
// W=ë, Q=â, J=û, K=ï, P=ü. Letters not listed (ç on C, ñ on N, á on X, …)
// fall through to EurKEY's native AltGr mapping. Most accents are direct
// EurKEY AltGr chords (capital on the AltGr+Shift level); circumflex only
// exists as the dead key AltGr+6.
bool process_eurkey_fr(uint16_t keycode, keyrecord_t *record, uint16_t toggle_keycode) {
    if (!record->event.pressed) {
        return true;
    }

    if (keycode == toggle_keycode) {
        user_config.eurkey_fr ^= 1;
        eeconfig_update_user(user_config.raw);
        return false;
    }

    if (!user_config.eurkey_fr) {
        return true;
    }

    uint16_t tap_keycode;

    if (IS_QK_LAYER_TAP(keycode)) {
        if (record->tap.count == 0) {
            return true;
        } // Key is being held.
        tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count == 0) {
            return true;
        } // Key is being held.
        tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else {
        tap_keycode = keycode;
    }

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();
    if ((all_mods & MOD_BIT(KC_RALT)) == 0) {
        return true;
    }
    const bool shifted = all_mods & MOD_MASK_SHIFT;

    switch (tap_keycode) {
        // aigu
        case KC_E:
            return send_ralt_key('g', mods, shifted);           // é
        // grave
        case KC_A:
            return send_ralt_key('z', mods, shifted);           // à
        case KC_D:
            return send_ralt_key('f', mods, shifted);           // è
        case KC_U:
            return send_ralt_key('h', mods, shifted);           // ù
        // circonflexe
        case KC_Q:
            return send_key_with_ralt('a', '6', mods, shifted); // â
        case KC_R:
            return send_key_with_ralt('e', '6', mods, shifted); // ê
        case KC_I:
            return send_key_with_ralt('i', '6', mods, shifted); // î
        case KC_O:
            return send_key_with_ralt('o', '6', mods, shifted); // ô
        case KC_J:
            return send_key_with_ralt('u', '6', mods, shifted); // û
        // tréma
        case KC_W:
            return send_ralt_key('e', mods, shifted);           // ë
        case KC_K:
            return send_ralt_key('i', mods, shifted);           // ï
        case KC_P:
            return send_ralt_key('u', mods, shifted);           // ü
        default:
            return true;
    }
}

#ifdef AUTOCORRECT_ENABLE
bool autocorrect_is_alpha(uint16_t keycode) {
    return is_alpha(keycode);
}
#endif

// https://getreuer.info/posts/keyboards/macros3/index.html#quopostrokey
// Types ' within a word, otherwise "" with the cursor placed in between.
bool process_quopostrokey(uint16_t keycode, keyrecord_t *record, uint16_t toggle_keycode) {
    static bool within_word = false;

    if (keycode == toggle_keycode) {
        if (record->event.pressed) {
            user_config.quopostrokey ^= 1;
            eeconfig_update_user(user_config.raw);
        }
        return false;
    }

    // When enabled, a tap on the base layer semicolon key (RGUI_T(KC_SCLN))
    // acts as the Quopostrokey; useful on 36-key builds without the quote
    // key. Only physical key presses are remapped: the U+J combo still
    // outputs a plain ';', which also keeps the punctuation mode prefix
    // reachable.
    if (keycode == RGUI_T(KC_SCLN) && record->tap.count > 0 && user_config.quopostrokey && IS_KEYEVENT(record->event) && is_layer(LAYER_BASE)) {
        keycode = U_QUOPOSTROKEY;
    }

    if (keycode == U_QUOPOSTROKEY) {
        static bool quot_registered = false;

        if (record->event.pressed) {
            const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();
            if (mods != 0) {
                register_code(KC_QUOT);
                quot_registered = true;
            } else if (within_word) {
                tap_code(KC_QUOT);
            } else {
                SEND_STRING("\"\"" SS_TAP(X_LEFT));
            }
        } else if (quot_registered) {
            unregister_code(KC_QUOT);
            quot_registered = false;
        }
        return false;
    }

    if (IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) {
        if (record->tap.count == 0) { // Key is being held.
            return true;
        }
    }

    within_word = is_alpha(get_tap_keycode(keycode));

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Runs first so it observes every key to track word boundaries.
    if (!process_quopostrokey(keycode, record, U_QUOPOSTROKEY_TOGG)) {
        return false;
    }
    if (!process_num_layer_override(keycode, record)) {
        return false;
    }
    // Punctuation mode must run before the EurKEY French processing: it
    // turns a `;`/`,` prefix into oneshot Shift/AltGr mods, which
    // process_eurkey_fr() then picks up to produce the French accents
    // (e.g. `;` then `a` -> à, not ä).
    if (!process_punctuation_mod(keycode, record, U_PUNCTUATION_MOD_TOGG)) {
        return false;
    }
    if (!process_eurkey_fr(keycode, record, U_EURKEY_FR_TOGG)) {
        return false;
    }
    if (!process_shift_backspace_delete(keycode, record)) {
        return false;
    }
    if (!process_select_word_user(keycode, record)) {
        return false;
    }
    if (!process_joinln(keycode, record, U_JOIN_LN)) {
        return false;
    }
    if (!process_login_macros(keycode, record)) {
        return false;
    }
    if (!process_macros_user(keycode, record)) {
        return false;
    }
    if (!process_caps_word_escape(keycode, record)) {
        return false;
    }
    if (!process_clipboard_shortcuts(keycode, record)) {
        return false;
    }
    if (!process_custom_tap_holds(keycode, record)) {
        return false;
    }
    if (!process_layer_lock_user(keycode, record)) {
        return false;
    }
    if (!process_nav_override(keycode, record)) {
        return false;
    }
    if (!process_gui_layers(keycode, record)) {
        return false;
    }

    return true;
}

// Keyboard boots up.
void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();

    if (!user_config.initialized) {
        eeconfig_init_user();
    }

    if (vial_eeprom_was_reset) {
        restore_vial_defaults();
    }
}

// EEPROM is getting reset.
void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.initialized = true;
    user_config.eurkey_fr = true;
    user_config.punctuation_mod = true;
    user_config.quopostrokey = false;

#ifdef UNICODE_ENABLE
    set_unicode_input_mode(UNICODE_MODE_LINUX);
#endif

#ifdef AUTOCORRECT_ENABLE
    autocorrect_enable();
#endif

    eeconfig_update_user(user_config.raw);
}
