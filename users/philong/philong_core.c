// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "philong_core.h"

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

user_config_t user_config;

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

    if (is_quopostrokey_target(keycode, record) && user_config.quopostrokey && IS_KEYEVENT(record->event) && is_layer(LAYER_BASE)) {
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
    // Punctuation mode must run before the French processing: it
    // turns a `;`/`,` prefix into oneshot Shift/AltGr mods, which
    // process_variant_french_accents() then picks up to produce the French accents.
    if (!process_punctuation_mod(keycode, record, U_PUNCTUATION_MOD_TOGG)) {
        return false;
    }
    if (!process_variant_french_accents(keycode, record)) {
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
    user_config.fr_accent = true;
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
