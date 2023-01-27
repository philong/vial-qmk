// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
    #include "print.h"
#endif

#include "features/achordion.h"
#include "features/layer_lock.h"
#include "features/select_word.h"
#include "features/repeat_key.h"
#include "features/sentence_case.h"
#include "features/autocorrection.h"

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │GUI├───┐           ┌───┤Alt│
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤Bsp│   │Ent├───┘
      *                       └───┘   └───┘
      */
    [0] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, MT_A,    MT_S,    MT_D,    MT_F,    KC_G,                           KC_H,    MT_J,    MT_K,    MT_L,    MT_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    MT_X,    KC_C,    KC_V,    KC_B,                           KC_N,    KC_M,    KC_COMM, MT_DOT,  KC_SLSH, KC_RSFT,
                                            KC_LGUI, KC_SPC, KC_BSPC,       KC_ENT,  KC_SPC,  KC_RALT
    ),

    [1] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [4] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [5] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [6] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    )
};

enum user_keycode {
    U_LAYER_LOCK = USER00,
    U_CAPS_WORD_TOGGLE,
    U_SEL_WORD,
    U_JOIN_LN,
    U_REPEAT,
    U_REV_REPEAT,
    U_CURRENT_DIRECTORY,
    U_UP_DIRECTORY,
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
    U_USERNAME,
    U_OS_LCTL,
    U_OS_LSFT,
    U_OS_LALT,
    U_OS_LGUI,
    U_OS_RCTL,
    U_OS_RSFT,
    U_OS_RALT,
    U_OS_RGUI,
};

enum oneshot_states {
    ONESHOT_INITIAL,
    ONESHOT_CONSUMED,
    ONESHOT_DONE,
};

int oneshot_state = ONESHOT_INITIAL;
fast_timer_t oneshot_timer = 0;

bool oneshot_state_lctl = false;
bool oneshot_state_lsft = false;
bool oneshot_state_lalt = false;
bool oneshot_state_lgui = false;
bool oneshot_state_rctl = false;
bool oneshot_state_rsft = false;
bool oneshot_state_ralt = false;
bool oneshot_state_rgui = false;

bool oneshot_pressed_lctl = false;
bool oneshot_pressed_lsft = false;
bool oneshot_pressed_lalt = false;
bool oneshot_pressed_lgui = false;
bool oneshot_pressed_rctl = false;
bool oneshot_pressed_rsft = false;
bool oneshot_pressed_ralt = false;
bool oneshot_pressed_rgui = false;

bool oneshot_primed(void) {
    return oneshot_state_lctl || oneshot_state_lsft || oneshot_state_lalt || oneshot_state_lgui
        || oneshot_state_rctl || oneshot_state_rsft || oneshot_state_ralt || oneshot_state_rgui;
}

bool oneshot_pressed(void) {
    return oneshot_pressed_lctl || oneshot_pressed_lsft || oneshot_pressed_lalt || oneshot_pressed_lgui
        || oneshot_pressed_rctl || oneshot_pressed_rsft || oneshot_pressed_ralt || oneshot_pressed_rgui;
}

bool oneshot_active(void) {
    return oneshot_primed() || oneshot_pressed();
}

// Mod-tap, RAlt mod and Colemak
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    return IS_MT(keycode) || (keycode >= QK_RALT && keycode < QK_RGUI) || keycode == KC_P;
}

// Colemak
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_O:
        case KC_Q ... KC_Z:
        case KC_SCOLON:
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

void set_led(bool active) {
    uint16_t level = active ? LED_PIN_ON_STATE : ~LED_PIN_ON_STATE;
    writePin(USER_LED_PIN, level);
}

bool caps_word_active = false;
bool in_high_layer = false;
bool layer_locked = false;
bool sentence_primed = false;
bool dynamic_macro_recording = false;

bool led_enabled_user(void) {
    return caps_word_active || in_high_layer || layer_locked || sentence_primed || dynamic_macro_recording || oneshot_active();
}

