// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "qmk_settings.h"

#include "quantum/keymap_extras/sendstring_colemak.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                            KC_LGUI, MO(1), KC_SPC,           KC_ENT,  KC_RCTL,  KC_RALT
    ),
    [1] = LAYOUT(
        KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_PGUP, KC_PGDN, KC_HOME, KC_END,  KC_DEL,  KC_F12,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LBRC, KC_RBRC,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS
    )
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        '*', '*', '*', '*', '*', '*',  '*', '*', '*', '*', '*', '*',
        '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
        '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
        '*', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', '*',
                       '*', '*', '*',  '*', '*', '*'
    );

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
};

// KC_A ... KC_Z -> Colemak
bool is_alpha(const uint16_t keycode) {
    return (KC_A <= keycode && keycode <= KC_O) // Exclude CM_SCLN == KC_P
           || (keycode == CM_O)                 // Include CM_O == KC_SCLN
           || (KC_Q <= keycode && keycode <= KC_Z);
}

void clear_all_mods(void) {
    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();
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
        case CM_DOT:
        case CM_COMM:
        case CM_SCLN:
        case CM_SLSH:
            return true;
    }

    return false;
}

uint16_t get_flow_tap_term(
    uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {

    const uint16_t tap_keycode = get_tap_keycode(keycode);

    // LGui+L
    if (prev_keycode == LGUI_T(CM_A) && tap_keycode == CM_L) {
        return QS.flow_tap_term * 4;
    }

    // home-row-mods
    switch (tap_keycode) {
        case CM_A:
        case CM_R:
        case CM_S:
        case CM_T:
        case CM_N:
        case CM_E:
        case CM_I:
        case CM_O:
            return 0;  // Disable filter for these keys.
    }

    // AltGr producing accented characters
    switch (prev_keycode) {
        case RALT_T(CM_X):
        case RALT_T(CM_V):
            switch (tap_keycode) {
                case CM_E:
                case CM_I:
                case CM_O:
                case CM_L:
                case CM_U:
                case CM_Y:
                case CM_QUOT:
                    return 0;
            }
            break;
        case RALT_T(CM_DOT):
        case RALT_T(CM_M):
            switch (tap_keycode) {
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
            if (tap_keycode == CM_V || tap_keycode == CM_X) {
                return 0;
            }
            break;
        case RSFT_T(CM_COMM):
            if (tap_keycode == CM_M || tap_keycode == CM_DOT) {
                return 0;
            }
            break;
    }

    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        return QS.flow_tap_term;
    }

    return 0;  // Disable Tap Flow.
}

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
            return process_tap_or_hold_press_key(record, C(CM_X), KC_RALT);
        case U_COPY:
            return process_tap_or_hold_press_key(record, C(CM_C), KC_LSFT);
        case U_PASTE:
            return process_tap_or_hold_press_key(record, C(KC_V), KC_RALT);
        case U_REDO:
            return process_tap_or_hold_press_key(record, C(S(CM_Z)), KC_RCTL);
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
const char SRCHSEL[] PROGMEM               = SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER);
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
    const uint16_t tap_keycode = get_tap_keycode(keycode);

    if (tap_keycode == KC_ESCAPE && is_caps_word_on()) {
        caps_word_off();
        return false;
    }

    return true;
}

bool process_layer_lock_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t current_layer = get_highest_layer(layer_state);

    if (current_layer == 0 && keycode == QK_LAYER_LOCK) {
        return process_repeat_key(QK_ALT_REPEAT_KEY, record);
    }

    return true;
}

bool is_nav_layer(void) {
    return get_highest_layer(layer_state) == 2;
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

bool process_punctuation_mod(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    // if (keycode == toggle_keycode) {
    //     user_config.punctuation_mod ^= 1;
    //     eeconfig_update_user(user_config.raw);
    //     return false;
    // }

    // if (!user_config.punctuation_mod) {
    //     return true;
    // }

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

    if (!all_mods && (is_alpha(tap_keycode) || tap_keycode == CM_QUOT || tap_keycode == CM_SLSH || tap_keycode == CM_SCLN)) {
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
        SEND_STRING(backspace_str);
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

            if (dot_count > 0) {
                dot_count = 0;
            }

            // ,, -> ,,
            if (last_keycode == CM_COMM && comma_count == 2 && dot_count == 0) {
                last_keycode = KC_NO;
                comma_count = 0;
                dot_count = 0;
                tap_code(KC_COMMA);
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_shift_backspace_delete(keycode, record)) {
        return false;
    }
    if (!process_select_word_user(keycode, record)) {
        return false;
    }
    if (!process_joinln(keycode, record, U_JOIN_LN)) {
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
    if (!process_layer_lock_user(keycode, record)) {
        return false;
    }
    if (!process_nav_override(keycode, record)) {
        return false;
    }
    if (!process_punctuation_mod(keycode, record)) {
        return false;
    }

    return true;
}

void keyboard_post_init_user(void) {
#ifdef AUTOCORRECT_ENABLE
    if (!autocorrect_is_enabled()) {
        autocorrect_enable();
    }
#endif
}

void eeconfig_init_user(void) { // EEPROM is getting reset!
#ifdef UNICODE_ENABLE
    set_unicode_input_mode(UNICODE_MODE_LINUX);
#endif

#ifdef AUTOCORRECT_ENABLE
    autocorrect_enable();
#endif
}
