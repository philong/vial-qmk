// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "via.h"
#include "qmk_settings.h"
#include "process_magic.h"

#include "quantum/keymap_extras/sendstring_colemak.h"

#ifdef ACHORDION_ENABLE
#include "features/achordion.h"
#endif  // ACHORDION_ENABLE

#include "features/layer_lock.h"
#include "features/select_word.h"
#include "features/repeat_key.h"
#include "features/sentence_case.h"
#ifndef AUTOCORRECT_ENABLE
#    include "features/autocorrection.h"
#endif
#ifdef MOUSEKEY_ENABLE
#    include "features/mouse_turbo_click.h"
#endif
#include "features-andrewjrae/casemodes.h"
#include "features-treeman/layermodes.h"

#include "autocomplete.h"

#include "keycodes.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
                                                                  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
                                                                  KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
                                                                  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                                  KC_LGUI, MO(1), KC_SPC, KC_ENT, MO(2), KC_RALT
                                                                  //`--------------------------'  `--------------------------'

                                                                  ),

                                                              [1] = LAYOUT_split_3x6_3(
                                                                  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
                                                                  KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                                  KC_LGUI, _______, KC_SPC, KC_ENT, MO(3), KC_RALT
                                                                  //`--------------------------'  `--------------------------'
                                                                  ),

                                                              [2] = LAYOUT_split_3x6_3(
                                                                  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
                                                                  KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                                                  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                                  KC_LGUI, MO(3), KC_SPC, KC_ENT, _______, KC_RALT
                                                                  //`--------------------------'  `--------------------------'
                                                                  ),

                                                              [3] = LAYOUT_split_3x6_3(
                                                                  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
                                                                  QK_BOOT, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, QK_BOOT,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
                                                                  RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                                  KC_LGUI, _______, KC_SPC, KC_ENT, _______, KC_RALT
                                                                  //`--------------------------'  `--------------------------'
  )
};

#ifdef CHORDAL_HOLD
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         '*',      'L',     'L',     'L',     'L',     'L',                          'R',     'R',     'R',     'R',    'R',     '*',
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         '*',      'L',     'L',     'L',     'L',     'L',                          'R',     'R',     'R',     'R',    'R',     '*',
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         '*',      'L',     'L',     'L',     'L',     'L',                          'R',     'R',     'R',     'R',    'R',     '*',
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              '*',     '*',    '*',         '*',     '*',     '*'
    //                                    `--------------------------'  `--------------------------'
    );
#endif  // CHORDAL_HOLD

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
    {U_USERNAME, "philong", "Phi-Long", "philong.do@gmail.com", "p.do@axelor.com"},
};

const size_t NUM_USER_MACROS = sizeof(USER_MACROS) / sizeof(*USER_MACROS);

static bool          sentence_primed         = false;
static bool          dynamic_macro_recording = false;
static bool          oneshot_mods_enabled    = false;
static bool          oneshot_layer_enabled   = false;
static layer_state_t locked_layers           = 0;

static bool quopostrokey_is_quote = false;

typedef union {
    uint32_t raw;
    struct {
        bool colemak_fr : 1;
        bool punctuation_mod: 1;
    };
} user_config_t;

user_config_t user_config;

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) { // EEPROM is getting reset!
    set_unicode_input_mode(UNICODE_MODE_LINUX);
    user_config.raw        = 0;
    user_config.colemak_fr = true;
    user_config.punctuation_mod = true;
#ifdef AUTOCORRECT_ENABLE
    autocorrect_enable();
#endif
    eeconfig_update_user(user_config.raw);
}

void clear_all_mods(void) {
    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();
}

void set_led(bool active) {
}

bool oneshot_active(void) {
    return oneshot_mods_enabled || oneshot_layer_enabled;
}

bool layer_locked(void) {
    return locked_layers != 0;
}

bool led_enabled_user(void) {
    return is_caps_word_on() || get_xcase_state() != XCASE_OFF || num_word_enabled() || layer_locked() || sentence_primed || dynamic_macro_recording || oneshot_active();
}

void update_led(void) {
    set_led(led_enabled_user());
}

bool is_tap_dance(const uint16_t keycode) {
    return QK_TAP_DANCE <= keycode && keycode <= QK_TAP_DANCE_MAX;
}

// KC_A ... KC_Z -> Colemak
bool is_alpha(const uint16_t keycode) {
    return (KC_A <= keycode && keycode <= KC_O) // Exclude CM_SCLN == KC_P
           || (keycode == CM_O)                 // Include CM_O == KC_SCLN
           || (KC_Q <= keycode && keycode <= KC_Z);
}

// Mod-tap, RAlt mod and Colemak
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    return IS_QK_MOD_TAP(keycode) || (keycode >= QK_RALT && keycode < QK_RGUI) || keycode == CM_SCLN;
}
static const uint16_t END_KEY_LAYER = 0;

static uint16_t get_base_tapping_term(void) {
#ifdef VIAL_KEYBOARD_UID
    return QS.tapping_term;
#else
    return TAPPING_TERM;
#endif
}

#ifdef VIAL_KEYBOARD_UID
uint16_t qs_get_tapping_term(uint16_t keycode, keyrecord_t *record) {
#else
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
#endif
    uint16_t tap_keycode;

    if (IS_QK_LAYER_TAP(keycode)) {
        const uint16_t layer = QK_LAYER_TAP_GET_LAYER(keycode);
        if (layer == END_KEY_LAYER) {
            return get_base_tapping_term();
        }
        tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MOD_TAP(keycode)) {
        tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else {
        return get_base_tapping_term();
    }

    switch (tap_keycode) {
        // Increase the tapping term for slower ring and pinky fingers.
        case CM_Q:
        case CM_W:
        case CM_A:
        case CM_R:
        case CM_Z:
        case CM_X:
        case CM_Y:
        case CM_SCLN:
        case CM_I:
        case CM_O:
        case CM_DOT:
        case CM_SLSH:
            return get_base_tapping_term() + 15;

        default:
            return get_base_tapping_term();
    }
}

void oneshot_mods_changed_user(uint8_t mods) {
    oneshot_mods_enabled = mods != 0;
}
void oneshot_locked_mods_changed_user(uint8_t mods) {
    oneshot_mods_enabled = mods != 0;
}
void oneshot_layer_changed_user(uint8_t layer) {
    oneshot_layer_enabled = layer != 0;
}

void toggle_num_word(void) {
    if (num_word_enabled()) {
        disable_num_word();
    } else {
        enable_num_word();
    }
}

bool process_num_word(uint16_t keycode, const keyrecord_t *record) {
    if (!num_word_enabled()) return true;

    switch (keycode) {
        case TD(10):
            if (record->event.pressed) {
                disable_num_word();
                tap_code16(CM_SCLN);
            }
            return false;
    }

    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            if (record->tap.count == 0) return true;
            keycode = keycode & 0xFF;
    }

    switch (keycode) {
        case CM_1 ... CM_0:
        case CM_PERC:
        case CM_COMM:
        case CM_DOT:
        case CM_SLSH:
        case CM_MINS:
        case CM_ASTR:
        case CM_PLUS:
        case CM_COLN:
        case CM_EQL:
        case CM_UNDS:
        case KC_BSPC:
        case CM_X:
        case KC_KP_DOT:
        // case QK_REPEAT_KEY:
        // case QK_ALT_REPEAT_KEY:
        case U_REPEAT:
        case U_ALT_REPEAT:
        case KC_KP_ENTER:
            // case KC_ENT:
            // case xxxxxxx:
            // Don't disable for above keycodes
            break;
        case KC_ESCAPE:
            if (record->event.pressed) {
                disable_num_word();
            }
            return false;
        default:
            if (record->event.pressed) {
                disable_num_word();
            }
    }

    return true;
}

