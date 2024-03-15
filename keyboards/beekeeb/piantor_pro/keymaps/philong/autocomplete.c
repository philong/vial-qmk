#include "autocomplete.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "quantum/keymap_extras/keymap_colemak.h"

#include "autocomplete_data.h"

#define MAX_WORD_LENGTH 31

static char    current_word[MAX_WORD_LENGTH + 1];      // Stores the current word being typed
static uint8_t current_word_mods[MAX_WORD_LENGTH + 1]; // Stores the mods in the current word
static uint8_t current_word_length = 0;                // Length of the current word

static char autocomplete_result[MAX_WORD_LENGTH + 1] = "";

struct last_autocomplete {
    ssize_t index;
    size_t  size;
};

static struct last_autocomplete last_autocomplete = {-1, 0};

static void reset_word(void) {
    if (current_word_length > 0) {
        current_word_length = 0;
        current_word[0]     = '\0';
    }
}

static bool is_allowed_in_buffer(uint16_t keycode) {
    return keycode < KC_CAPS_LOCK && keycode != KC_ENTER;
}

// __attribute__((weak)) const char keycode_to_char[KC_CAPS_LOCK] PROGMEM = {
//     [0] = ' ', [1] = ' ', [2] = ' ', [3] = ' ', [4] = 'a', [5] = 'b', [6] = 'c', [7] = 'd', [8] = 'e', [9] = 'f', [10] = 'g', [11] = 'h', [12] = 'i', [13] = 'j', [14] = 'k', [15] = 'l', [16] = 'm', [17] = 'n', [18] = 'o', [19] = 'p', [20] = 'q', [21] = 'r', [22] = 's', [23] = 't', [24] = 'u', [25] = 'v', [26] = 'w', [27] = 'x', [28] = 'y', [29] = 'z', [30] = '1', [31] = '2', [32] = '3', [33] = '4', [34] = '5', [35] = '6', [36] = '7', [37] = '8', [38] = '9', [39] = '0', [40] = ' ', [41] = ' ', [42] = ' ', [43] = ' ', [44] = ' ', [45] = '-', [46] = ' ', [47] = ' ', [48] = ' ', [49] = ' ', [50] = ' ', [51] = ' ', [52] = '\'', [53] = ' ', [54] = ',', [55] = '.',[56] = ' ',
// };

// Colemak
__attribute__((weak)) const char keycode_to_char[KC_CAPS_LOCK] PROGMEM = {
    [0] = ' ', [1] = ' ', [2] = ' ', [3] = ' ', [4] = 'a', [5] = 'b', [6] = 'c', [7] = 's', [8] = 'f', [9] = 't', [10] = 'd', [11] = 'h', [12] = 'u', [13] = 'n', [14] = 'e', [15] = 'i', [16] = 'm', [17] = 'k', [18] = 'y', [19] = ' ', [20] = 'q', [21] = 'p', [22] = 'r', [23] = 'g', [24] = 'l', [25] = 'v', [26] = 'w', [27] = 'x', [28] = 'j', [29] = 'z', [30] = '1', [31] = '2', [32] = '3', [33] = '4', [34] = '5', [35] = '6', [36] = '7', [37] = '8', [38] = '9', [39] = '0', [40] = ' ', [41] = ' ', [42] = ' ', [43] = ' ', [44] = ' ', [45] = '-', [46] = ' ', [47] = ' ', [48] = ' ', [49] = ' ', [50] = ' ', [51] = 'o', [52] = '\'', [53] = ' ', [54] = ',', [55] = '.', [56] = ' ',
};

__attribute__((weak)) char autocomplete_keycode_to_char(uint16_t keycode) {
    return keycode >= KC_CAPS_LOCK ? ' ' : keycode_to_char[keycode];
}

static char get_shifted_char(const char c) {
    if (c == '\'') {
        return '\"';
    }
    return toupper(c);
}

static char keycode_to_case_char(uint16_t keycode, bool shifted) {
    const char c = autocomplete_keycode_to_char(keycode);
    return shifted ? get_shifted_char(c) : c;
}