void update_led(void) {
    set_led(led_enabled_user());
}

void caps_word_set_user(bool active) {
    caps_word_active = active;
    update_led();

    if (active) {
        oneshot_state_lsft = false;
        oneshot_state_rsft = false;
    }
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    in_high_layer = get_highest_layer(state) != 0;
    update_led();
    return state;
}

bool led_update_user(led_t led_state) {
    if (led_enabled_user()) {
        set_led(true);
        return false;
    }
    return true;
}

void layer_lock_set_user(layer_state_t locked_layers) {
    layer_locked = locked_layers != 0;
    update_led();
}

void sentence_case_primed(bool primed) {
    sentence_primed = primed;
    update_led();
}

void dynamic_macro_record_start_user(void) {
    dynamic_macro_recording = true;
    update_led();
}

void dynamic_macro_record_end_user(int8_t direction) {
    dynamic_macro_recording = false;
    update_led();
}

// Colemak
bool sentence_case_check_ending(const uint16_t* buffer) {
#if SENTENCE_CASE_BUFFER_SIZE >= 5
  // Don't consider the abbreviations "vs." and "etc." to end the sentence.
  if (SENTENCE_CASE_JUST_TYPED(KC_SPC, KC_V, KC_D, KC_DOT) ||
      SENTENCE_CASE_JUST_TYPED(KC_SPC, KC_K, KC_F, KC_C, KC_DOT)) {
    return false;  // Not a real sentence ending.
  }
#endif  // SENTENCE_CASE_BUFFER_SIZE >= 5
  return true;  // Real sentence ending; capitalize next letter.
}

bool autocorrection_is_letter(uint16_t keycode) {
    return (KC_A <= keycode && keycode <= KC_Z && keycode != KC_P) || keycode == KC_SCOLON;
}

bool autocorrection_is_boundary(uint16_t keycode) {
    return (KC_1 <= keycode && keycode <= KC_SLSH && keycode != KC_SCOLON) || keycode == KC_P;
}

