// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
    #include "print.h"
#endif

#include "via.h"
#include "qmk_settings.h"

#include "features/achordion.h"
#include "features/layer_lock.h"
#include "features/select_word.h"
#include "features/repeat_key.h"
#include "features/sentence_case.h"
#include "features/autocorrection.h"
#include "features/mouse_turbo_click.h"
#include "andrewjrae-features/casemodes.h"

// #include "layermodes.h"
#include "keycodes.h"



// https://github.com/treeman/qmk_firmware/blob/master/keyboards/ferris/keymaps/treeman/layermodes.c

static uint16_t num_word_timer;
static bool _num_word_enabled = false;

void num_word_user(bool enabled);

bool num_word_enabled(void) {
    return _num_word_enabled;
}

void enable_num_word(void) {
    _num_word_enabled = true;
    layer_on(_NUM_WORD);
    num_word_user(_num_word_enabled);
}

void disable_num_word(void) {
    _num_word_enabled = false;
    layer_off(_NUM_WORD);
    num_word_user(_num_word_enabled);
}

void toggle_num_word(void) {
    if (num_word_enabled()) {
        disable_num_word();
    } else {
        enable_num_word();
    }
}

void process_num_word_activation(const keyrecord_t *record) {
    if (record->event.pressed) {
        layer_on(_NUM_WORD);
        num_word_timer = timer_read();
    } else {
        if (timer_elapsed(num_word_timer) < TAPPING_TERM) {
            // Tapping enables NUMWORD
            _num_word_enabled = true;
            num_word_user(_num_word_enabled);
        } else {
            // Holding turns off NUM when released
            layer_off(_NUM_WORD);
        }
    }
}

bool process_num_word(uint16_t keycode, const keyrecord_t *record) {
    if (!_num_word_enabled) return true;

    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            if (record->tap.count == 0)
                return true;
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
        case U_REPEAT:
        case U_ALT_REPEAT:
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



void clear_all_mods(void) {
    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();
}

uint16_t qs_get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    // Increase the tapping term a little for slower ring and pinky fingers.
    uint16_t tap_keycode;

    if (IS_LT(keycode)) {
        tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_MT(keycode)) {
        tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else {
      return QS.tapping_term;
    }

    switch (tap_keycode) {
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
            return QS.tapping_term + 15;

        default:
            return QS.tapping_term;
    }
}

enum oneshot_states {
    ONESHOT_INITIAL,
    ONESHOT_CONSUMED,
    ONESHOT_DONE,
};

static int oneshot_state = ONESHOT_INITIAL;
fast_timer_t oneshot_timer = 0;

static bool oneshot_state_lctl = false;
static bool oneshot_state_lsft = false;
static bool oneshot_state_lalt = false;
static bool oneshot_state_lgui = false;
static bool oneshot_state_rctl = false;
static bool oneshot_state_rsft = false;
static bool oneshot_state_ralt = false;
static bool oneshot_state_rgui = false;

static bool oneshot_pressed_lctl = false;
static bool oneshot_pressed_lsft = false;
static bool oneshot_pressed_lalt = false;
static bool oneshot_pressed_lgui = false;
static bool oneshot_pressed_rctl = false;
static bool oneshot_pressed_rsft = false;
static bool oneshot_pressed_ralt = false;
static bool oneshot_pressed_rgui = false;

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
    return IS_MT(keycode) || (keycode >= QK_RALT && keycode < QK_RGUI) || keycode == CM_SCLN;
}

