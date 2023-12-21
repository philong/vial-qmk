#pragma once

#include QMK_KEYBOARD_H

#include <stdint.h>

bool process_autocomplete(uint16_t keycode, keyrecord_t *record, uint16_t autocomplete_keycode);

char* get_current_word(void);

uint8_t get_current_word_length(void);
