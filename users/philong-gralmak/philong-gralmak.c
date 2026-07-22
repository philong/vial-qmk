// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

// Shared philong-gralmak keymap: Gralmak variant of users/philong-eurkey.
// The host still runs the QWERTY-based EurKEY layout; the keymap rearranges
// the letters to Gralmak (https://github.com/DreymaR/Gralmak), including its
// quote/semicolon swap.

#include "../philong/philong_core.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [LAYER_BASE] = LAYOUT_LR(
        TD(16),          TD(11),          TD(12),          TD(13),          TD(14),          TD(15),          KC_LEFT,         KC_DOWN,         KC_UP,           KC_RGHT,         TD(2),           TD(3),
        TD(4),           KC_B,            LT(LAYER_GUI_NUM, KC_L), LT(LAYER_GUI_NUM, KC_D), LT(LAYER_GUI_NUM, KC_W), KC_Q, KC_J,     LT(LAYER_GUI_NAV, KC_F), LT(LAYER_GUI_NAV, KC_O), LT(LAYER_GUI_NAV, KC_U), KC_QUOT, TD(0),
        TD(1),           LGUI_T(KC_N),    LALT_T(KC_R),    LSFT_T(KC_T),    LCTL_T(KC_S),    LT(LAYER_GUI_NUM, KC_G), LT(LAYER_GUI_NAV, KC_Y), RCTL_T(KC_H), RSFT_T(KC_A), LALT_T(KC_E), RGUI_T(KC_I), KC_SCLN,
        LSFT_T(KC_MINS), KC_Z,            KC_X,            LSFT_T(KC_M),    RALT_T(KC_C),    KC_V,            KC_K,            RALT_T(KC_P),    RSFT_T(KC_COMM), KC_DOT,          KC_SLSH,         LT(0, KC_MINS),
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

    // Held via the W/E/R/G positions (Gralmak l/d/w/g): GUI (+Alt/Shift/Ctrl) is registered as real
    // mods by process_gui_layers(), so the plain keys below combine with them.
    [LAYER_GUI_NUM] = LAYOUT_LR(
        _______,         _______,         _______,         _______,         _______,         _______,         KC_6,            KC_7,            KC_8,            KC_9,            KC_0,            KC_MINS,
        _______,         _______,         _______,         _______,         _______,         _______,         KC_EQL,          KC_7,            KC_8,            KC_9,            KC_QUOT,         KC_PPLS,
        _______,         _______,         _______,         _______,         _______,         _______,         KC_MINS,         KC_4,            KC_5,            KC_6,            KC_PDOT,         S(KC_9),
        _______,         _______,         _______,         _______,         _______,         _______,         KC_0,            KC_1,            KC_2,            KC_3,            KC_BSLS,         S(KC_0),
                                                           _______,         _______,         _______,         KC_PENT,         KC_BSPC,         KC_DEL
    ),

    // Held via the U/I/O/H positions (Gralmak f/o/u/y): GUI (+Ctrl/Shift/Alt) is registered as real
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
    {{LCTL_T(KC_S), LT(LAYER_GUI_NUM, KC_G), KC_NO, KC_NO}, U_SELECT_WORD},
    {{LT(LAYER_GUI_NUM, KC_W), KC_Q, KC_NO, KC_NO}, U_SELECT_WORD_BACK},
    {{RALT_T(KC_C), KC_V, KC_NO, KC_NO}, U_JOIN_LN},
    {{KC_K, RALT_T(KC_P), KC_NO, KC_NO}, KC_0},
    {{LT(LAYER_GUI_NAV, KC_Y), RCTL_T(KC_H), KC_NO, KC_NO}, KC_MINS},
    {{KC_J, LT(LAYER_GUI_NAV, KC_F), KC_NO, KC_NO}, KC_EQL},
    {{LT(LAYER_GUI_NUM, KC_W), LCTL_T(KC_S), KC_NO, KC_NO}, KC_GRV},
    {{LT(LAYER_GUI_NAV, KC_F), RCTL_T(KC_H), KC_NO, KC_NO}, KC_SCLN},
    {{LT(LAYER_GUI_NUM, KC_L), LALT_T(KC_R), KC_NO, KC_NO}, S(KC_9)},
    {{LT(LAYER_GUI_NUM, KC_D), LSFT_T(KC_T), KC_NO, KC_NO}, S(KC_0)},
    {{LT(LAYER_GUI_NAV, KC_O), RSFT_T(KC_A), KC_NO, KC_NO}, KC_LBRC},
    {{LT(LAYER_GUI_NAV, KC_U), LALT_T(KC_E), KC_NO, KC_NO}, KC_RBRC},
    {{LT(1, KC_SPC), LT(3, KC_TAB), KC_NO, KC_NO}, KC_ENT},
    {{LT(5, KC_ESC), LT(1, KC_SPC), KC_NO, KC_NO}, KC_BSPC},
    {{LT(LAYER_GUI_NUM, KC_L), LT(LAYER_GUI_NUM, KC_D), LT(LAYER_GUI_NUM, KC_W), KC_NO}, U_SRCHSEL},
    {{KC_X, LSFT_T(KC_M), RALT_T(KC_C), KC_NO}, U_USERNAME},
    {{LT(LAYER_GUI_NAV, KC_F), LT(LAYER_GUI_NAV, KC_O), LT(LAYER_GUI_NAV, KC_U), KC_NO}, U_AND_OPERATOR},
    {{RALT_T(KC_P), RSFT_T(KC_COMM), KC_DOT, KC_NO}, U_ARROW},
    {{KC_K, RALT_T(KC_P), RSFT_T(KC_COMM), KC_NO}, U_NOT_EQUAL},
    {{LT(LAYER_GUI_NAV, KC_Y), RCTL_T(KC_H), RSFT_T(KC_A), KC_NO}, U_DOUBLE_MINUS},
    {{KC_J, LT(LAYER_GUI_NAV, KC_F), LT(LAYER_GUI_NAV, KC_O), KC_NO}, U_EQUAL},
    {{LALT_T(KC_R), KC_X, KC_NO, KC_NO}, U_UP_DIRECTORY},
    {{LALT_T(KC_E), KC_DOT, KC_NO, KC_NO}, U_THREE_DOTS},
    {{LGUI_T(KC_N), KC_Z, KC_NO, KC_NO}, QK_LAYER_LOCK},
    {{RGUI_T(KC_I), KC_SLSH, KC_NO, KC_NO}, U_DOUBLE_SLASH},
    {{LSFT_T(KC_T), LSFT_T(KC_M), KC_NO, KC_NO}, OSM(MOD_LSFT)},
    {{LCTL_T(KC_S), RALT_T(KC_C), KC_NO, KC_NO}, OSM(MOD_RALT)},
    {{RCTL_T(KC_H), RALT_T(KC_P), KC_NO, KC_NO}, OSM(MOD_RALT)},
    {{RSFT_T(KC_A), RSFT_T(KC_COMM), KC_NO, KC_NO}, OSM(MOD_RSFT)},
    {{LT(LAYER_GUI_NUM, KC_L), LALT_T(KC_R), LT(LAYER_GUI_NUM, KC_D), LSFT_T(KC_T)}, U_PARENTHESES},
    {{LT(LAYER_GUI_NAV, KC_O), RSFT_T(KC_A), LT(LAYER_GUI_NAV, KC_U), LALT_T(KC_E)}, U_BRACKETS},
    {{LT(4, KC_ENT), LT(2, KC_BSPC), KC_NO, KC_NO}, QK_ALT_REPEAT_KEY},
    {{LT(2, KC_BSPC), LT(6, KC_DEL), KC_NO, KC_NO}, QK_REPEAT_KEY},
    {{KC_Q, LT(LAYER_GUI_NUM, KC_G), KC_NO, KC_NO}, S(KC_GRV)},
    {{KC_J, LT(LAYER_GUI_NAV, KC_Y), KC_NO, KC_NO}, S(KC_SCLN)},
    {{KC_B, LGUI_T(KC_N), KC_NO, KC_NO}, U_DOUBLE_BACKTICK},
    {{KC_QUOT, RGUI_T(KC_I), KC_NO, KC_NO}, KC_QUOT},
    {{LT(LAYER_GUI_NUM, KC_G), KC_V, KC_NO, KC_NO}, S(KC_LBRC)},
    {{LT(LAYER_GUI_NAV, KC_Y), KC_K, KC_NO, KC_NO}, S(KC_RBRC)},
    {{LT(LAYER_GUI_NUM, KC_G), KC_V, LT(LAYER_GUI_NAV, KC_Y), KC_K}, U_BRACES},
    {{LSFT_T(KC_M), RALT_T(KC_C), KC_V, KC_NO}, U_LOWER_THAN_OR_EQUAL},
    {{LT(LAYER_GUI_NUM, KC_D), LT(LAYER_GUI_NUM, KC_W), KC_Q, KC_NO}, U_LEFT_SHIFT},
    {{OSM(MOD_LSFT), OSM(MOD_RALT), KC_NO, KC_NO}, OSM(MOD_RSFT | MOD_RALT)},
    {{RCTL_T(KC_H), RALT_T(KC_P), RSFT_T(KC_A), RSFT_T(KC_COMM)}, OSM(MOD_RSFT | MOD_RALT)},
    {{KC_DOT, KC_SLSH, KC_NO, KC_NO}, U_CURRENT_DIRECTORY},
    {{LT(5, KC_ESC), LT(6, KC_DEL), KC_NO, KC_NO}, MO(LAYER_ADJUST)},
    {{LSFT_T(KC_T), LCTL_T(KC_S), LT(LAYER_GUI_NUM, KC_G), KC_NO}, U_SELECT_LINE},
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