// Colemak
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            keycode = keycode & 0xFF;
    }

    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_O:
        case KC_Q ... KC_Z:
        case CM_O:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)
        case KC_A ... KC_O:
        case KC_Q ... KC_Z:
        case CM_O:
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
        case KC_LSFT:
        case KC_RSFT:
        case U_OS_LSFT:
        case U_OS_RSFT:
            // If mod chording disable the mods
            if (record->event.pressed && (get_mods() != 0)) {
                return true;
            }
            break;
        default:
            if (record->event.pressed) {
                return true;
            }
            break;
    }
    return false;
}

void caps_word_set_user(bool active) {
    update_led();
}

void xcase_set_user(enum xcase_state state) {
    update_led();
}

bool led_update_user(led_t led_state) {
    if (led_enabled_user()) {
        set_led(true);
        return false;
    }
    return true;
}

void sentence_case_primed(bool primed) {
    sentence_primed = primed;
    update_led();
}

static bool         dynamic_macro_recorded[]   = {false, false};
static const size_t DYNAMIC_MACRO_RECORDED_LEN = sizeof(dynamic_macro_recorded) / sizeof(bool);

size_t get_dynamic_macro_index(int8_t direction) {
    if (direction > 0) {
        return 0;
    } else if (direction < 0) {
        return 1;
    }
    return -1;
}

bool dynamic_macro_record_start_user(int8_t direction) {
    dynamic_macro_recording = true;
    update_led();
    return true;
}

bool dynamic_macro_record_end_user(int8_t direction) {
    dynamic_macro_recording = false;
    update_led();
    size_t index = get_dynamic_macro_index(direction);
    if (index < 0 || index >= DYNAMIC_MACRO_RECORDED_LEN || dynamic_macro_recorded[index]) return true;
    dynamic_macro_recorded[index] = true;
    return true;
}

// void dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record) {
//     size_t index = get_dynamic_macro_index(direction);
//     if (index < 0 || index >= DYNAMIC_MACRO_RECORDED_SIZE || dynamic_macro_recorded[index]) return;
//     dynamic_macro_recorded[index] = true;
// }

bool dynamic_macro_play_user(int8_t direction) {
    size_t index = get_dynamic_macro_index(direction);
    if (index < 0 || index >= DYNAMIC_MACRO_RECORDED_LEN || dynamic_macro_recorded[index]) return true;

    switch (index) {
        case 0:
            SEND_STRING_DELAY(SS_TAP(X_END) SS_TAP_CODE_DELAY SS_LSFT(SS_TAP(X_HOME)) SS_TAP_CODE_DELAY DMACRO1_TEXT1 SS_TAP(X_TAB) SS_TAP_CODE_DELAY, 2);
            SEND_STRING_DELAY(SS_TAP(X_END) SS_TAP_CODE_DELAY SS_LSFT(SS_TAP(X_HOME)) SS_TAP_CODE_DELAY DMACRO1_TEXT2 SS_TAP(X_ENTER), 2);
            break;
        case 1:
        default:
            SEND_STRING_DELAY(SS_TAP(X_END) SS_TAP_CODE_DELAY SS_LSFT(SS_TAP(X_HOME)) SS_TAP_CODE_DELAY DMACRO2_TEXT1 SS_TAP(X_TAB) SS_TAP_CODE_DELAY, 2);
            SEND_STRING_DELAY(SS_TAP(X_END) SS_TAP_CODE_DELAY SS_LSFT(SS_TAP(X_HOME)) SS_TAP_CODE_DELAY DMACRO2_TEXT2 SS_TAP(X_ENTER), 2);
    }
    return true;
}

// Colemak
bool sentence_case_check_ending(const uint16_t *buffer) {
#if SENTENCE_CASE_BUFFER_SIZE >= 5
    // Don't consider the abbreviations "vs." and "etc." to end the sentence.
    if (SENTENCE_CASE_JUST_TYPED(KC_SPC, CM_V, CM_S, CM_DOT) || SENTENCE_CASE_JUST_TYPED(KC_SPC, CM_E, CM_T, CM_C, CM_DOT)) {
        return false; // Not a real sentence ending.
    }
#endif           // SENTENCE_CASE_BUFFER_SIZE >= 5
    return true; // Real sentence ending; capitalize next letter.
}

// Colemak
#ifndef AUTOCORRECT_ENABLE
bool autocorrection_is_letter(uint16_t keycode) {
    return is_alpha(keycode);
}
bool autocorrection_is_boundary(uint16_t keycode) {
    return (KC_1 <= keycode && keycode <= KC_SLSH && keycode != KC_SCLN) || keycode == KC_P;
}
#else
bool autocorrect_is_alpha(uint16_t keycode) {
    return is_alpha(keycode);
}
bool autocorrect_is_boundary(uint16_t keycode) {
    return (KC_1 <= keycode && keycode <= KC_0) || (KC_TAB <= keycode && keycode < KC_SCLN) || (keycode == CM_SCLN) || (KC_GRAVE <= keycode && keycode <= KC_SLASH);
}
#endif