static size_t find_last_word_pos(const char *buffer) {
    if (buffer == NULL || *buffer == '\0') {
        return 0;
    }

    const size_t len = strlen(buffer);

    if (len == 0) {
        return 0;
    }

    // Start from the end of the buffer and move backwards until a non-space character or the beginning of the buffer is found
    ssize_t pos = len - 1;
    while (pos >= 0 && isspace((int)buffer[pos])) {
        --pos;
    }

    // Keep moving backwards until a space character or the beginning of the buffer is found
    while (pos >= 0 && !isspace((int)buffer[pos])) {
        --pos;
    }

    // Return the position of the last word
    return pos + 1;
}

static bool has_upper(const char *str, const size_t max_len) {
    for (size_t i = 0; str[i] != '\0' && i < max_len; ++i) {
        if (isupper((unsigned char)str[i])) {
            return true;
        }
    }
    return false;
}

static bool is_all_upper(const char *str, const size_t max_len) {
    for (size_t i = 0; str[i] != '\0' && i < max_len; ++i) {
        if (!isupper((unsigned char)str[i])) {
            return false;
        }
    }
    return true;
}

static int word_cmp(const char *word, const char *prefix_word, const size_t prefix_word_len) {
    if (has_upper(word, prefix_word_len)) {
        return strncmp(word, prefix_word, prefix_word_len);
    }
    return strncasecmp(word, prefix_word, prefix_word_len);
}

static ssize_t autocomplete_search_min(const char **words, const size_t max_size, const size_t start_index, const char *prefix_word, const size_t prefix_word_len, char *result, const size_t min_completion, const int num_skips) {
    int skips = num_skips;
    for (size_t index = start_index; index < max_size; ++index) {
        const char *word = words[index];
        if (word == NULL) {
            break;
        }
        const size_t word_len = strlen(word);
        if (word_len > prefix_word_len + min_completion && word_cmp(word, prefix_word, prefix_word_len) == 0) {
            if (skips > 0) {
                --skips;
                continue;
            }

            // Set remaining characters to complete the word
            const char  *remaining = word + prefix_word_len;
            const size_t len       = strlen(remaining);
            strncpy(result, remaining, MIN(len, MAX_WORD_LENGTH));
            result[len] = '\0';
            return index;
        }
    }

    return -1;
}

static bool is_end_of_sentence(const char *str) {
    int length = strlen(str);

    // Trim whitespace characters at the end of the string
    while (length > 0 && isspace((int)str[length - 1])) {
        length--;
    }

    // Check if the last non-whitespace character is a period, exclamation mark, or question mark
    if (length > 0 && (str[length - 1] == '.' || str[length - 1] == '!' || str[length - 1] == '?')) {
        return true; // End of a sentence
    } else {
        return false; // Not the end of a sentence
    }
}

static __ssize_t autocomplete_run(const char **words, const size_t words_len, size_t start_index, const char *prefix_word, const size_t prefix_word_len, char *result, const int num_skips) {
    ssize_t found_index = -1;

    // Suggestion loop
    for (int i = 0; i < 2; ++i) {
        if (i != 0) {
            if (start_index == 0) {
                break;
            }
            start_index = 0;
        }

        for (ssize_t min_completion = 1; min_completion >= 0; --min_completion) {
            found_index = autocomplete_search_min(words, words_len, start_index, prefix_word, prefix_word_len, result, min_completion, num_skips);
            if (found_index >= 0) {
                if (found_index == last_autocomplete.index && min_completion == 1) {
                    continue;
                }
                return found_index;
            }
        }
    }

    return -1;
}