// Colemak
bool caps_word_press_user(uint16_t keycode) {
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

void set_led(bool active) {
    uint16_t level = active ? LED_PIN_ON_STATE : ~LED_PIN_ON_STATE;
    writePin(USER_LED_PIN, level);
}

bool in_high_layer = false;
bool layer_locked = false;
bool sentence_primed = false;
bool dynamic_macro_recording = false;

bool led_enabled_user(void) {
    return is_caps_word_on() || get_xcase_state() != XCASE_OFF || _num_word_enabled || in_high_layer || layer_locked || sentence_primed || dynamic_macro_recording || oneshot_active();
}

void update_led(void) {
    set_led(led_enabled_user());
}

void caps_word_set_user(bool active) {
    update_led();

    if (active) {
        oneshot_state_lsft = false;
        oneshot_state_rsft = false;
    }
}

void xcase_set_user(enum xcase_state state) {
    update_led();
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

bool dynamic_macro_recorded[] = { false, false };
const size_t DYNAMIC_MACRO_RECORDED_LEN = sizeof (dynamic_macro_recorded) / sizeof (bool);

size_t get_dynamic_macro_index(int8_t direction) {
    if (direction > 0) {
        return 0;
    } else if (direction < 0) {
        return 1;
    }
    return  -1;
}

void dynamic_macro_record_start_user(void) {
    dynamic_macro_recording = true;
    update_led();
}

void dynamic_macro_record_end_user(int8_t direction) {
    dynamic_macro_recording = false;
    update_led();

    size_t index = get_dynamic_macro_index(direction);
    if (index < 0 || index >= DYNAMIC_MACRO_RECORDED_LEN || dynamic_macro_recorded[index]) return;
    dynamic_macro_recorded[index] = true;
}

// void dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record) {
//     size_t index = get_dynamic_macro_index(direction);
//     if (index < 0 || index >= DYNAMIC_MACRO_RECORDED_SIZE || dynamic_macro_recorded[index]) return;
//     dynamic_macro_recorded[index] = true;
// }

static const int dynamic_macro_delay = 4;

void dynamic_macro_play_user(int8_t direction) {
    size_t index = get_dynamic_macro_index(direction);
    if (index < 0 || index >= DYNAMIC_MACRO_RECORDED_LEN || dynamic_macro_recorded[index]) return;

    switch (index) {
    case 0:
        // tap_code16(MACRO14);
        send_string_with_delay_P(
            SS_TAP(X_END)
            SS_LSFT(SS_TAP(X_HOME))
            DMACRO1_TEXT1
            SS_TAP(X_TAB)
            DMACRO1_TEXT2
            SS_TAP(X_ENTER),
            dynamic_macro_delay
        );
        break;
    case 1:
    default:
        send_string_with_delay_P(
            SS_TAP(X_END)
            SS_LSFT(SS_TAP(X_HOME))
            DMACRO2_TEXT1
            SS_TAP(X_TAB)
            DMACRO2_TEXT2
            SS_TAP(X_ENTER),
            dynamic_macro_delay
        );
    }
}

// Colemak
bool sentence_case_check_ending(const uint16_t* buffer) {
#if SENTENCE_CASE_BUFFER_SIZE >= 5
  // Don't consider the abbreviations "vs." and "etc." to end the sentence.
  if (SENTENCE_CASE_JUST_TYPED(KC_SPC, CM_V, CM_S, CM_DOT) ||
      SENTENCE_CASE_JUST_TYPED(KC_SPC, CM_E, CM_T, CM_C, CM_DOT)) {
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
    if (IS_MOD(keycode)) {
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
    if (keycode != joinln_keycode || !record->event.pressed) {
        return true;
    }

    const uint8_t mods = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if (all_mods & MOD_MASK_SHIFT) {
        clear_all_mods();

        // Split current line
        SEND_STRING(
            SS_LCTL(
                SS_TAP(X_LEFT) SS_TAP(X_RGHT)
            )
            SS_TAP(X_ENTER)
        );

        set_mods(mods);
    } else {
        // Join current line with next line
        SEND_STRING(
            SS_TAP(X_END)
            SS_LCTL(SS_TAP(X_DEL))
            SS_TAP(X_SPC)
        );
        // SEND_STRING( // Go to the end of the line and tap delete.
        //     SS_TAP(X_END) SS_TAP(X_DEL)
        //     // In case this has joined two words together, insert one space.
        //     SS_TAP(X_SPC)
        //     SS_LCTL(
        //     // Go to the beginning of the next word.
        //     SS_TAP(X_RGHT) SS_TAP(X_LEFT)
        //     // Select back to the end of the previous word. This should select
        //     // all spaces and tabs between the joined lines from indentation
        //     // or trailing whitespace, including the space inserted earlier.
        //     SS_LSFT(SS_TAP(X_LEFT) SS_TAP(X_RGHT)))
        //     // Replace the selection with a single space.
        //     SS_TAP(X_SPC));
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

    if (IS_LT(keycode)) {
        tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_MT(keycode)) {
        tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else {
        tap_keycode = keycode;
    }

    const bool shifted = mods & MOD_MASK_SHIFT;
    const bool controlled = mods & MOD_MASK_CTRL;
    const bool alted = mods & MOD_MASK_ALT;
    const bool guied = mods & MOD_MASK_GUI;

    switch (tap_keycode) {
    case U_SEL_WORD:
        return shifted ? S(KC_UP) : C(S(KC_LEFT));
    case U_JOIN_LN:
        return shifted ? U_JOIN_LN : S(U_JOIN_LN);
    case KC_SPACE:
        return combine_keycode(KC_BACKSPACE, mods);
    case KC_ENTER:
        return combine_keycode(KC_ESCAPE, mods);
    case KC_ESCAPE:
        return combine_keycode(KC_ENTER, mods);
    }

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
                case KC_Z: return C(KC_Z);      // Ctrl + Z <-> Ctrl + Shift + Z

                case KC_X: return C(S(KC_V));   // Ctrl + Shift + X -> Ctrl + Shift + V
                case KC_C: return C(S(KC_V));   // Ctrl + Shift + C <-> Ctrl + Shift + V
                case KC_V: return C(S(KC_C));   // Ctrl + Shift + C <-> Ctrl + Shift + V

                case CM_T: return C(CM_W);      // Ctrl + Shift + T -> Ctrl + W
            }
        } else {
            // Shift
            switch (tap_keycode) {
                case KC_TAB: return KC_TAB; // Tab <-> Shift + Tab
            }
        }
    } else if (controlled) {
        // Ctrl
        switch (tap_keycode) {
            case KC_Z: return C(S(KC_Z));   // Ctrl + Z <-> Ctrl + Shift + Z
            case KC_Y: return C(KC_Z);      // Ctrl + Y -> Ctrl + Z

            case KC_X: return C(KC_V);      // Ctrl + X -> Ctrl + V
            case KC_C: return C(KC_V);      // Ctrl + C <-> Ctrl + V
            case KC_V: return C(KC_C);      // Ctrl + C <-> Ctrl + V

            case CM_W: return C(S(CM_T));   // Ctrl + W -> Ctrl + Shift + T
            case CM_T: return C(CM_W);      // Ctrl + T -> Ctrl + W
        }
    } else {
        // No mods
        switch (tap_keycode) {
            case KC_TAB: return S(KC_TAB);    // Tab <-> Shift + Tab
        }
    }

    return KC_TRNS;
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
  return !is_oneshot_trigger(keycode);
}

// Shift+REPEAT -> ALTREP
bool process_repeat_key_with_alt_user(uint16_t keycode, keyrecord_t* record,
                                      uint16_t repeat_keycode,
                                      uint16_t alt_repeat_keycode) {
    const uint8_t mods = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if (keycode == repeat_keycode && (all_mods & MOD_MASK_SHIFT)) {
        clear_all_mods();
        bool result = process_repeat_key_with_alt(alt_repeat_keycode, record, repeat_keycode, alt_repeat_keycode);
        set_mods(mods);
        return result;
    }

    return process_repeat_key_with_alt(keycode, record, U_REPEAT, U_ALT_REPEAT);
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
    switch (other_keycode) {
        case QK_TAP_DANCE...QK_TAP_DANCE_MAX:
            return false;
    }

    if (is_outer_key(tap_hold_keycode, tap_hold_record)) { return true; }
    if (is_outer_key(other_keycode, other_record)) { return true; }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    switch (tap_hold_keycode) {
    case MT_F:
        return ACHORDION_TIMEOUT_MIN;
    default:
        return ACHORDION_TIMEOUT_DEFAULT;
    }
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
    const char *controlled_string;
    const char *shifted_controlled_string;
};

const char CURRENT_DIRECTORY[] PROGMEM = "./";
const char UP_DIRECTORY[] PROGMEM = "../";
const char DOT[] PROGMEM = ".";
const char THREE_DOTS[] PROGMEM = "...";
const char DOUBLE_COLON[] PROGMEM = "::";
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
const char LEFT_SHIFT[] PROGMEM = "<<";
const char RIGHT_SHIFT[] PROGMEM = ">>";
const char DIAMOND[] PROGMEM = "<>";
const char ADD_ASSIGN[] PROGMEM = "+=";
const char SUB_ASSIGN[] PROGMEM = "-=";
const char DOUBLE_UNDERSCORE[] PROGMEM = "__";
const char IN_UNDERSCORES[] PROGMEM = SS_LCTL(SS_TAP(X_LEFT)) "__" SS_LCTL(SS_TAP(X_RGHT)) "__";

const struct user_macro USER_MACROS[] PROGMEM = {
    {U_CURRENT_DIRECTORY, CURRENT_DIRECTORY, UP_DIRECTORY, NULL, NULL},
    {U_UP_DIRECTORY, UP_DIRECTORY, CURRENT_DIRECTORY, NULL, NULL},
    {U_DOT, DOT, THREE_DOTS, NULL, NULL},
    {U_THREE_DOTS, THREE_DOTS, DOUBLE_COLON, NULL, NULL},
    {U_DOUBLE_COLON, DOUBLE_COLON, THREE_DOTS, NULL, NULL},
    {U_EQUAL, EQUAL, DOUBLE_PLUS, STRICT_EQUAL, ADD_ASSIGN},
    {U_STRICT_EQUAL, STRICT_EQUAL, EQUAL, NULL, NULL},
    {U_NOT_EQUAL, NOT_EQUAL, DIAMOND, STRICT_NOT_EQUAL, STRICT_NOT_EQUAL},
    {U_STRICT_NOT_EQUAL, STRICT_NOT_EQUAL, NOT_EQUAL, NULL, NULL},
    {U_LOWER_THAN_OR_EQUAL, LOWER_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, NULL, NULL},
    {U_GREATER_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL, LOWER_THAN_OR_EQUAL, NULL, NULL},
    {U_ARROW, ARROW, DOUBLE_ARROW, NULL, NULL},
    {U_DOUBLE_ARROW, DOUBLE_ARROW, ARROW, NULL, NULL},
    {U_AND_OPERATOR, AND_OPERATOR, OR_OPERATOR, NULL, NULL},
    {U_OR_OPERATOR, OR_OPERATOR, AND_OPERATOR, NULL, NULL},
    {U_DOUBLE_MINUS, DOUBLE_MINUS, DOUBLE_UNDERSCORE, IN_UNDERSCORES, SUB_ASSIGN},
    {U_DOUBLE_SLASH, DOUBLE_SLASH, DOUBLE_QUESTION, NULL, NULL},
    {U_DOUBLE_QUESTION, DOUBLE_QUESTION, DOUBLE_SLASH, NULL, NULL},
    {U_LEFT_SHIFT, LEFT_SHIFT, RIGHT_SHIFT, NULL, NULL},
    {U_RIGHT_SHIFT, RIGHT_SHIFT, LEFT_SHIFT, NULL, NULL},
    {U_USERNAME, "philong.do@gmail.com", "p.do@axelor.com", "philong", "Phi-Long Do"},
};

const size_t NUM_USER_MACROS = sizeof (USER_MACROS) / sizeof (*USER_MACROS);

bool process_macros_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) { return true; }

    uint16_t tap_keycode;

    if (IS_LT(keycode)) {
        if (record->tap.count == 0) { return true; } // Key is being held.
        tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_MT(keycode)) {
        if (record->tap.count == 0) { return true; } // Key is being held.
        tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else {
        tap_keycode = keycode;
    }

    const uint8_t mods = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    const bool is_shifted = all_mods & MOD_MASK_SHIFT;
    const bool is_controlled = all_mods & MOD_MASK_CTRL;

    for (size_t i = 0; i < NUM_USER_MACROS; ++i) {
        const struct user_macro macro = USER_MACROS[i];
        if (macro.keycode != tap_keycode) {
            continue;
        }
        if (macro.shifted_controlled_string && is_shifted && is_controlled) {
            clear_all_mods();
            send_string_P(macro.shifted_controlled_string);
            set_mods(mods);
        } else if (macro.controlled_string && is_controlled) {
            clear_all_mods();
            send_string_P(macro.controlled_string);
            set_mods(mods);
        } else if (macro.shifted_string && is_shifted) {
            clear_all_mods();
            send_string_P(macro.shifted_string);
            set_mods(mods);
        } else {
            send_string_P(macro.string);
        }
        return false;
    }

	switch (tap_keycode) {
        case KC_ESCAPE:
            if (is_caps_word_on()) {
                caps_word_off();
                return false;
            }
            if (get_xcase_state() != XCASE_OFF) {
                disable_xcase();
            }
            if (num_word_enabled()) {
                disable_num_word();
                return false;
            }
            break;
		case U_CAPS_WORD_TOGGLE:
            if (is_shifted && is_controlled) {
                // caps lock
                caps_word_off();
                disable_xcase();
                disable_num_word();
                clear_all_mods();
                tap_code(KC_CAPSLOCK);
                set_mods(mods);
            } else if (is_controlled) {
                // num word
                caps_word_off();
                disable_xcase();
                clear_all_mods();
                toggle_num_word();
                set_mods(mods);
            } else if (is_shifted) {
                caps_word_off();
                disable_xcase();
                disable_num_word();
                // https://github.com/andrewjrae/kyria-keymap/#x-case
                if (get_xcase_state() != XCASE_OFF) {
                    disable_xcase();
                } else {
                    // enable_xcase();
                    enable_xcase_with(OSM(MOD_LSFT));
                }
            } else {
                // caps word
                disable_xcase();
                disable_num_word();
                caps_word_toggle();
            }
            return false;
        case U_NUM_WORD_TOGGLE:
            caps_word_off();
            toggle_num_word();
            return false;
        case U_CG_TOGG:
            process_magic(CG_TOGG, record);
            return false;
	}

    return true;
}

void num_word_user(bool enabled) {
    update_led();
}

bool process_select_word_user(uint16_t keycode, keyrecord_t* record, uint16_t sel_keycode) {
    const int8_t repeat_key_count = get_repeat_key_count();

    if (repeat_key_count == 0 && !process_select_word(keycode, record, U_SEL_WORD)) {
        return false;
    }

    if (keycode != U_SEL_WORD || !record->event.pressed) {
        return true;
    }

    const uint8_t mods = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    if (all_mods & MOD_MASK_SHIFT) {
        if (repeat_key_count > 0) {
            SEND_STRING(
                SS_TAP(X_DOWN)
            );
        } else {
            SEND_STRING(
                SS_TAP(X_UP)
            );
        }
    } else {
        if (repeat_key_count > 0) {
            SEND_STRING(
                SS_LCTL(SS_LSFT(SS_TAP(X_RGHT)))
            );
        } else {
            SEND_STRING(
                SS_LCTL(SS_LSFT(SS_TAP(X_LEFT)))
            );
        }
    }

    return false;
}

typedef union {
  uint32_t raw;
  struct {
    bool colemak_fr :1;
  };
} user_config_t;

user_config_t user_config;

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 0;
  user_config.colemak_fr = false;
  eeconfig_update_user(user_config.raw);
}

// bool send_key_with_ralt(char *key, char *dead_ralt_key, uint8_t mods, bool shifted) {
//     clear_all_mods();
//     SEND_STRING(SS_RALT(dead_ralt_key));
//     SEND_STRING(shifted ? SS_LSFT(key) : key);
//     set_mods(mods);
//     return false;
// }

bool process_colemak_fr(uint16_t keycode, keyrecord_t *record, uint16_t toggle_keycode) {
    if (!record->event.pressed) { return true; }

    if (keycode == toggle_keycode) {
        user_config.colemak_fr ^= 1;
        eeconfig_update_user(user_config.raw);
        return false;
    }

    if (!user_config.colemak_fr) { return true; }

    uint16_t tap_keycode;

    if (IS_LT(keycode)) {
        if (record->tap.count == 0) { return true; } // Key is being held.
        tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_MT(keycode)) {
        if (record->tap.count == 0) { return true; } // Key is being held.
        tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
    } else {
        tap_keycode = keycode;
    }

    const uint8_t mods = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();
    if ((all_mods & MOD_BIT(KC_RALT)) == 0) { return true; }
    const bool shifted = all_mods & MOD_MASK_SHIFT;

    switch (tap_keycode) {
        // grave
        case CM_A:
            clear_all_mods();
            SEND_STRING(SS_RALT("r"));
            SEND_STRING(shifted ? SS_LSFT("a") : "a");
            set_mods(mods);
            return false;
        case CM_P:
            clear_all_mods();
            SEND_STRING(SS_RALT("r"));
            SEND_STRING(shifted ? SS_LSFT("e") : "e");
            set_mods(mods);
            return false;
        case CM_L:
            clear_all_mods();
            SEND_STRING(SS_RALT("r"));
            SEND_STRING(shifted ? SS_LSFT("u") : "u");
            set_mods(mods);
            return false;
        // circonflexe
        case CM_Q:
            clear_all_mods();
            SEND_STRING(SS_RALT("x"));
            SEND_STRING(shifted ? SS_LSFT("a") : "a");
            set_mods(mods);
            return false;
        case CM_F:
            clear_all_mods();
            SEND_STRING(SS_RALT("x"));
            SEND_STRING(shifted ? SS_LSFT("e") : "e");
            set_mods(mods);
            return false;
        case CM_I:
            clear_all_mods();
            SEND_STRING(SS_RALT("x"));
            SEND_STRING(shifted ? SS_LSFT("i") : "i");
            set_mods(mods);
            return false;
        case CM_O:
            clear_all_mods();
            SEND_STRING(SS_RALT("x"));
            SEND_STRING(shifted ? SS_LSFT("o") : "o");
            set_mods(mods);
            return false;
        case CM_U:
            clear_all_mods();
            SEND_STRING(SS_RALT("x"));
            SEND_STRING(shifted ? SS_LSFT("u") : "u");
            set_mods(mods);
            return false;
        // tréma
        case CM_W:
            clear_all_mods();
            SEND_STRING(SS_RALT("d"));
            SEND_STRING(shifted ? SS_LSFT("e") : "e");
            set_mods(mods);
            return false;
        case CM_Y:
            clear_all_mods();
            SEND_STRING(SS_RALT("d"));
            SEND_STRING(shifted ? SS_LSFT("i") : "i");
            set_mods(mods);
            return false;
        case CM_SCLN:
            clear_all_mods();
            SEND_STRING(SS_RALT("d"));
            SEND_STRING(shifted ? SS_LSFT("u") : "u");
            set_mods(mods);
            return false;
        default:
            return true;
    }

    // switch (tap_keycode) {
    //     // grave
    //     case CM_A:
    //         return send_key_with_ralt("a", "r", mods, shifted);
    //     case CM_P:
    //         return send_key_with_ralt("e", "r", mods, shifted);
    //     case CM_L:
    //         return send_key_with_ralt("u", "r", mods, shifted);
    //     // circonflexe
    //     case CM_Q:
    //         return send_key_with_ralt("a", "x", mods, shifted);
    //     case CM_F:
    //         return send_key_with_ralt("e", "x", mods, shifted);
    //     case CM_I:
    //         return send_key_with_ralt("i", "x", mods, shifted);
    //     case CM_O:
    //         return send_key_with_ralt("o", "x", mods, shifted);
    //     case CM_U:
    //         return send_key_with_ralt("u", "x", mods, shifted);
    //     // tréma
    //     case CM_W:
    //         return send_key_with_ralt("e", "d", mods, shifted);
    //     case CM_Y:
    //         return send_key_with_ralt("i", "d", mods, shifted);
    //     case CM_SCLN:
    //         return send_key_with_ralt("u", "d", mods, shifted);
    //     default:
    //         return true;
    // }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion_user(keycode, record)) { return false; }
    if (!process_repeat_key_with_alt_user(keycode, record, U_REPEAT, U_ALT_REPEAT)) { return false; }
    if (!process_layer_lock_user(keycode, record, U_LAYER_LOCK)) { return false; }
    if (!process_colemak_fr(keycode, record, U_CM_TOGG)) { return false; }
    if (!process_oneshot(keycode, record)) { return false; }
    if (!process_select_word_user(keycode, record, U_SEL_WORD)) { return false; }
    if (!process_joinln(keycode, record, U_JOIN_LN)) { return false; }
    if (!process_sentence_case(keycode, record)) { return false; }
    if (!process_macros_user(keycode, record)) { return false; }
    if (!process_autocorrection(keycode, record)) { return false; }
    if (!process_mouse_turbo_click(keycode, record, U_TURBO_CLICK)) { return false; }
    if (!process_case_modes(keycode, record)) { return false; }
    if (!process_num_word(keycode, record)) {  return false; }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_oneshot_done(keycode, record);
}

void matrix_scan_user(void) {
    achordion_task();
    layer_lock_task();
    oneshot_task();
    select_word_task();
    sentence_case_task();
}

// Workaround for https://github.com/qmk/qmk_firmware/issues/16406
void suspend_wakeup_init_user(void) {
    NVIC_SystemReset();
}