// Colemak
char sentence_case_press_user(uint16_t keycode, keyrecord_t *record, uint8_t mods) {
    if ((mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
        const bool shifted = mods & MOD_MASK_SHIFT;
        switch (keycode) {
            case KC_LCTL ... KC_RGUI: // Mod keys.
                return '\0';          // These keys are ignored.

            case KC_A ... KC_O:
            case KC_Q ... KC_Z:
            case KC_SCLN:
                return 'a'; // Letter key.

            case KC_DOT: // . is punctuation, Shift . is a symbol (>)
                return !shifted ? '.' : '#';
            case KC_1:
            case KC_SLSH:
                return shifted ? '.' : '#';
            case KC_2 ... KC_0: // 2 3 4 5 6 7 8 9 0
            case KC_MINS:       // - = [ ] ; backslash
            case KC_EQUAL:
            case KC_LEFT_BRACKET:
            case KC_RIGHT_BRACKET:
            case KC_P:
            case KC_BACKSLASH:

            case KC_GRAVE:
            case KC_COMMA:
                return '#'; // Symbol key.

            case KC_SPC:
                return ' '; // Space key.

            case KC_QUOT:
            case U_QUOP:
                return '\''; // Quote key.
            case KC_F24:
                return '.'; // Exclamation key.
        }
    }

    // Otherwise clear Sentence Case to initial state.
    sentence_case_clear();
    return '\0';
}

static bool lctl_primed = false;
static bool lsft_primed = false;
static bool lalt_primed = false;
static bool lgui_primed = false;
static bool rctl_primed = false;
static bool rsft_primed = false;
static bool ralt_primed = false;
static bool rgui_primed = false;

bool is_oneshot_trigger(uint16_t keycode) {
    return U_OS_LCTL <= keycode && keycode <= U_OS_RGUI;
}

bool process_oneshot_trigger(uint16_t keycode, keyrecord_t *record, uint16_t trigger_keycode, uint16_t mod_key, bool *primed) {
    if (keycode != trigger_keycode) {
        if (primed && !is_oneshot_trigger(keycode)) {
            *primed = false;
        }
        return true;
    }

    static fast_timer_t oneshot_timer = 0;

    if (record->event.pressed) {
        register_code(mod_key);
        oneshot_timer = timer_read_fast();
        *primed       = true;
    } else {
        unregister_code(mod_key);
        if (*primed) {
            if (timer_elapsed_fast(oneshot_timer) <= GET_TAPPING_TERM(keycode, record)) {
                // Primed and tapped
                set_oneshot_mods(get_oneshot_mods() | MOD_BIT(mod_key));
            }
            *primed = false;
        }
    }

    return false;
}

bool process_oneshot(uint16_t keycode, keyrecord_t *record) {
    if (!process_oneshot_trigger(keycode, record, U_OS_LCTL, KC_LCTL, &lctl_primed)) {
        return false;
    }
    if (!process_oneshot_trigger(keycode, record, U_OS_LSFT, KC_LSFT, &lsft_primed)) {
        return false;
    }
    if (!process_oneshot_trigger(keycode, record, U_OS_LALT, KC_LALT, &lalt_primed)) {
        return false;
    }
    if (!process_oneshot_trigger(keycode, record, U_OS_LGUI, KC_LGUI, &lgui_primed)) {
        return true;
    }
    if (!process_oneshot_trigger(keycode, record, U_OS_RCTL, KC_RCTL, &rctl_primed)) {
        return false;
    }
    if (!process_oneshot_trigger(keycode, record, U_OS_RSFT, KC_RSFT, &rsft_primed)) {
        return false;
    }
    if (!process_oneshot_trigger(keycode, record, U_OS_RALT, KC_RALT, &ralt_primed)) {
        return false;
    }
    if (!process_oneshot_trigger(keycode, record, U_OS_RGUI, KC_RGUI, &rgui_primed)) {
        return false;
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

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    uint16_t tap_keycode;

    if (IS_QK_LAYER_TAP(keycode)) {
        tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MOD_TAP(keycode)) {
        tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else {
        tap_keycode = keycode;
    }

    const bool shifted    = mods & MOD_MASK_SHIFT;
    const bool controlled = mods & MOD_MASK_CTRL;
    const bool alted      = mods & MOD_MASK_ALT;
    const bool guied      = mods & MOD_MASK_GUI;

    if (shifted) {
        switch (tap_keycode) {
            case CM_GRV:
                tap_keycode = CM_TILD; // ~
                break;
            case CM_1:
                tap_keycode = CM_EXLM; // !
                break;
            case CM_2:
                tap_keycode = CM_AT; // @
                break;
            case CM_3:
                tap_keycode = CM_HASH; // #
                break;
            case CM_4:
                tap_keycode = CM_DLR; // $
                break;
            case CM_5:
                tap_keycode = CM_PERC; // %
                break;
            case CM_6:
                tap_keycode = CM_CIRC; // ^
                break;
            case CM_7:
                tap_keycode = CM_AMPR; // &
                break;
            case CM_8:
                tap_keycode = CM_ASTR; // *
                break;
            case CM_9:
                tap_keycode = CM_LPRN; // (
                break;
            case CM_0:
            case TD(4):
                tap_keycode = CM_RPRN; // )
                break;
            case CM_MINS:
                tap_keycode = CM_UNDS; // _
                break;
            case CM_EQL:
                tap_keycode = CM_PLUS; // +
                break;
            case CM_SCLN:
                tap_keycode = CM_COLN; // :
                break;
            case CM_LBRC:
                tap_keycode = CM_LCBR; // {
                break;
            case CM_RBRC:
                tap_keycode = CM_RCBR; // }
                break;
            case CM_BSLS:
                tap_keycode = CM_PIPE; // |
                break;
            case CM_QUOT:
                tap_keycode = CM_DQUO; // "
                break;
            case CM_COMM:
                tap_keycode = CM_LABK; // <
                break;
            case CM_DOT:
                tap_keycode = CM_RABK; // >
                break;
            case CM_SLSH:
                tap_keycode = CM_QUES; // ?
                break;
        }
    }

    switch (tap_keycode) {
        case U_SEL_WORD:
            return shifted ? S(KC_UP) : C(S(KC_LEFT));
        case U_JOIN_LN:
            return shifted ? U_JOIN_LN : S(U_JOIN_LN);
        case U_QUOP:
            return quopostrokey_is_quote ? CM_DQUO : CM_QUOT;
        case KC_SPACE:
            return combine_keycode(KC_BACKSPACE, mods);
        case KC_ENTER:
            return combine_keycode(KC_ESCAPE, mods);
        case KC_ESCAPE:
            return combine_keycode(KC_ENTER, mods);
        case CM_GRV:
            return CM_GRV; // ``
        case CM_1 ... CM_0:
        case TD(4):
            return CM_1; // 00, 000
        case CM_MINS:
            return CM_EQL;
        case CM_EQL:
            return U_EQUAL;
        case CM_SCLN:
            return CM_SCLN; // Comment
        case CM_LBRC:
        case TD(0):
            return shifted ? CM_LCBR : CM_LBRC; // []
        case CM_RBRC:
            return shifted ? KC_ENTER : CM_RBRC;
        case CM_BSLS:
            return CM_BSLS;
        case CM_QUOT:
            return CM_QUOT; // ''
        case CM_COMM:
            return KC_SPACE;
        case CM_DOT:
            return CM_DOT; // ./, ../
        case CM_SLSH:
            return CM_SLSH; // //
        case CM_TILD:
            return CM_TILD;
        case CM_EXLM:
        case KC_F24: // !
            return CM_EQL;
        case CM_AT:
            return CM_AT; // gmail.com
        case CM_HASH:
            return CM_HASH;
        case CM_DLR:
            return CM_DLR; // {}
        case CM_PERC:
            return CM_PERC;
        case CM_CIRC:
            return CM_2;
        case CM_AMPR:
            return CM_AMPR; // &&
        case CM_ASTR:
            return CM_ASTR; // *text*
        case CM_LPRN:
        case TD(1):
            return CM_LPRN; // ()
        case CM_RPRN:
            return KC_SPACE;
        case CM_UNDS:
            return CM_UNDS; // _text_
        case CM_PLUS:
            return CM_EQL;
        case CM_COLN:
        case KC_F23:        // :
            return CM_COLN; // "text",
        case CM_LCBR:
        case TD(2):
            return CM_LCBR; // {}
        case CM_RCBR:
            return KC_ENTER;
        case CM_PIPE:
            return CM_PIPE; // ||
        case CM_DQUO:
            return CM_DQUO; // ""
        case CM_LABK:
            return CM_EQL;
        case CM_RABK:
            return CM_EQL;
        case CM_QUES:
            return CM_QUES; // c ? a : b
    }

    // Colemak
    if (controlled || alted || guied) {
        switch (tap_keycode) {
            // F B
            case CM_F:
                return combine_keycode(CM_B, mods);
            case CM_B:
                return combine_keycode(CM_F, mods);
            // D U
            case CM_D:
                return combine_keycode(CM_U, mods);
            case CM_U:
                return combine_keycode(CM_D, mods);
            // N P
            case CM_N:
                return combine_keycode(CM_P, mods);
            case CM_P:
                return combine_keycode(CM_N, mods);
            // A E
            case CM_A:
                return combine_keycode(CM_E, mods);
            case CM_E:
                return combine_keycode(CM_A, mods);
            // O I
            case CM_O:
                return combine_keycode(CM_I, mods);
            case CM_I:
                return combine_keycode(CM_O, mods);
            // J K
            case CM_J:
                return combine_keycode(CM_K, mods);
            case CM_K:
                return combine_keycode(CM_J, mods);
            // H L
            case CM_H:
                return combine_keycode(CM_L, mods);
            case CM_L:
                return combine_keycode(CM_H, mods);
            // W B
            case CM_W:
                return combine_keycode(CM_B, mods);
        }
    } else {
        // Double letter instead of vim support
        switch (tap_keycode) {
            case CM_F:
            case CM_B:
            case CM_D:
            case CM_U:
            case CM_N:
            case CM_P:
            case CM_A:
            case CM_E:
            case CM_O:
            case CM_I:
            case CM_J:
            case CM_K:
            case CM_H:
            case CM_L:
            case CM_W:
                return combine_keycode(tap_keycode, mods);
        }
    }

    if (shifted) {
        if (controlled) {
            // Ctrl + Shift
            switch (tap_keycode) {
                case KC_Z:
                    return C(KC_Z); // Ctrl + Z <-> Ctrl + Shift + Z

                case KC_X:
                    return C(S(KC_V)); // Ctrl + Shift + X -> Ctrl + Shift + V
                case KC_C:
                    return C(S(KC_V)); // Ctrl + Shift + C <-> Ctrl + Shift + V
                case KC_V:
                    return C(S(KC_C)); // Ctrl + Shift + C <-> Ctrl + Shift + V

                case CM_T:
                    return C(CM_W); // Ctrl + Shift + T -> Ctrl + W
            }
        } else {
            // Shift
            switch (tap_keycode) {
                case KC_TAB:
                    return KC_TAB; // Tab <-> Shift + Tab
            }
        }
    } else if (controlled) {
        // Ctrl
        switch (tap_keycode) {
            case KC_Z:
                return C(S(KC_Z)); // Ctrl + Z <-> Ctrl + Shift + Z
            case KC_Y:
                return C(KC_Z); // Ctrl + Y -> Ctrl + Z

            case KC_X:
                return C(KC_V); // Ctrl + X -> Ctrl + V
            case KC_C:
                return C(KC_V); // Ctrl + C <-> Ctrl + V
            case KC_V:
                return C(KC_C); // Ctrl + C <-> Ctrl + V

            case CM_W:
                return C(S(CM_T)); // Ctrl + W -> Ctrl + Shift + T
            case CM_T:
                return C(CM_W); // Ctrl + T -> Ctrl + W
        }
    } else {
        // No mods
        switch (tap_keycode) {
            case KC_TAB:
                return S(KC_TAB); // Tab <-> Shift + Tab
        }
    }

    return KC_TRNS;
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods) {
    return !is_oneshot_trigger(keycode);
}

bool ends_with_two_digits(const char *str) {
    if (str == NULL) { return false; }
    const size_t len = strlen(str);
    return len >= 2 && isdigit((unsigned char)str[len - 1])
            && isdigit((unsigned char)str[len - 2]);
}

bool process_repeat_key_with_alt_user(uint16_t keycode, keyrecord_t *record, uint16_t repeat_keycode, uint16_t alt_repeat_keycode) {
    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if ((all_mods & MOD_MASK_SHIFT)) {
        if (keycode == repeat_keycode) {
            // Shift + QK_REPEAT_KEY -> QK_ALT_REPEAT_KEY
            clear_all_mods();
            bool result = process_repeat_key_with_alt(alt_repeat_keycode, record, repeat_keycode, alt_repeat_keycode);
            set_mods(mods);
            return result;
        } else if (keycode == alt_repeat_keycode) {
            // Shift + QK_ALT_REPEAT_KEY -> QK_REPEAT_KEY
            clear_all_mods();
            bool result = process_repeat_key_with_alt(repeat_keycode, record, repeat_keycode, alt_repeat_keycode);
            set_mods(mods);
            return result;
        }
    }

    // Custom alt repeat key
    if (record->event.pressed) {
        switch (keycode) {
            case CM_GRV:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("`" SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() == -2) {
                    SEND_STRING("````" SS_TAP(X_LEFT) SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() == -3) {
                    SEND_STRING(SS_LSFT(SS_TAP(X_ENT)) SS_TAP(X_UP) SS_TAP(X_END));
                    return false;
                } else if (get_repeat_key_count() <= -4) {
                    SEND_STRING(SS_LSFT(SS_TAP(X_ENT)));
                    return false;
                }
                break;
            case CM_1:
                if (get_repeat_key_count() == -1) {
                    const char *word = get_current_word();
                    if (ends_with_two_digits(word)) {
                        SEND_STRING("000");
                    } else {
                        SEND_STRING("00");
                    }
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING("000");
                    return false;
                }
                break;
            case CM_SCLN:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING(" // ");
                    return false;
                }
                break;
            case CM_LBRC:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("0]");
                    return false;
                } else if (get_repeat_key_count() < -1 && get_repeat_key_count() >= -10) {
                    char str[2];
                    sprintf(str, "%d", -get_repeat_key_count() - 1);
                    SEND_STRING(SS_TAP(X_BSPC) SS_TAP(X_BSPC));
                    SEND_STRING(str);
                    SEND_STRING("]");
                    return false;
                } else if (get_repeat_key_count() < -10) {
                    SEND_STRING("[]");
                    return false;
                }
                break;
            case CM_RBRC:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING(SS_TAP(X_BSPC) "[-1]");
                    return false;
                } else if (get_repeat_key_count() < -1 && get_repeat_key_count() >= -9) {
                    char str[2];
                    sprintf(str, "%d", -get_repeat_key_count());
                    SEND_STRING(SS_TAP(X_BSPC) SS_TAP(X_BSPC));
                    SEND_STRING(str);
                    SEND_STRING("]");
                    return false;
                } else if (get_repeat_key_count() < -9) {
                    SEND_STRING("[]");
                    return false;
                }
                break;
            case CM_BSLS:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("n");
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING("\\n");
                    return false;
                }
                break;
            case CM_QUOT:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("'" SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() == -2) {
                    SEND_STRING("''''" SS_TAP(X_LEFT) SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() == -3) {
                    SEND_STRING(SS_LSFT(SS_TAP(X_ENT)) SS_TAP(X_UP) SS_TAP(X_END));
                    return false;
                } else if (get_repeat_key_count() <= -4) {
                    SEND_STRING(SS_LSFT(SS_TAP(X_ENT)));
                    return false;
                }
                break;
            case CM_DOT:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING(CURRENT_DIRECTORY);
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING(UP_DIRECTORY);
                    return false;
                }
                break;
            case CM_SLSH:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("/ ");
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING(SS_TAP(X_ENT) "// ");
                    return false;
                }
                break;
            case CM_TILD:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("/");
                    return false;
                }
                break;
            case CM_AT:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("gmail.com");
                    return false;
                }
                break;
            case CM_HASH:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING(" ");
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING(SS_TAP(X_ENT) "# ");
                    return false;
                }
                break;
            case CM_DLR:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("{}" SS_TAP(X_LEFT));
                    return false;
                }
                break;
            case CM_PERC:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("s");
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING("%n");
                    return false;
                }
                break;
            case CM_AMPR:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("& ");
                    return false;
                }
                break;
            case CM_ASTR:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("*" SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING("**" SS_TAP(X_LEFT));
                    return false;
                }
                break;
            case CM_LPRN:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING(")" SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING("()" SS_TAP(X_LEFT));
                    return false;
                }
                break;
            case CM_UNDS:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("_" SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING("__" SS_TAP(X_LEFT));
                    return false;
                }
                break;
            case CM_COLN:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING(" \"\"," SS_TAP(X_LEFT) SS_TAP(X_LEFT));
                    return false;
                }
                break;
            case CM_LCBR:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("}" SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() < -1) {
                    SEND_STRING("{}" SS_TAP(X_LEFT));
                    return false;
                }
                break;
            case CM_PIPE:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("| ");
                    return false;
                }
                break;
            case CM_DQUO:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("\"" SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() == -2) {
                    SEND_STRING("\"\"\"\"" SS_TAP(X_LEFT) SS_TAP(X_LEFT));
                    return false;
                } else if (get_repeat_key_count() == -3) {
                    SEND_STRING(SS_LSFT(SS_TAP(X_ENT)) SS_TAP(X_UP) SS_TAP(X_END));
                    return false;
                } else if (get_repeat_key_count() <= -4) {
                    SEND_STRING(SS_LSFT(SS_TAP(X_ENT)));
                    return false;
                }
                break;
            case CM_QUES:
                if (get_repeat_key_count() == -1) {
                    SEND_STRING("  : "
                        SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
                    return false;
                }
                break;
        }
    }

    return process_repeat_key_with_alt(keycode, record, U_REPEAT, U_ALT_REPEAT);
}