static ssize_t autocomplete(const char *prefix_word, const uint8_t *word_mods, const int num_skips, char *result) {
    result[0]                    = '\0';
    const size_t prefix_word_len = strlen(prefix_word);
    size_t       start_index;
    bool         initial_run;

    if (last_autocomplete.index >= 0) {
        start_index = last_autocomplete.index + 1;
        initial_run = false;
    } else {
        start_index = 0;
        initial_run = true;
    }

    const char **words;
    size_t       words_len;

    if (prefix_word_len <= 0 || is_end_of_sentence(prefix_word)) {
        words     = start_words;
        words_len = start_words_len;
    } else {
        char      start_letter = tolower(prefix_word[0]);
        const int index        = start_letter - 'a';

        if (index < 0 || index >= ALPHABET_SIZE) {
            return -1; // Invalid prefix
        }

        if (start_letter == 'c' && (word_mods[0] & MOD_BIT(KC_RIGHT_ALT))) {
            words     = c_cedilla_words;
            words_len = c_cedilla_words_len;
        } else {
            words     = autocomplete_data[index];
            words_len = MAX_AUTOCOMPLETE;
        }
    }

    ssize_t found_index;

    if (initial_run && prefix_word_len > 1) {
        char         initial_word[prefix_word_len];
        const size_t initial_word_len = prefix_word_len - 1;
        strncpy(initial_word, prefix_word, initial_word_len);
        initial_word[initial_word_len] = '\0';
        found_index = autocomplete_run(words, words_len, start_index, initial_word, initial_word_len, result, num_skips);
        if (found_index >= 0) {
            result[0]   = '\0';
            found_index = autocomplete_run(words, words_len, found_index + 1, prefix_word, prefix_word_len, result, 0);
        }
    } else {
        found_index = autocomplete_run(words, words_len, start_index, prefix_word, prefix_word_len, result, num_skips);
    }

    if (found_index >= 0) {
        return found_index;
    }

    // Fallback
    if (isspace((int)prefix_word[prefix_word_len - 1])) {
        strcpy(result, "the ");
        return 0;
    }

    return found_index;
}

//  Like strpbrk, but also takes camelCase into account.
static const char *strchr_multiple(const char *str) {
    static const char *char_set = " -_.,";
    const char        *original = str;

    while (*str != '\0') {
        if (isupper((unsigned char)*str) && str != original) {
            return --str;
        }
        const char *ch = char_set;
        while (*ch != '\0') {
            if (*str == *ch) {
                return str;
            }
            ch++;
        }
        str++;
    }

    return NULL;
}

static void send_string_auto_unicode(const char *str) {
    SEND_STRING(str);
    // int length = strlen(str);
    // int i      = 0;

    // while (i < length) {
    //     if ((unsigned char)str[i] <= 127) {
    //         // Plain ASCII character
    //         int j = i;
    //         while (j < length && (unsigned char)str[j] <= 127) {
    //             j++;
    //         }
    //         // Send the plain ASCII substring
    //         char plain_ascii[j - i + 1];
    //         strncpy(plain_ascii, &str[i], j - i);
    //         plain_ascii[j - i] = '\0';
    //         SEND_STRING(plain_ascii);
    //         i = j;
    //     } else {
    //         // Non-ASCII character
    //         int j = i;
    //         while (j < length && (unsigned char)str[j] > 127) {
    //             j++;
    //         }
    //         // Send the UTF-8 substring
    //         char utf8[j - i + 1];
    //         strncpy(utf8, &str[i], j - i);
    //         utf8[j - i] = '\0';
    //         send_unicode_string(utf8);
    //         i = j;
    //     }
    // }
}

static void convert_to_uppercase(char *str) {
    size_t i = 0;
    while (str[i] != '\0') {
        str[i] = toupper(str[i]);
        ++i;
    }
}

