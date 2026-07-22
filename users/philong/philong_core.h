// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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

    U_FR_TOGG,
    U_PUNCTUATION_MOD_TOGG,

    U_LOGIN_ADMIN,
    U_LOGIN_DEMO,

    U_QUOPOSTROKEY,
    U_QUOPOSTROKEY_TOGG,
};

#define U_CM_TOGG U_FR_TOGG
#define U_EURKEY_FR_TOGG U_FR_TOGG

#define _______ KC_TRNS

typedef union {
    uint32_t raw;
    struct {
        // Set by eeconfig_init_user(): distinguishes initialized defaults
        // from a zeroed user datablock (raw == 0 must read as uninitialized).
        bool initialized : 1;
        bool fr_accent : 1;
        bool punctuation_mod: 1;
        bool quopostrokey : 1;
    };
} user_config_t;

#define colemak_fr fr_accent
#define eurkey_fr fr_accent

extern user_config_t user_config;

// Prototypes for functions provided by variant-specific files:
bool is_alpha(const uint16_t keycode);
uint8_t gui_layer_mods(uint16_t tap_keycode);
bool process_variant_french_accents(uint16_t keycode, keyrecord_t *record);
bool is_quopostrokey_target(uint16_t keycode, keyrecord_t *record);

// Core helper functions provided by philong_core:
void via_init_kb(void);
uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods);
uint8_t combo_ref_from_layer(uint8_t layer);
void clear_all_mods(void);
layer_state_t get_current_layer(void);
bool is_layer(layer_state_t state);
bool is_nav_layer(void);
bool on_left_hand(keypos_t pos);
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record);
bool caps_word_press_user(uint16_t keycode);
bool process_tap_or_hold_press_key(keyrecord_t* record, const char *tap_string, uint16_t hold_keycode);
bool process_clipboard_shortcuts(uint16_t keycode, keyrecord_t *record);
bool process_custom_tap_holds(uint16_t keycode, keyrecord_t *record);
bool process_shift_backspace_delete(uint16_t keycode, keyrecord_t *record);
bool process_joinln(uint16_t keycode, keyrecord_t *record, uint16_t joinln_keycode);
bool process_select_word_user(uint16_t keycode, keyrecord_t *record);
bool process_login_macros(uint16_t keycode, keyrecord_t *record);
bool process_macros_user(uint16_t keycode, keyrecord_t *record);
bool process_caps_word_escape(uint16_t keycode, keyrecord_t *record);
bool process_layer_lock_user(uint16_t keycode, keyrecord_t *record);
bool process_num_layer_override(uint16_t keycode, keyrecord_t *record);
bool process_nav_override(uint16_t keycode, keyrecord_t *record);
uint8_t get_keycode_mods(uint8_t mods);
uint16_t combine_keycode(uint16_t keycode, uint8_t mods);
bool process_punctuation_mod(uint16_t keycode, keyrecord_t *record, uint16_t toggle_keycode);
bool process_gui_layers(uint16_t keycode, keyrecord_t *record);
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record);
void send_char_shifted(char key);
bool send_key_with_ralt(char key, char dead_ralt_key, uint8_t mods, bool shifted);
bool send_ralt_key(char key, uint8_t mods, bool shifted);
bool process_quopostrokey(uint16_t keycode, keyrecord_t *record, uint16_t toggle_keycode);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
void keyboard_post_init_user(void);
void eeconfig_init_user(void);