#ifdef CHORDAL_HOLD
// Not needed anymore?
// The return value is true to consider the tap-hold key held or false to consider it tapped.
// bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
    // return get_chordal_hold_default(tap_hold_record, other_record);
// }
#endif  // CHORDAL_HOLD
#ifdef ACHORDION_ENABLE
static bool on_left_hand(keypos_t pos) {
#ifdef SPLIT_KEYBOARD
    return pos.row < MATRIX_ROWS / 2;
#else
    return (MATRIX_COLS > MATRIX_ROWS) ? pos.col < MATRIX_COLS / 2 : pos.row < MATRIX_ROWS / 2;
#endif
}

static bool is_left_thumb_row(keypos_t pos) {
    return pos.row == (MATRIX_ROWS / 2) - 1;
}

static bool is_right_thumb_row(keypos_t pos) {
    return pos.row == MATRIX_ROWS - 1;
}

static bool is_left_outer_col(keypos_t pos) {
    return pos.col == OUTER_COL_LEFT;
}

static bool is_right_outer_col(keypos_t pos) {
    return pos.col == OUTER_COL_RIGHT;
}

static bool is_outer_key(keyrecord_t *record) {
    if (on_left_hand(record->event.key)) {
        return is_left_thumb_row(record->event.key) || is_left_outer_col(record->event.key);
    } else {
        return is_right_thumb_row(record->event.key) || is_right_outer_col(record->event.key);
    }
}