bool process_autocomplete(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    // Reset if word tracking becomes uncertain.
    if (((all_mods & MOD_MASK_CG) || (all_mods & MOD_BIT(KC_LEFT_ALT))) && keycode != U_QUOP) {
        reset_word();
        return true;
    }

    // let through anything above that's normal keyboard keycode or a mod
    if (IS_MODIFIER_KEYCODE(keycode)) {
        return true;
    }

    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            // case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            if (record->tap.count == 0) {
                return true;
            }
            keycode = keycode & 0xFF;
            break;
        case U_QUOP:
            keycode = CM_QUOT;
            break;
    }

    if (keycode == KC_ESCAPE) {
        reset_word();
        return true;
    }

    if (keycode == U_AUTOCOMPLETE || keycode == U_AUTOCOMPLETE2 || keycode == U_AUTOCOMPLETE3) {
        // Autocomplete the word based on the current input

        if (last_autocomplete.index >= 0) {
            current_word_length -= last_autocomplete.size;
            current_word[current_word_length] = '\0';

            char backspace_str[MAX_WORD_LENGTH];
            memset(backspace_str, '\b', MIN(last_autocomplete.size, MAX_WORD_LENGTH));
            backspace_str[last_autocomplete.size] = '\0';
            SEND_STRING(backspace_str);
        }

        int num_skips;

        switch (keycode) {
            case U_AUTOCOMPLETE:
                num_skips = 0;
                break;
            case U_AUTOCOMPLETE2:
                num_skips = 1;
                break;
            case U_AUTOCOMPLETE3:
                num_skips = 2;
                break;
            default:
                return true;
        }

        size_t      position    = 0;
        const char *token       = current_word;
        ssize_t     found_index = -1;

        while (1) {
            const uint8_t *word_mods = current_word_mods + position;

            if ((found_index = autocomplete(token, word_mods, num_skips, autocomplete_result)) >= 0) {
                break;
            }

            token = strchr_multiple(token);

            if (token == NULL) {
                break;
            }

            position = ++token - current_word;
        }

        if (autocomplete_result[0] != '\0') {
            const bool shifted = (all_mods && MOD_MASK_SHIFT) || is_caps_word_on();
            char      *result;

            if (shifted || (token != NULL && strlen(token) > 1 && is_all_upper(token, MAX_WORD_LENGTH))) {
                char result_upper[MAX_WORD_LENGTH + 1];
                strcpy(result_upper, autocomplete_result);
                convert_to_uppercase(result_upper);
                result = result_upper;
            } else {
                result = autocomplete_result;
            }

            send_string_auto_unicode(result);
            const size_t autocomplete_len = strlen(autocomplete_result);
            const size_t new_len          = current_word_length + autocomplete_len;

            last_autocomplete.index = found_index;
            last_autocomplete.size  = autocomplete_len;

            if (new_len > MAX_WORD_LENGTH) {
                // Rotate to make room.
                memmove(current_word, current_word + autocomplete_len, MAX_WORD_LENGTH - 1);
                current_word_length = MAX_WORD_LENGTH - autocomplete_len;
            }
            strncpy(current_word + current_word_length, autocomplete_result, MIN(autocomplete_len, MAX_WORD_LENGTH));
            current_word_length += autocomplete_len;
            current_word[current_word_length] = '\0';
        }
        return false;
    }

    if (last_autocomplete.index >= 0) {
        last_autocomplete.index = -1;
        last_autocomplete.size  = 0;
    }

    if (keycode == KC_BACKSPACE) {
        if (all_mods & MOD_MASK_CTRL) {
            // Currently not used
            const size_t word_pos             = find_last_word_pos(current_word);
            current_word_length               = word_pos;
            current_word[current_word_length] = '\0';
        } else if (current_word_length > 0) {
            // Remove the last character from the word
            current_word[--current_word_length] = '\0';
        }
    } else if (is_allowed_in_buffer(keycode)) {
        // If the buffer is full, rotate it to discard the oldest character.
        if (current_word_length >= MAX_WORD_LENGTH) {
            memmove(current_word, current_word + 1, MAX_WORD_LENGTH - 1);
            current_word_length = MAX_WORD_LENGTH - 1;
        }

        // Add the pressed key to the current word
        const bool shifted                     = (all_mods & MOD_MASK_SHIFT) || is_caps_word_on();
        current_word_mods[current_word_length] = all_mods;
        current_word[current_word_length++]    = keycode_to_case_char(keycode, shifted);
        current_word[current_word_length]      = '\0'; // Null-terminate the word
    } else {
        // Non-alphanumeric key pressed
        reset_word();
    }

    return true;
}

char *get_current_word(void) {
    if (!current_word_length) {
        return NULL;
    }
    return current_word;
}

uint8_t get_current_word_length(void) {
    return current_word_length;
}
