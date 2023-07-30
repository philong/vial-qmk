
/* keyboard uid */
#define VIAL_KEYBOARD_UID {0xF0, 0x67, 0x2F, 0x54, 0x23, 0xB3, 0x7B, 0x55}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 4 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 5 }

/* default layer count */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

#define KEYCODES_V5

#ifndef UNICODE_MODE_LINUX
    #define UNICODE_MODE_LINUX UC_LNX
#endif
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

// Colemak
#define UNICODE_KEY_LNX LCTL(LSFT(KC_I))

#ifdef CONSOLE_ENABLE
    #define VIAL_INSECURE
    #undef NKRO_ENABLE
    #undef MOUSEKEY_ENABLE
    #undef EXTRAKEY_ENABLE
#endif

// QMK 0.19.0 keycode parsing macros currently missing from Vial
#ifdef KEYCODES_V5
    #define IS_QK_BASIC(code) ((code) >= QK_BASIC && (code) <= QK_BASIC_MAX)
    #define IS_QK_MOD_TAP(code) ((code) >= QK_MOD_TAP && (code) <= QK_MOD_TAP_MAX)
    #define IS_QK_LAYER_TAP(code) ((code) >= QK_LAYER_TAP && (code) <= QK_LAYER_TAP_MAX)
    #define QK_MOD_TAP_GET_MODS(kc) (((kc) >> 8) & 0x1F)
    #define QK_MOD_TAP_GET_TAP_KEYCODE(kc) ((kc)&0xFF)
    #define QK_LAYER_TAP_GET_TAP_KEYCODE(kc) ((kc)&0xFF)
    #define QK_MODS_GET_BASIC_KEYCODE(kc) ((kc)&0xFF)
    #define QK_MODS_GET_MODS(kc) (((kc) >> 8) & 0x1F)
    #define QK_MOMENTARY_GET_LAYER(kc) ((kc)&0x1F)
    #define QK_LAYER_TAP_TOGGLE_GET_LAYER(kc) ((kc)&0x1F)
    #define QK_LAYER_MOD_GET_LAYER(kc) (((kc) >> 5) & 0xF)
    #define QK_LAYER_TAP_GET_LAYER(kc) (((kc) >> 8) & 0xF)
    #define IS_MODIFIER_KEYCODE(kc) IS_MOD(kc)
#else
    #define IS_MT(code) IS_QK_MOD_TAP(code)
    #define IS_LT(code) IS_QK_LAYER_TAP(code)
#endif

#ifndef QK_KB_0
  #define QK_KB_0 USER00
#endif

// https://precondition.github.io/home-row-mods#getting-started-with-home-row-mods-on-qmk

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 175
#ifndef TAPPING_TERM_PER_KEY
    #define TAPPING_TERM_PER_KEY
#endif

// Prevent normal rollover on alphas from accidentally triggering mods.
#ifdef KEYCODES_V5
    #define IGNORE_MOD_TAP_INTERRUPT
#endif

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

#define PERMISSIVE_HOLD

#define ACHORDION_TIMEOUT_DEFAULT 500
#define ACHORDION_TIMEOUT_MIN 100

#ifndef AUTO_SHIFT_NO_SETUP
    #define AUTO_SHIFT_NO_SETUP
#endif
#define NO_AUTO_SHIFT_ALPHA
// #define AUTO_SHIFT_MODIFIERS
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define RETRO_SHIFT 500

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 30000

#define COMBO_ONLY_FROM_LAYER 0

#define FORCE_NKRO

#define USER_LED_PIN C13
#define LED_CAPS_LOCK_PIN USER_LED_PIN
#define LED_PIN_ON_STATE 0

// make cantor:philong:dfu-util-split-left
// make cantor:philong:dfu-util-split-right
// https://github.com/qmk/qmk_firmware/blob/master/docs/flashing.md#make-targets-3
#define EE_HANDS

// Fix cold boot
// https://github.com/qmk/qmk_firmware/issues/8990
// #define SPLIT_USB_DETECT
// #define SPLIT_USB_TIMEOUT 7000
#define SPLIT_WATCHDOG_ENABLE

// Mod tap after wake up is broken
// https://github.com/qmk/qmk_firmware/issues/16406
// #define USB_SUSPEND_WAKEUP_DELAY 5000

#define ONESHOT_TIMEOUT 2000

#define LAYER_LOCK_IDLE_TIMEOUT 60000

#define SELECT_WORD_TIMEOUT 2000

#define SENTENCE_CASE_TIMEOUT 2000

#include "ignore.extras.h"

#ifndef DMACRO1_TEXT1
    #define DMACRO1_TEXT1 ""
#endif
#ifndef DMACRO1_TEXT2
    #define DMACRO1_TEXT2 ""
#endif
#ifndef DMACRO2_TEXT1
    #define DMACRO2_TEXT1 ""
#endif
#ifndef DMACRO2_TEXT2
    #define DMACRO2_TEXT2 ""
#endif
