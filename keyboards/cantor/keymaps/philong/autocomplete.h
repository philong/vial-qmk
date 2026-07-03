#pragma once

#include QMK_KEYBOARD_H

#include "quantum/keymap_extras/keymap_colemak.h"

bool process_autocomplete(uint16_t keycode, keyrecord_t *record, uint16_t autocomplete_keycode);