static bool is_end_key(uint16_t keycode) {
    return IS_QK_LAYER_TAP(keycode) && QK_LAYER_TAP_GET_LAYER(keycode) == END_KEY_LAYER;
}

// The return value is true to consider the tap-hold key held or false to consider it tapped.
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    if (!IS_KEYEVENT(tap_hold_record->event) || !IS_KEYEVENT(other_record->event)) {
        return true;
    }

    if (is_outer_key(tap_hold_record) || is_outer_key(other_record)) {
        return true;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    if (is_end_key(tap_hold_keycode)) {
        return 0;
    }

    if (IS_QK_LAYER_TAP(tap_hold_keycode)) {
        return 100;
    }

    switch (tap_hold_keycode) {
        case MT_F:
            return 100;
        default:
            return 500;
    }
}

bool achordion_streak_continue(uint16_t keycode) {
    // If any mods other than shift or AltGr are held, don't continue the streak
    if (get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) return false;
    // This function doesn't get called for holds, so convert to tap version of keycodes
    if (IS_QK_MOD_TAP(keycode)) keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    if (IS_QK_LAYER_TAP(keycode)) keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    // Regular letters and punctuation continue the streak
    if (is_alpha(keycode)) return true;
    switch (keycode) {
    case KC_DOT:
    case KC_COMMA:
    case KC_QUOTE:
    case KC_SPACE:
    case U_QUOP:
        return true;
    }
    // All other keys end the streak
    return false;
}

// Disable streak detection for layer taps and shift mod-taps
uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode, uint16_t next_keycode) {
    uint16_t keycode = tap_hold_keycode;

    if (IS_QK_LAYER_TAP(keycode)) {
        // Disable streak detection on thumb LT keys.
        if (QK_LAYER_TAP_GET_LAYER(keycode) < 11) {
            return 0;
        }
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MOD_TAP(keycode)) {
        keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }

    // No streak for whole home-row-mod keys?
    // Example case this solves: fast typing code then Ctrl+Shift+I to format
    switch (keycode) {
        case CM_A:
        case CM_R:
        case CM_S:
        case CM_T:
        case CM_N:
        case CM_E:
        case CM_I:
        case CM_O:
            return 0;
    }

    if (IS_QK_MOD_TAP(next_keycode)) {
        next_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(next_keycode);
    } else if (IS_QK_LAYER_TAP(next_keycode)) {
        next_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(next_keycode);
    }

    // No streak for some AltGr producing accented characters
    switch (tap_hold_keycode) {
        case RALT_T(CM_X):
        case RALT_T(CM_V):
            switch (next_keycode) {
                case CM_E:
                case CM_I:
                case CM_O:
                case CM_L:
                case CM_U:
                case CM_Y:
                case U_QUOP:
                case CM_C:
                    return 0;
            }
            break;
        case RALT_T(CM_DOT):
        case RALT_T(CM_M):
            switch (next_keycode) {
                case CM_A:
                case CM_Q:
                case CM_W:
                case CM_F:
                case CM_P:
                case CM_Z:
                case CM_C:
                case CM_V:
                case CM_COMM:
                    return 0;
            }
            break;
        case LSFT_T(CM_C):
            if (next_keycode == CM_V || next_keycode == CM_X) {
                return 0;
            }
            break;
        case RSFT_T(CM_COMM):
            if (next_keycode == CM_M || next_keycode == CM_DOT) {
                return 0;
            }
            break;
    }

    const uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
    if (mod & MOD_LSFT) {
        return 100;
    } else {
        return 150;
    }
}

bool process_achordion_user(uint16_t keycode, keyrecord_t *record) {
    return process_achordion(keycode, record);
}
#endif  // ACHORDION_ENABLE

void layer_lock_set_user(layer_state_t state) {
    locked_layers = state;
    update_led();
}

bool process_macros_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
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

    switch (tap_keycode) {
        case KC_ESCAPE:
            if (is_caps_word_on() || get_xcase_state() != XCASE_OFF || num_word_enabled()) {
                caps_word_off();
                disable_xcase();
                disable_num_word();
                return false;
            }
            break;
        case U_NUM_WORD_TOGGLE:
            caps_word_off();
            disable_xcase();
            toggle_num_word();
            return false;
        case U_CG_TOGG:
            process_magic(CG_TOGG, record);
            set_unicode_input_mode(keymap_config.swap_lctl_lgui ? UNICODE_MODE_MACOS : UNICODE_MODE_LINUX);
            return false;
        case U_AC_TOGG:
            process_magic(AC_TOGG, record);
            return false;
    }

    return true;
}

bool process_tap_or_hold_press_key(keyrecord_t* record, uint16_t tap_keycode, uint16_t hold_keycode) {
    if (record->tap.count == 0) {  // Key is being held.
        if (record->event.pressed) {
            register_code16(hold_keycode);
        } else {
            unregister_code16(hold_keycode);
        }
    } else if (record->event.pressed) {
        tap_code16(tap_keycode);
    }
    return false;
}

#define U_UNDO  LT(0, CM_Z)
#define U_CUT   LT(0, CM_X)
#define U_COPY  LT(0, CM_C)
#define U_PASTE LT(0, CM_V)
#define U_REDO  LT(0, CM_B)

bool process_clipboard_shortcuts(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case U_UNDO:
            return process_tap_or_hold_press_key(record, C(CM_Z), KC_LGUI);
        case U_CUT:
            return process_tap_or_hold_press_key(record, C(CM_X), KC_LALT);
        case U_COPY:
            return process_tap_or_hold_press_key(record, C(CM_C), KC_LSFT);
        case U_PASTE:
            return process_tap_or_hold_press_key(record, C(KC_V), KC_RALT);
        case U_REDO:
            return process_tap_or_hold_press_key(record, C(S(CM_Z)), KC_LCTL);
    }
    return true;
}

// static const uint16_t end_keycodes = {
//     KC_SCLN,
//     KC_COMMA,
//     KC_DOT,
//     KC_SLASH,
//     KC_ONE,
// }
// static const size_t num_end_keycodes = sizeof(end_keycodes) / sizeof(end_keycodes[0]);

static uint8_t end_keys_saved_mods = 0;