// Colemak
char sentence_case_press_user(uint16_t keycode, keyrecord_t *record, uint8_t mods) {
    if ((mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
        const bool shifted = mods & MOD_MASK_SHIFT;
        switch (keycode) {
            case KC_LCTL ... KC_RGUI: // Mod keys.
                return '\0';              // These keys are ignored.

            case KC_A ... KC_O:
            case KC_Q ... KC_Z:
            case KC_SCOLON:
                return 'a'; // Letter key.

            case KC_DOT: // . is punctuation, Shift . is a symbol (>)
                return !shifted ? '.' : '#';
            case KC_1:
            case KC_SLSH:
                return shifted ? '.' : '#';
            case KC_2 ... KC_0:       // 2 3 4 5 6 7 8 9 0
            case KC_MINS:  // - = [ ] ; backslash
            case KC_EQUAL:
            case KC_LEFT_BRACKET:
            case KC_RIGHT_BRACKET:
            case KC_P:
            case KC_BACKSLASH:

            case KC_GRAVE:
            case KC_COMMA:
                return '#';           // Symbol key.

            case KC_SPC:
                return ' '; // Space key.

            case KC_QUOT:
                return '\'';  // Quote key.
        }
    }

    // Otherwise clear Sentence Case to initial state.
    sentence_case_clear();
    return '\0';
}

bool process_oneshot_trigger(uint16_t keycode, keyrecord_t *record, uint16_t trigger_key, uint16_t mod_key, bool *oneshot_key_state, bool *oneshot_pressed) {
    if (keycode != trigger_key) {
        return true;
    }

    if (record->event.pressed) {
        oneshot_timer = timer_read_fast();
        register_code(mod_key);
        (*oneshot_key_state) = !(*oneshot_key_state);
        (*oneshot_pressed) = true;
    } else {
        unregister_code(mod_key);
        if (oneshot_state == ONESHOT_INITIAL) {
            const bool is_hold = timer_elapsed_fast(oneshot_timer) > get_tapping_term(keycode, record);
            if (is_hold) {
                (*oneshot_key_state) = false;
            }
        }
        (*oneshot_pressed) = false;
    }
    update_led();

    return false;
}

bool process_oneshot_initial(uint16_t keycode, keyrecord_t *record, uint16_t trigger_key, uint16_t mod_key, bool *oneshot_key_state) {
    if ((*oneshot_key_state) && record->event.pressed) {
        register_code(mod_key);
        return true;
    }

    return false;
}

bool process_oneshot_initial_dual(uint16_t keycode, keyrecord_t *record, uint16_t trigger_key_r, uint16_t mod_key_r, bool *oneshot_key_state_r, uint16_t trigger_key_l, uint16_t mod_key_l, bool *oneshot_key_state_l) {
    if (((*oneshot_key_state_l) || (*oneshot_key_state_r)) && record->event.pressed) {
        if ((*oneshot_key_state_l)) {
            register_code(mod_key_l);
        } else {
            register_code(mod_key_r);
        }
        return true;
    }

    return false;
}

void process_oneshot_done_key(uint16_t mod_key, bool *oneshot_key_state, bool oneshot_pressed) {
    if ((*oneshot_key_state)) {
        if (!oneshot_pressed) {
            unregister_code(mod_key);
        }
        (*oneshot_key_state) = false;
        update_led();
    }
}

void process_oneshot_done_key_dual(uint16_t mod_key_l, bool *oneshot_key_state_l, bool oneshot_pressed_l,
                                   uint16_t mod_key_r, bool *oneshot_key_state_r, bool oneshot_pressed_r) {
    if ((*oneshot_key_state_l) || (*oneshot_key_state_r)) {
        if (!oneshot_pressed_l) {
            unregister_code(mod_key_l);
        }
        if (!oneshot_pressed_r) {
            unregister_code(mod_key_r);
        }
        (*oneshot_key_state_l) = false;
        (*oneshot_key_state_r) = false;
        update_led();
    }
}

void process_oneshot_done(uint16_t keycode, keyrecord_t *record) {
    if (oneshot_state != ONESHOT_DONE) {
        return;
    }

    process_oneshot_done_key_dual(KC_LCTL, &oneshot_state_lctl, oneshot_pressed_lctl, KC_RCTL, &oneshot_state_rctl, oneshot_pressed_rctl);
    process_oneshot_done_key_dual(KC_LSFT, &oneshot_state_lsft, oneshot_pressed_lsft, KC_RSFT, &oneshot_state_rsft, oneshot_pressed_rsft);
    process_oneshot_done_key(KC_LALT, &oneshot_state_lalt, oneshot_pressed_lalt);
    process_oneshot_done_key(KC_RALT, &oneshot_state_ralt, oneshot_pressed_ralt);
    process_oneshot_done_key_dual(KC_LGUI, &oneshot_state_lgui, oneshot_pressed_lgui, KC_RGUI, &oneshot_state_rgui, oneshot_pressed_rgui);
    oneshot_state = ONESHOT_INITIAL;
}

bool is_oneshot_trigger(uint16_t keycode) {
    switch (keycode) {
        case U_OS_LCTL:
        case U_OS_LSFT:
        case U_OS_LALT:
        case U_OS_LGUI:
        case U_OS_RCTL:
        case U_OS_RSFT:
        case U_OS_RALT:
        case U_OS_RGUI:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored(uint16_t keycode) {
    if (IS_LT(keycode) || IS_MOD(keycode)) {
        return true;
    }

    switch (keycode) {
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
        case QK_TO ... QK_TO_MAX:
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            return true;
        default:
            return false;
    }
}

bool process_oneshot(uint16_t keycode, keyrecord_t *record) {
    if (is_oneshot_ignored(keycode)) {
        return true;
    }

    if (!process_oneshot_trigger(keycode, record, U_OS_LCTL, KC_LCTL, &oneshot_state_lctl, &oneshot_pressed_lctl)) { return true; }
    if (!process_oneshot_trigger(keycode, record, U_OS_LSFT, KC_LSFT, &oneshot_state_lsft, &oneshot_pressed_lsft)) { return true; }
    if (!process_oneshot_trigger(keycode, record, U_OS_LALT, KC_LALT, &oneshot_state_lalt, &oneshot_pressed_lalt)) { return true; }
    if (!process_oneshot_trigger(keycode, record, U_OS_LGUI, KC_LGUI, &oneshot_state_lgui, &oneshot_pressed_lgui)) { return true; }
    if (!process_oneshot_trigger(keycode, record, U_OS_RCTL, KC_RCTL, &oneshot_state_rctl, &oneshot_pressed_rctl)) { return true; }
    if (!process_oneshot_trigger(keycode, record, U_OS_RSFT, KC_RSFT, &oneshot_state_rsft, &oneshot_pressed_rsft)) { return true; }
    if (!process_oneshot_trigger(keycode, record, U_OS_RALT, KC_RALT, &oneshot_state_ralt, &oneshot_pressed_ralt)) { return true; }
    if (!process_oneshot_trigger(keycode, record, U_OS_RGUI, KC_RGUI, &oneshot_state_rgui, &oneshot_pressed_rgui)) { return true; }

    if (oneshot_state == ONESHOT_INITIAL) {
        bool consumed = false;
        consumed = process_oneshot_initial_dual(keycode, record, U_OS_LCTL, KC_LCTL, &oneshot_state_lctl, U_OS_RCTL, KC_RCTL, &oneshot_state_rctl) || consumed;
        consumed = process_oneshot_initial_dual(keycode, record, U_OS_LSFT, KC_LSFT, &oneshot_state_lsft, U_OS_RSFT, KC_RSFT, &oneshot_state_rsft) || consumed;
        consumed = process_oneshot_initial(keycode, record, U_OS_LALT, KC_LALT, &oneshot_state_lalt) || consumed;
        consumed = process_oneshot_initial(keycode, record, U_OS_RALT, KC_RALT, &oneshot_state_ralt) || consumed;
        consumed = process_oneshot_initial_dual(keycode, record, U_OS_LGUI, KC_LGUI, &oneshot_state_lgui, U_OS_RGUI, KC_RGUI, &oneshot_state_rgui) || consumed;
        if (consumed) {
            oneshot_state = ONESHOT_CONSUMED;
        }
    } else if (oneshot_state == ONESHOT_CONSUMED) {
        oneshot_state = ONESHOT_DONE;
        if (record->event.pressed) {
            process_oneshot_done(keycode, record);
        }
    }

    return true;
}

void oneshot_task(void) {
#if (ONESHOT_TIMEOUT > 0)
    if (oneshot_timer && timer_elapsed_fast(oneshot_timer) > ONESHOT_TIMEOUT) {
        oneshot_timer = 0;
        oneshot_state_lctl = oneshot_state_lsft = oneshot_state_lalt = oneshot_state_lgui =
            oneshot_state_rctl = oneshot_state_rsft = oneshot_state_ralt = oneshot_state_rgui = false;
        update_led();
    }
#endif
}

// Join lines like Vim's `J` command.
// https://getreuer.info/posts/keyboards/macros/index.html
bool process_joinln(uint16_t keycode, keyrecord_t* record, uint16_t joinln_keycode) {
    if (keycode == joinln_keycode && record->event.pressed) {
        SEND_STRING( // Go to the end of the line and tap delete.
            SS_TAP(X_END) SS_TAP(X_DEL)
            // In case this has joined two words together, insert one space.
            SS_TAP(X_SPC)
            SS_LCTL(
            // Go to the beginning of the next word.
            SS_TAP(X_RGHT) SS_TAP(X_LEFT)
            // Select back to the end of the previous word. This should select
            // all spaces and tabs between the joined lines from indentation
            // or trailing whitespace, including the space inserted earlier.
            SS_LSFT(SS_TAP(X_LEFT) SS_TAP(X_RGHT)))
            // Replace the selection with a single space.
            SS_TAP(X_SPC));
        return false;
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

uint16_t get_rev_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    uint16_t tap_keycode = keycode;

    if (IS_LT(keycode)) {
        tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_MT(keycode)) {
        tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    }

    const bool shifted = mods & MOD_MASK_SHIFT;
    const bool controlled = mods & MOD_MASK_CTRL;
    const bool alted = mods & MOD_MASK_ALT;
    const bool guied = mods & MOD_MASK_GUI;

    // Colemak
    if (controlled || alted || guied) {
        switch (tap_keycode) {
            // F B
            case KC_E: return combine_keycode(KC_B, mods);
            case KC_B: return combine_keycode(KC_E, mods);
            // D U
            case KC_G: return combine_keycode(KC_I, mods);
            case KC_I: return combine_keycode(KC_G, mods);
            // N P
            case KC_J: return combine_keycode(KC_R, mods);
            case KC_R: return combine_keycode(KC_J, mods);
            // A E
            case KC_A: return combine_keycode(KC_K, mods);
            case KC_K: return combine_keycode(KC_A, mods);
            // J K
            case KC_Y: return combine_keycode(KC_N, mods);
            case KC_N: return combine_keycode(KC_Y, mods);
            // H L
            case KC_H: return combine_keycode(KC_U, mods);
            case KC_U: return combine_keycode(KC_H, mods);
        }
    } else {
        switch (tap_keycode) {
            // J K
            case KC_Y: return combine_keycode(KC_N, mods);
            case KC_N: return combine_keycode(KC_Y, mods);
            // H L
            case KC_H: return combine_keycode(KC_U, mods);
            case KC_U: return combine_keycode(KC_H, mods);
        }
    }

    if (shifted) {
        if (controlled) {
            // Ctrl + Shift
            switch (tap_keycode) {
                case KC_C: return C(S(KC_V));   // Ctrl + Shift + C / Ctrl + Shift + V
                case KC_V: return C(S(KC_C));   // Ctrl + Shift + C / Ctrl + Shift + V
                case KC_Z: return C(KC_Z);      // Ctrl + Z / Ctrl + Shift + Z
            }
        } else {
            // Shift
            switch (tap_keycode) {
                case KC_TAB: return KC_TAB; // Tab / Shift + Tab
            }
        }
    } else if (controlled) {
        // Ctrl
        switch (tap_keycode) {
            case KC_C: return C(KC_V);      // Ctrl + C / Ctrl + V
            case KC_V: return C(KC_C);      // Ctrl + C / Ctrl + V
            case KC_Z: return C(S(KC_Z));   // Ctrl + Z / Ctrl + Shift + Z
            case KC_Y: return C(KC_Z);      // Ctrl + Y reverses to Ctrl + Z.
        }
    } else {
        // No mods
        switch (tap_keycode) {
            case KC_TAB: return S(KC_TAB);    // Tab / Shift + Tab
        }
    }

    return KC_NO;
}

bool get_repeat_key_eligible(uint16_t keycode, keyrecord_t* record) {

  if (is_oneshot_trigger(keycode)) {
    return false;
  }

  switch (keycode) {
    // Ignore MO, TO, TG, and TT layer switch keys.
    case QK_MOMENTARY ... QK_MOMENTARY_MAX:
    case QK_TO ... QK_TO_MAX:
    case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
    // Ignore mod keys.
    case KC_LCTL ... KC_RGUI:
    case KC_HYPR:
    case KC_MEH:
      // Ignore one-shot keys.
#ifndef NO_ACTION_ONESHOT
    case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
    case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
#endif  // NO_ACTION_ONESHOT
      return false;

      // Ignore hold events on tap-hold keys.
#ifndef NO_ACTION_TAPPING
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
#ifndef NO_ACTION_LAYER
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
#endif  // NO_ACTION_LAYER
      if (record->tap.count == 0) {
        return false;
      }
      break;
#endif  // NO_ACTION_TAPPING

#ifdef SWAP_HANDS_ENABLE
    case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
      if (IS_SWAP_HANDS_KEYCODE(keycode) || record->tap.count == 0) {
        return false;
      }
      break;
#endif  // SWAP_HANDS_ENABLE
  }

  return true;
}

bool process_repeat_key_with_rev_user(uint16_t keycode, keyrecord_t* record,
                                      uint16_t repeat_keycode,
                                      uint16_t rev_repeat_keycode) {
    const uint8_t mods = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if (keycode == repeat_keycode && (all_mods & MOD_MASK_SHIFT)) {
        clear_mods();
        clear_weak_mods();
        clear_oneshot_mods();
        bool result = process_repeat_key_with_rev(rev_repeat_keycode, record, repeat_keycode, rev_repeat_keycode);
        set_mods(mods);
        return result;
    }

    return process_repeat_key_with_rev(keycode, record, U_REPEAT, U_REV_REPEAT);
}

static bool on_left_hand(keypos_t pos) {
#ifdef SPLIT_KEYBOARD
  return pos.row < MATRIX_ROWS / 2;
#else
  return (MATRIX_COLS > MATRIX_ROWS) ? pos.col < MATRIX_COLS / 2
                                     : pos.row < MATRIX_ROWS / 2;
#endif
}

bool is_outer_key(uint16_t keycode, keyrecord_t* record) {
    if (on_left_hand(record->event.key)) {
        return record->event.key.row == (MATRIX_ROWS / 2) - 1 || record->event.key.col == 0;
    } else {
        return record->event.key.row == MATRIX_ROWS - 1 || record->event.key.col == MATRIX_COLS - 1;
    }
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
  if (is_outer_key(tap_hold_keycode, tap_hold_record)) { return true; }
  if (is_outer_key(other_keycode, other_record)) { return true; }

  return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    return ACHORDION_DEFAULT_TIMEOUT;
}

bool process_achordion_user(uint16_t keycode, keyrecord_t *record) {
    // Doubled tap-hold holds issue while recording a dynamic macro
    // https://getreuer.info/posts/keyboards/achordion/index.html#compatibility
    if (dynamic_macro_recording) {
        return true;
    }

    return process_achordion(keycode, record);
}

bool process_layer_lock_user(uint16_t keycode, keyrecord_t *record, uint16_t layer_lock_key) {
    // Unlock all layers if any layer is locked (ensures key has toggle effect).
    if (keycode == layer_lock_key && layer_locked && record->event.pressed) {
        layer_lock_all_off();
        layer_locked = false;
        update_led();
        return false;
    }

    return process_layer_lock(keycode, record, layer_lock_key);
}

struct user_macro {
    const enum user_keycode keycode;
    const char *string;
    const char *shifted_string;
};

const char CURRENT_DIRECTORY[] PROGMEM = "./";
const char UP_DIRECTORY[] PROGMEM = "../";
const char THREE_DOTS[] PROGMEM = "...";
const char DOUBLE_COLON[] PROGMEM = "PP";   // Colemak
const char EQUAL[] PROGMEM = "==";
const char STRICT_EQUAL[] PROGMEM = "===";
const char NOT_EQUAL[] PROGMEM = "!=";
const char STRICT_NOT_EQUAL[] PROGMEM = "!==";
const char LOWER_THAN_OR_EQUAL[] PROGMEM = "<=";
const char GREATER_THAN_OR_EQUAL[] PROGMEM = ">=";
const char ARROW[] PROGMEM = "->";
const char DOUBLE_ARROW[] PROGMEM = "=>";
const char AND_OPERATOR[] PROGMEM = "&&";
const char OR_OPERATOR[] PROGMEM = "||";
const char DOUBLE_MINUS[] PROGMEM = "--";
const char DOUBLE_PLUS[] PROGMEM = "++";
const char DOUBLE_SLASH[] PROGMEM = "//";
const char DOUBLE_QUESTION[] PROGMEM = "??";

const struct user_macro USER_MACROS[] PROGMEM = {
    {U_CURRENT_DIRECTORY, CURRENT_DIRECTORY, UP_DIRECTORY},
    {U_UP_DIRECTORY, UP_DIRECTORY, CURRENT_DIRECTORY},
    {U_THREE_DOTS, THREE_DOTS, DOUBLE_COLON},
    {U_DOUBLE_COLON, DOUBLE_COLON, THREE_DOTS},
    {U_EQUAL, EQUAL, STRICT_EQUAL},
    {U_STRICT_EQUAL, STRICT_EQUAL, EQUAL},
    {U_NOT_EQUAL, NOT_EQUAL, STRICT_NOT_EQUAL},
    {U_STRICT_NOT_EQUAL, STRICT_NOT_EQUAL, NOT_EQUAL},
    {U_LOWER_THAN_OR_EQUAL, LOWER_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL},
    {U_GREATER_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, LOWER_THAN_OR_EQUAL},
    {U_ARROW, ARROW, DOUBLE_ARROW},
    {U_DOUBLE_ARROW, DOUBLE_ARROW, ARROW},
    {U_AND_OPERATOR, AND_OPERATOR, OR_OPERATOR},
    {U_OR_OPERATOR, OR_OPERATOR, AND_OPERATOR},
    {U_DOUBLE_MINUS, DOUBLE_MINUS, DOUBLE_PLUS},
    {U_DOUBLE_SLASH, DOUBLE_SLASH, DOUBLE_QUESTION},
    {U_DOUBLE_QUESTION, DOUBLE_QUESTION, DOUBLE_SLASH},
    {U_USERNAME, "rhlu;jt.g;@tmalu.c;m", "r.g;@axku;s.c;m"},
};

const size_t NUM_USER_MACROS = sizeof (USER_MACROS) / sizeof (*USER_MACROS);

bool process_macros_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) { return true; }

    const uint8_t mods = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    for (size_t i = 0; i < NUM_USER_MACROS; ++i) {
        const struct user_macro macro = USER_MACROS[i];
        if (macro.keycode != keycode) {
            continue;
        }
        if (all_mods & MOD_MASK_SHIFT) {
            clear_mods();
            clear_weak_mods();
            clear_oneshot_mods();
            send_string_P(macro.shifted_string);
            set_mods(mods);
        } else {
            send_string_P(macro.string);
        }
        return false;
    }

	switch (keycode) {
		case U_CAPS_WORD_TOGGLE:
            if (all_mods & MOD_MASK_SHIFT) {
                clear_mods();
                clear_weak_mods();
                clear_oneshot_mods();
                tap_code(KC_CAPSLOCK);
                set_mods(mods);
            } else {
                caps_word_toggle();
            }
            return false;
	}

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion_user(keycode, record)) { return false; }
    if (!process_repeat_key_with_rev(keycode, record, U_REPEAT, U_REV_REPEAT)) { return false; }
    if (!process_layer_lock_user(keycode, record, U_LAYER_LOCK)) { return false; }
    if (!process_oneshot(keycode, record)) { return false; }
    if (!process_select_word(keycode, record, U_SEL_WORD)) { return false; }
    if (!process_joinln(keycode, record, U_JOIN_LN)) { return false; }
    if (!process_sentence_case(keycode, record)) { return false; }
    if (!process_macros_user(keycode, record)) { return false; }
    if (!process_autocorrection(keycode, record)) { return false; }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_oneshot_done(keycode, record);
}

void matrix_scan_user(void) {
    achordion_task();
    layer_lock_task();
    oneshot_task();
    sentence_case_task();
}

// Workaround for https://github.com/qmk/qmk_firmware/issues/16406
void suspend_wakeup_init_user(void) {
    NVIC_SystemReset();
}
