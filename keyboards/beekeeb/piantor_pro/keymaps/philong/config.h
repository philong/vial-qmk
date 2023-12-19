/* keyboard uid */
#define VIAL_KEYBOARD_UID {0x49, 0x32, 0xC4, 0xEF, 0x12, 0x96, 0xC8, 0x4F}

// 36 keys
#define VIAL_UNLOCK_COMBO_ROWS { 0, 4 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 1 }

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1
#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 1

/* default layer count */
#define DYNAMIC_KEYMAP_LAYER_COUNT 16

#ifndef UNICODE_MODE_LINUX
    #define UNICODE_MODE_LINUX UC_LNX
#endif
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

// Colemak
#define UNICODE_KEY_LNX LCTL(LSFT(KC_I))

#ifdef CONSOLE_ENABLE
    #ifndef VIAL_INSECURE
        #define VIAL_INSECURE
    #endif
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

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD
#define QUICK_TAP_TERM 0

#define PERMISSIVE_HOLD

#define ACHORDION_STREAK

#ifndef AUTO_SHIFT_NO_SETUP
    #define AUTO_SHIFT_NO_SETUP
#endif
#define NO_AUTO_SHIFT_ALPHA
// #define AUTO_SHIFT_MODIFIERS
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define RETRO_SHIFT 500

// #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 30000

#define COMBO_ONLY_FROM_LAYER 0
#define VIAL_COMBO_ENTRIES 64

#define DYNAMIC_KEYMAP_MACRO_COUNT 64

#define ONESHOT_TIMEOUT 2000
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MOUSEKEY_DELAY 0

#define MK_C_OFFSET_UNMOD 12
#define MK_C_INTERVAL_UNMOD 16

#define MK_C_OFFSET_0 4
#define MK_C_INTERVAL_0 16

#define MK_C_OFFSET_1 24
#define MK_C_INTERVAL_1 16

#define MK_C_OFFSET_2 32
#define MK_C_INTERVAL_2 16

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