bool process_end_keys(uint16_t keycode, keyrecord_t *record) {
    if (!IS_QK_LAYER_TAP(keycode)) {
        return true; // Continue default handling.
    }

    const uint16_t layer = QK_LAYER_TAP_GET_LAYER(keycode);

    if (layer != END_KEY_LAYER) {
        return true; // Continue default handling.
    }

    const uint16_t tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    // !
    if (tap_keycode == KC_F24) {
        if (record->tap.count == 0) { // Key is being held.
            if (record->event.pressed) {
                clear_all_mods();
                tap_code16(KC_END);
                set_mods(all_mods);
            }
        }

        if (record->event.pressed) {
            end_keys_saved_mods = all_mods;
            set_mods(all_mods | MOD_BIT(KC_LSFT));
            register_code16(KC_1);
        } else {
            unregister_code16(KC_1);
            set_mods(end_keys_saved_mods);
        }
        return false; // Skip default handling.
    }

    // :
    if (tap_keycode == KC_F23) {
        if (record->tap.count == 0) { // Key is being held.
            if (record->event.pressed) {
                clear_all_mods();
                tap_code16(KC_END);
                set_mods(all_mods);
            }
        }

        if (record->event.pressed) {
            end_keys_saved_mods = all_mods;
            set_mods(all_mods | MOD_BIT(KC_LSFT));
            register_code16(CM_SCLN);
        } else {
            unregister_code16(CM_SCLN);
            set_mods(end_keys_saved_mods);
        }
        return false; // Skip default handling.
    }

    if (record->tap.count == 0) { // Key is being held.
        if (record->event.pressed) {
            clear_all_mods();
            tap_code16(KC_END);
            set_mods(all_mods);

            register_code16(tap_keycode);
        } else {
            unregister_code16(tap_keycode);
        }

        return false;
    }

    return true;
}

bool process_multi_caps_word(uint16_t keycode, keyrecord_t *record, uint16_t caps_word_keycode) {
    if (keycode != caps_word_keycode) {
        return true;
    }

    if (!record->event.pressed) {
        return false;
    }

    if (is_caps_word_on() || get_xcase_state() != XCASE_OFF || num_word_enabled()) {
        caps_word_off();
        disable_xcase();
        disable_num_word();
        return false;
    }

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    const bool is_shifted    = all_mods & MOD_MASK_SHIFT;
    const bool is_controlled = all_mods & MOD_MASK_CTRL;
    const bool is_alted      = all_mods & MOD_MASK_ALT;

    if (is_shifted && is_controlled) {
        clear_all_mods();
        tap_code(KC_CAPS_LOCK);
        set_mods(mods);
    } else if (is_controlled) {
        toggle_num_word();
    } else if (is_shifted) {
        enable_xcase_with(OSM(MOD_LSFT));
    } else if (is_alted) {
        enable_xcase();
    } else {
        caps_word_toggle();
    }

    return false;
}

void num_word_user(bool enabled) {
    update_led();
}

uint16_t SELECT_WORD_KEYCODE = U_SEL_WORD;

bool process_select_word_user(uint16_t keycode, keyrecord_t *record) {
    const int8_t repeat_key_count = get_repeat_key_count();

    if (repeat_key_count == 0 && !process_select_word(keycode, record)) {
        return false;
    }

    if (keycode != U_SEL_WORD || !record->event.pressed) {
        return true;
    }

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if (all_mods & MOD_MASK_SHIFT || all_mods & MOD_MASK_CTRL) {
        clear_all_mods();
        if (repeat_key_count > 0) {
            SEND_STRING(SS_LSFT(SS_TAP(X_DOWN)));
        } else {
            SEND_STRING(SS_LSFT(SS_TAP(X_UP)));
        }
        set_mods(mods);
    } else {
        if (repeat_key_count > 0) {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RGHT))));
        } else {
            SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_LEFT))));
        }
    }

    return false;
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

bool process_colemak_fr(uint16_t keycode, keyrecord_t *record, uint16_t toggle_keycode) {
    if (!record->event.pressed) {
        return true;
    }

    if (keycode == toggle_keycode) {
        user_config.colemak_fr ^= 1;
        eeconfig_update_user(user_config.raw);
        return false;
    }

    if (!user_config.colemak_fr) {
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
        // grave
        case CM_A:
            return send_key_with_ralt('a', 'r', mods, shifted);
        case CM_P:
            return send_key_with_ralt('e', 'r', mods, shifted);
        case CM_L:
            return send_key_with_ralt('u', 'r', mods, shifted);
        // circonflexe
        case CM_Q:
            return send_key_with_ralt('a', 'x', mods, shifted);
        case CM_F:
            return send_key_with_ralt('e', 'x', mods, shifted);
        case CM_I:
            return send_key_with_ralt('i', 'x', mods, shifted);
        case CM_O:
            return send_key_with_ralt('o', 'x', mods, shifted);
        case CM_U:
            return send_key_with_ralt('u', 'x', mods, shifted);
        // tréma
        case CM_W:
            return send_key_with_ralt('e', 'd', mods, shifted);
        case CM_Y:
            return send_key_with_ralt('i', 'd', mods, shifted);
        case CM_SCLN:
            return send_key_with_ralt('u', 'd', mods, shifted);
        default:
            return true;
    }
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
    static short dot_count = 0;
    static uint16_t last_keycode = KC_NO;
    static fast_timer_t timer = 0;

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if (!all_mods && (is_alpha(tap_keycode) || tap_keycode == U_QUOP || tap_keycode == CM_SLSH)) {
        last_keycode = KC_NO;

        const bool shifted_ralted = (comma_count == 2 && dot_count == 1)
            || (comma_count == 1 && dot_count == 2);
        const bool shifted = (comma_count == 1 && dot_count == 0) || shifted_ralted;
        const bool ralted = (comma_count == 1 && dot_count == 1) || shifted_ralted;

        if ((!shifted && !ralted) || timer_elapsed_fast(timer) > ONESHOT_TIMEOUT) {
            comma_count = 0;
            dot_count = 0;
            return true;
        }

        char backspace_str[4];
        const size_t total = comma_count + dot_count;
        memset(backspace_str, '\b', total);
        backspace_str[total] = '\0';
        SEND_STRING_DELAY(backspace_str, 2);
        comma_count = 0;
        dot_count = 0;

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
        case CM_COMM:
            timer = timer_read_fast();
            ++comma_count;

            // ,, -> ,
            if (last_keycode == CM_COMM && comma_count == 2 && dot_count == 0) {
                last_keycode = KC_NO;
                comma_count = 0;
                dot_count = 0;
                return false;
            }
            break;
        case CM_DOT:
            timer = timer_read_fast();
            ++dot_count;
            break;
        default:
            if (comma_count > 0) {
                comma_count = 0;
            }
            if (dot_count > 0) {
                dot_count = 0;
            }
    }

    last_keycode = tap_keycode;

    return true;
}

static bool right_pressed = false;
static bool down_pressed  = false;
static bool left_pressed  = false;

static bool ctl_down = false;
static bool sft_down = false;
static bool alt_down = false;