#include "../philong/philong_core.c"

bool is_alpha(const uint16_t keycode) {
    return KC_A <= keycode && keycode <= KC_Z;
}

bool is_quopostrokey_target(uint16_t keycode, keyrecord_t *record) {
    return keycode == KC_QUOT;
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
        case KC_N:
        case KC_R:
        case KC_T:
        case KC_S:
        case KC_H:
        case KC_A:
        case KC_E:
        case KC_I:
            return 0;  // Disable filter for these keys.
    }

    // AltGr producing accented characters
    switch (prev_keycode) {
        case RALT_T(KC_X):
        case RALT_T(KC_C):
            switch (tap_keycode) {
                case KC_A: // à
                case KC_E: // é
                case KC_I: // î
                case KC_O: // ô
                case KC_U: // ù
                case KC_P: // ü (the right AltGr key tapped)
                    return 0;
            }
            break;
        case RALT_T(KC_DOT):
        case RALT_T(KC_P):
            switch (tap_keycode) {
                case KC_D: // è
                case KC_R: // ê
                case KC_W: // ë
                case KC_N: // ñ (EurKEY native)
                case KC_C: // ç (EurKEY native)
                    return 0;
            }
            break;
        case LSFT_T(KC_M):
            if (tap_keycode == KC_C || tap_keycode == KC_X) {
                return 0;
            }
            break;
        case RSFT_T(KC_COMM):
            if (tap_keycode == KC_P || tap_keycode == KC_DOT) {
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

    // RGui+L screen lock protection: force RGUI_T(KC_I) to tap when L is
    // pressed (Gralmak puts L on the left hand, opposite the right GUI).
    if (tap_hold_keycode == RGUI_T(KC_I) && get_tap_keycode(other_keycode) == KC_L) {
        return false;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}
#endif

// The two GUI layers are shared by several layer-tap keys; which GUI+modifier
// combination gets held as real mods depends on the trigger's tap keycode.
uint8_t gui_layer_mods(uint16_t tap_keycode) {
    switch (tap_keycode) {
        case KC_L:
        case KC_U:
            return MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI);
        case KC_D:
        case KC_O:
            return MOD_BIT(KC_LSFT) | MOD_BIT(KC_LGUI);
        case KC_W:
        case KC_F:
            return MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI);
        case KC_G:
            return MOD_BIT(KC_LGUI);
        case KC_Y:
            return MOD_BIT(KC_RGUI);
        default:
            return 0;
    }
}

// French accents by default on AltGr+letter. Same character-based map as
// philong-eurkey: each vowel carries its most-used French accent (e=é, a=à,
// i=î, o=ô, u=ù), the rest by frequency on d=è, r=ê, w=ë, q=â, j=û, k=ï,
// p=ü. Letters not listed (ç on C, ñ on N, á on X, …) fall through to
// EurKEY's native AltGr mapping. The switch matches tap keycodes, which
// equal typed characters on the QWERTY-based host, so it is independent of
// the key arrangement. Most accents are direct EurKEY AltGr chords (capital
// on the AltGr+Shift level); circumflex only exists as the dead key AltGr+6.
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

bool process_variant_french_accents(uint16_t keycode, keyrecord_t *record) {
    return process_eurkey_fr(keycode, record, U_EURKEY_FR_TOGG);
}