bool process_nav_override(uint16_t keycode, keyrecord_t *record) {
    bool is_nav  = get_highest_layer(layer_state) == 5;
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

bool within_word(void) {
    const uint8_t current_word_length = get_current_word_length();
    if (!current_word_length) {
        return false;
    }
    const char c = get_current_word()[current_word_length - 1];
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '\'';
}

// Based on https://getreuer.info/posts/keyboards/macros3/index.html#quopostrokey
static bool process_quopostrokey(uint16_t keycode, keyrecord_t *record) {
    static uint16_t pressed_keycode = KC_NO;

    if (keycode == U_QUOP) {
        if (record->event.pressed) {
            const uint8_t mods     = get_mods();
            const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

            if ((all_mods & MOD_BIT(KC_RALT))) {
                pressed_keycode = CM_0;
                register_code(pressed_keycode);
                quopostrokey_is_quote = false;
                return true;
            }

            if (all_mods & MOD_MASK_SHIFT) {
                pressed_keycode = CM_QUOT;
                register_code(pressed_keycode);
                quopostrokey_is_quote = true;
                return true;
            }

            if (all_mods & MOD_MASK_CTRL) {
                clear_all_mods();
                pressed_keycode = CM_QUOT;
                register_code(pressed_keycode);
                quopostrokey_is_quote = false;
                set_mods(mods);
                return true;
            }

            if (!within_word()) {
                SEND_STRING("\"\"" SS_TAP(X_LEFT));
                quopostrokey_is_quote = true;
                return false;
            } else {
                quopostrokey_is_quote = false;
            }

            pressed_keycode = CM_QUOT;
            register_code(pressed_keycode);
            return true;
        } else if (pressed_keycode != KC_NO) {
            unregister_code(pressed_keycode);
            pressed_keycode = KC_NO;
            return true;
        }

        return false;
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

// Generates a pseudorandom value in 0-255.
static uint8_t simple_rand(void) {
    static uint16_t random = 0;
    if (random == 0) {
        random = timer_read();
    }
    random *= UINT16_C(36563);
    return (uint8_t)(random >> 8);
}

// Based on https://getreuer.info/posts/keyboards/macros3/index.html#random-emojis
void send_approve(bool random) {
    static const char *emojis[] = {
        "👍", // Thumbs Up
        "🌞", // Sun with Face
        "👏", // Clapping Hands
        "🙌", // Raising Hands
        "💪", // Flexed Biceps
        "🤝", // Handshake
        "🎉", // Party Popper
        "✨", // Sparkles
        "🌟", // Plowing Star
        "💯", // Hundred Points
        "👌", // OK Hand
        "👾", // Alien Monster
    };
    const int NUM_EMOJIS = sizeof(emojis) / sizeof(*emojis);

    if (!random) {
        send_unicode_string(emojis[0]);
        return;
    }

    // Pseudorandomly pick an index between 0 and NUM_EMOJIS - 2.
    uint8_t index = ((NUM_EMOJIS - 1) * simple_rand()) >> 8;

    // Don't pick the same emoji twice in a row.
    static uint8_t last_index = 0;
    if (index >= last_index) {
        ++index;
    }
    last_index = index;

    // Produce the emoji.
    send_unicode_string(emojis[index]);
}

void send_face(bool random) {
    static const char *emojis[] = {
        "🙂", // Slightly Smiling Face
        "😊", // Smiling Face with Smiling Eyes
        "😇", // Smiling Face with Halo
        "🥰", // Smiling Face with Hearts
        "😍", // Smiling Face with Heart-Eyes
        "😀", // Grinning Face
        "😃", // Grinning Face with Big Eyes
        "😄", // Grinning Face with Smiling Eyes
        "😁", // Beaming Face with Smiling Eyes
        "😆", // Grinning Squinting Face
        "😅", // Grinning Face with Sweat
        "🤣", // Rolling on the Floor Laughing
        "😂", // Face with Tears of Joy
        "🙃", // Upside-Down Face
        "😉", // Winking Face
        "🤩", // Star-Struck
        // "😘", // Face Blowing a Kiss
        // "😗", // Kissing Face
        // "😚", // Kissing Face with Closed Eyes
        // "😙", // Kissing Face with Smiling Eyes
    };
    const int NUM_EMOJIS = sizeof(emojis) / sizeof(*emojis);

    if (!random) {
        send_unicode_string(emojis[0]);
        return;
    }

    // Pseudorandomly pick an index between 0 and NUM_EMOJIS - 2.
    uint8_t index = ((NUM_EMOJIS - 1) * simple_rand()) >> 8;

    // Don't pick the same emoji twice in a row.
    static uint8_t last_index = 0;
    if (index >= last_index) {
        ++index;
    }
    last_index = index;

    // Produce the emoji.
    send_unicode_string(emojis[index]);
}

void send_please(bool random) {
    static const char *emojis[] = {
        "🙏", // Folded Hands
        "🙇", // Person Bowing
        "🥺", // Pleading Face
        "😳", // Flushed Face
        "😭", // Loudly Crying Face
        "😱", // Face Screaming in Fear
        "😢", // Crying Face
        "🤭", // Face with Hand Over Mouth
        // "🙈", // See-No-Evil Monkey
        // "🙊", // Speak-No-Evil Monkey
    };
    const int NUM_EMOJIS = sizeof(emojis) / sizeof(*emojis);

    if (!random) {
        send_unicode_string(emojis[0]);
        return;
    }

    // Pseudorandomly pick an index between 0 and NUM_EMOJIS - 2.
    uint8_t index = ((NUM_EMOJIS - 1) * simple_rand()) >> 8;

    // Don't pick the same emoji twice in a row.
    static uint8_t last_index = 0;
    if (index >= last_index) {
        ++index;
    }
    last_index = index;

    // Produce the emoji.
    send_unicode_string(emojis[index]);
}

void send_food(bool random) {
    static const char *emojis[] = {
        "🍴", // Fork and Knife
        "🍔", // Hamburger
        "🍟", // French Fries
        "🍕", // Pizza
        "🌭", // Hot Dog
        "🥪", // Sandwich
        "🌮", // Taco
        "🌯", // Burrito
        "🥙", // Stuffed Flatbread
        "🍳", // Cooking (Egg in a pan)
        "🥘", // Shallow Pan of Food (often Paella)
        "🍲", // Pot of Food (could be stew or soup)
        "🍛", // Curry Rice
        "🍜", // Steaming Bowl (noodles)
        "🍝", // Spaghetti
        "🍠", // Roasted Sweet Potato
        "🍢", // Oden
        "🍣", // Sushi
        "🍤", // Fried Shrimp
        "🍥", // Fish Cake with Swirl
        "🥮", // Moon Cake
        "🍱", // Bento Box
        "🍚", // Cooked Rice
        "🍘", // Rice Cracker
        "🍙", // Rice Ball
        "🍧", // Shaved Ice
        "🍨", // Ice Cream
        "🍩", // Doughnut
        "🍪", // Cookie
        "🎂", // Birthday Cake
        "🍰", // Shortcake
        "🧁", // Cupcake
        "🥧", // Pie
        "🍫", // Chocolate Bar
        "🍬", // Candy
        "🍭", // Lollipop
        "🍮", // Custard
        "🍯", // Honey Pot
        "🥗", // Green Salad
    };
    const int NUM_EMOJIS = sizeof(emojis) / sizeof(*emojis);

    if (!random) {
        send_unicode_string(emojis[0]);
        return;
    }

    // Pseudorandomly pick an index between 0 and NUM_EMOJIS - 2.
    uint8_t index = ((NUM_EMOJIS - 1) * simple_rand()) >> 8;

    // Don't pick the same emoji twice in a row.
    static uint8_t last_index = 0;
    if (index >= last_index) {
        ++index;
    }
    last_index = index;

    // Produce the emoji.
    send_unicode_string(emojis[index]);
}

void send_monkey(bool random) {
    static const char *emojis[] = {
        "🐵", // Monkey Face
        "🙈", // See-No-Evil Monkey
        "🙉", // Hear-No-Evil Monkey
        "🙊", // Speak-No-Evil Monkey
        "🐒", // Monkey
    };
    const int NUM_EMOJIS = sizeof(emojis) / sizeof(*emojis);

    if (!random) {
        send_unicode_string(emojis[0]);
        return;
    }

    // Pseudorandomly pick an index between 0 and NUM_EMOJIS - 2.
    uint8_t index = ((NUM_EMOJIS - 1) * simple_rand()) >> 8;

    // Don't pick the same emoji twice in a row.
    static uint8_t last_index = 0;
    if (index >= last_index) {
        ++index;
    }
    last_index = index;

    // Produce the emoji.
    send_unicode_string(emojis[index]);
}

void send_emoji(void) {
    const uint8_t mods         = get_mods();
    const uint8_t all_mods     = mods | get_weak_mods() | get_oneshot_mods();
    const bool    is_shifted   = all_mods & MOD_MASK_SHIFT;
    const bool    is_controled = all_mods & MOD_MASK_CTRL;
    const bool    is_alted     = all_mods & MOD_MASK_ALT;
    const bool    is_guied     = all_mods & MOD_MASK_GUI;

    clear_all_mods();
    if (is_guied) {
        send_monkey(is_alted);
    } else if (is_controled && is_shifted) {
        send_food(is_alted);
    } else if (is_controled) {
        send_please(is_alted);
    } else if (is_shifted) {
        send_face(is_alted);
    } else {
        send_approve(is_alted);
    }
    set_mods(mods);
}

bool process_emoji(uint16_t keycode, keyrecord_t *record) {
    if (keycode != U_EMOJI) {
        return true;
    }

    if (record->event.pressed) {
        send_emoji();
    }

    return false;
}

bool process_layer_lock_user(uint16_t keycode, keyrecord_t *record, uint16_t layer_lock_keycode) {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (keycode == layer_lock_keycode && current_layer == 0) {
        if (record->event.pressed) {
            send_emoji();
        }
        return false;
    }

    // Unlock all layers if any layer is locked (ensures key has toggle effect).
    if (keycode == layer_lock_keycode && locked_layers != 0 && record->event.pressed) {
        layer_lock_all_off();
        layer_clear();
        update_led();
        locked_layers = 0;
        return false;
    }

    // Disable tap-hold holds if any layer is locked.
    if (locked_layers != 0) {
        if (IS_QK_MOD_TAP(keycode)) {
            const uint16_t tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            if (record->event.pressed) {
                register_code(tap_keycode);
            } else {
                unregister_code(tap_keycode);
            }
            return false;
        } else if (IS_QK_LAYER_TAP(keycode)) {
            const uint16_t tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            if (record->event.pressed) {
                register_code(tap_keycode);
            } else {
                unregister_code(tap_keycode);
            }
            return false;
        }
    }

    // Layer overrides
    if (keycode == layer_lock_keycode && record->event.pressed) {
        switch (current_layer) {
            case 2:
                layer_off(2);
                layer_on(9);
                break;
        }
    }

    return process_layer_lock(keycode, record, layer_lock_keycode);
}

// https://getreuer.info/posts/keyboards/macros3/index.html#a-mouse-jiggler
void process_mouse_jiggler(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        static deferred_token token  = INVALID_DEFERRED_TOKEN;
        static report_mouse_t report = {0};
        if (token) {
            // If jiggler is currently running, stop when any key is pressed.
            cancel_deferred_exec(token);
            token  = INVALID_DEFERRED_TOKEN;
            report = (report_mouse_t){}; // Clear the mouse.
            host_mouse_send(&report);
        } else if (keycode == U_JIGGLE) {
            uint32_t jiggler_callback(uint32_t trigger_time, void *cb_arg) {
                // Deltas to move in a circle of radius 20 pixels over 32 frames.
                static const int8_t deltas[32] = {0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0, 0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
                static uint8_t      phase      = 0;
                // Get x delta from table and y delta by rotating a quarter cycle.
                report.x = deltas[phase];
                report.y = deltas[(phase + 8) & 31];
                phase    = (phase + 1) & 31;
                host_mouse_send(&report);
                return 16; // Call the callback every 16 ms.
            }

            token = defer_exec(1, jiggler_callback, NULL); // Schedule callback.
        }
    }
}

bool num_layer_override(uint16_t keycode, keyrecord_t *record) {
    const uint8_t current_layer = get_highest_layer(layer_state);

    if (current_layer == _NUM || current_layer == _NUM2) {
        // Three dots -> single dot
        if (keycode == U_THREE_DOTS) {
            if (record->event.pressed) {
                register_code16(KC_DOT);
            } else {
                unregister_code16(KC_DOT);
            }
            return false;
        }
        // Comma
        if (keycode == U_OS_RSFT) {
            if (record->event.pressed) {
                register_code16(KC_COMMA);
            } else {
                unregister_code16(KC_COMMA);
            }
            return false;
        }
    }

    return true;
}

bool process_fix_ubuntu_dock_switch(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    static bool in_switch = false;
    static deferred_token token = INVALID_DEFERRED_TOKEN;
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

    if (!in_switch) {
        const uint8_t mods         = get_mods();
        const uint8_t all_mods     = mods | get_weak_mods() | get_oneshot_mods();
        const bool    is_guied     = all_mods & MOD_MASK_GUI;

        if (is_guied && tap_keycode >= KC_1 && tap_keycode <= KC_0) {
            in_switch = true;
        }
    } else if (token == INVALID_DEFERRED_TOKEN) {
        if (tap_keycode == KC_ESCAPE) {
            in_switch = false;
        } else if (tap_keycode == KC_ENTER || tap_keycode == KC_KP_ENTER) {
            in_switch = false;
            const uint32_t ubuntu_dock_fix_callback(uint32_t trigger_time, void *cb_arg) {
                tap_code(KC_ESCAPE);
                if (token != INVALID_DEFERRED_TOKEN) {
                    cancel_deferred_exec(token);
                    token  = INVALID_DEFERRED_TOKEN;
                }
                return 100;
            }

            token = defer_exec(500, ubuntu_dock_fix_callback, NULL);
        } else if (tap_keycode != KC_UP && tap_keycode != KC_DOWN
                && tap_keycode != KC_LEFT && tap_keycode != KC_RIGHT) {
            in_switch = false;
        }
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#if defined(MOUSEKEY_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    process_mouse_jiggler(keycode, record);
#endif
#ifdef ACHORDION_ENABLE
    if (!process_achordion_user(keycode, record)) {
        return false;
    }
#endif  // ACHORDION_ENABLE
    if (!process_repeat_key_with_alt_user(keycode, record, U_REPEAT, U_ALT_REPEAT)) {
        return false;
    }
    if (!process_layer_lock_user(keycode, record, U_LAYER_LOCK)) {
        return false;
    }
    if (!process_colemak_fr(keycode, record, U_CM_TOGG)) {
        return false;
    }
    if (!process_punctuation_mod(keycode, record, U_PUNCTUATION_MOD_TOGG)) {
        return false;
    }
    if (!num_layer_override(keycode, record)) {
        return false;
    }
    if (!process_oneshot(keycode, record)) {
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
    if (!process_quopostrokey(keycode, record)) {
        return false;
    }
    if (!process_emoji(keycode, record)) {
        return false;
    }
    if (!process_sentence_case(keycode, record)) {
        return false;
    }
    if (!process_macros_user(keycode, record)) {
        return false;
    }
    if (!process_clipboard_shortcuts(keycode, record)) {
        return false;
    }
    if (!process_end_keys(keycode, record)) {
        return false;
    }
    if (!process_multi_caps_word(keycode, record, U_CAPS_WORD_TOGGLE)) {
        return false;
    }
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    if (!process_num_word(keycode, record)) {
        return false;
    }
    if (!process_autocomplete(keycode, record)) {
        return false;
    }
    if (!process_nav_override(keycode, record)) {
        return false;
    }

#ifndef AUTOCORRECT_ENABLE
    if (!process_autocorrection(keycode, record)) {
        return false;
    }
#endif

#ifdef MOUSEKEY_ENABLE
    if (!process_mouse_turbo_click(keycode, record, U_TURBO_CLICK)) {
        return false;
    }
#endif

    if (!process_fix_ubuntu_dock_switch(keycode, record)) {
        return false;
    }

    return true;
}

void housekeeping_task_user(void) {
#ifdef ACHORDION_ENABLE
    achordion_task();
#endif  // ACHORDION_ENABLE
    layer_lock_task();
    select_word_task();
    sentence_case_task();
}
