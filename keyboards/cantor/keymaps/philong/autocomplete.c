#include "autocomplete.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH 20

static char    current_word[MAX_WORD_LENGTH + 1];      // Stores the current word being typed
static uint8_t current_word_mods[MAX_WORD_LENGTH + 1]; // Stores the mods in the current word
static uint8_t current_word_length = 0;                // Length of the current word

static char autocomplete_result[MAX_WORD_LENGTH + 1] = "";

#define ALPHABET_SIZE 26
#define MAX_WORDS 52

static const char *PROGMEM autocomplete_list[ALPHABET_SIZE][MAX_WORDS] = {
    {"async", "await", "add", "array", "arrays", "abstract", "and", "args", "arg", "arguments", "assert", "auto", "annotation", "actual", "alias", "abbr", "arrow", "alter", "average", "atom", "atomic", "abs", "absolute", "all", "allow", "allowed", "author", "authorize", "authorized", NULL},
    {"break", "bool", "boolean", "byte", "begin", "base", "become", "blank", "bad", "bisect", "branch", "back", "between", "boot", "because", NULL},
    {"class", "const", "catch", "case", "child", "children", "char", "character", "cache", "close", "current", "collection", "collections", "continue", "context", "contains", "constructor", "comment", "comments", "computer", "cpu", "companion", "copy", "copyright", "copyleft", "commit", "command", "create", "count", "clone", "check", "call", "callback", "callbacks", "control", "chrome", "cancel", "cursor", NULL},
    {"data", "def", "define", "del", "delete", "default", "dict", "double", "dummy", "decimal", "develop", "debug", "debugger", "dynamic", "delegate", "duplicate", "domain", "domains", "done", "down", "divide", "diagonal", "diff", "drop", "distinct", "discard", "draft", NULL},
    {"else", "except", "exception", "enum", "end", "echo", "event", "export", "exports", "error", "extends", "elif", "explicit", "extern", "external", "expect", "expected", "empty", "enter", "escape", "effect", "each", "extra", "extract", "example", "examples", NULL},
    {"final", "false", "for", "forEach", "function", "float", "from", "friend", "field", "file", "full", "fetch", "forbid", "forbidden", "forward", "free", "fail", "failure", "find", "found", "first", NULL},
    {"get", "getter", "group", "group by", "goto", "global", "generic", "git", "good", "gpu", NULL},
    {"hidden", "How are you?", "has", "hash", "help", "header", "have", "having", "hour", "hours", "host", "high", "hibernate", "hello", "Hello, World!", "heap", NULL},
    {"interface", "implement", "implements", "int", "integer", "index", "indexes", "input", "instance", "instanceof", "import", "imports", "include", "inline", "implicit", "intern", "internal", "international", "internationalization", "inner", "init", "initialize", "insert", NULL},
    {"join", "json", "jump", "java", "javascript", NULL},
    {"key", "keyword", "keywords", "kill", "killall", "kind", "keep", "keyboard", "kernel", NULL},
    {"len", "length", "let", "list", "long", "lock", "lambda", "log", "login", "logout", "logger", "local", "location", "localization", "loop", "left", "line", "like", "layout", "liquid", "load", "loading", "low", "listen", "listener", "listeners", "little", "level", "levels", NULL},
    {"map", "main", "module", "mutable", "match", "matches", "method", "month", "master", "mutable", "max", "maximize", "maximum", "min", "minimize", "minimum", "minus", "merge", "multi", "multiply", "model", "models", "move", "memo", "mean", "malloc", "mem", "memory", "medium", "minute", "minutes", "milli", "millisecond", "milliseconds", "micro", "microsecond", "microseconds", "normal", "mouse", "mask", NULL},
    {"null", "name", "namespace", "next", "none", "node", "number", "numeric", "native", "nonlocal", "net", "nil", "npm", "not", "new", NULL},
    {"object", "override", "output", "operator", "open", "order", "old", "original", "optional", "org", NULL},
    {"public", "print", "println", "private", "protected", "push", "pop", "python", "package", "pointer", "position", "previous", "permits", "provides", "parent", "pass", "property", "param", "parameter", "parameters", "prefix", "post", "pull", "produce", "protocol", "password", "plus", "percent", "parse", "play", "player", "put", "phone", "project", "projects", "purchase", "purchases", NULL},
    {"query", "queue", "quit", "quote", NULL},
    {"return", "returns", "read", "raise", "ref", "reference", "require", "required", "run", "record", "records", "register", "receiver", "remote", "reduce", "reducer", "redo", "right", "range", "react", "remove", "restart", "reboot", "round", "random", "restrict", "restricted", "recipe", "retry", NULL},
    {"str", "string", "switch", "super", "static", "stash", "struct", "self", "system", "size", "sizeof", "synchronized", "set", "setter", "success", "successful", "short", "socket", "select", "select * from ", "sealed", "signed", "suffix", "suspend", "status", "shift", "sql", "sort", "sorted", "solid", "state", "sum", "start", "startup", "stop", "shutdown", "store", "small", "simple", "second", "seconds", "standard", "stage", "smart", "smartphone", "smartphones", "script", "split", "search", "sale", "sales", NULL},
    {"this", "throw", "true", "type", "typeof", "typescript", "temp", "transaction", "transactional", "transient", "transitive", "then", "template", "try", "table", "tuple", "title", "that", "those", "telephone", "telephones", NULL},
    {"undefined", "update", "updater", "use", "useState", "useEffect", "useMemo", "useCallback", "useRef", "useContext", "useReducer", "union", "url", "using", "user", "username", "unsigned", "undef", "unless", "upstream", "upsert", NULL},
    {"value", "valueOf", "void", "var", "variable", "variables", "varchar", "volatile", "vector", "virtual", "via", "view", NULL},
    {"while", "where", "write", "with", "warning", "week", "wide", "web", "www", "wchar_t", "word", "words", "world", "window", "windows", NULL},
    {"xml", "xor", "xpath", NULL},
    {"yield", "yes", "yarn", "year", NULL},
    {"zip", "zero", "zone", "zoom", NULL},
};

static const char *PROGMEM extra_autocomplete_list[ALPHABET_SIZE][MAX_WORDS] = {
    {"Android", "Amazon", "Apple", "Axelor", "And you?", NULL},                                      // a
    {"bonjour", NULL},                                                                               // b
    {NULL},                                                                                          // c
    {NULL},                                                                                          // d
    {NULL},                                                                                          // e
    {"firefox", NULL},                                                                               // f
    {"Google", NULL},                                                                                // g
    {"Hi, how are you?", NULL},                                                                      // h
    {"i18n", "I'm fine, thanks.", NULL},                                                             // i
    {"jpql", "jpa", NULL},                                                                           // j
    {NULL},                                                                                          // k
    {"l10n", "Linux", NULL},                                                                         // l
    {"Microsoft", NULL},                                                                             // m
    {NULL},                                                                                          // n
    {NULL},                                                                                          // o
    {"pnpm", "Phi-Long", "Phi-Long Do", "philong", "philong.do@gmail.com", "p.do@axelor.com", NULL}, // p
    {"qmk", NULL},                                                                                   // q
    {NULL},                                                                                          // r
    {"salut", NULL},                                                                                 // s
    {NULL},                                                                                          // t
    {"Unix", "Ubuntu", NULL},                                                                        // u
    {"Vial", NULL},                                                                                  // v
    {NULL},                                                                                          // w
    {NULL},                                                                                          // x
    {NULL},                                                                                          // y
    {NULL},                                                                                          // z
};

static void reset_word(void) {
    if (current_word_length > 0) {
        current_word_length = 0;
        current_word[0]     = '\0';
    }
}

static bool is_allowed_in_buffer(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_SCLN:
        case CM_LBRC:
        case CM_RBRC:
        case CM_BSLS:
        case CM_QUOT:
        case CM_COMM:
        case CM_DOT:
        case CM_SLSH:
        case KC_SPACE:
        case KC_TAB:
        case CM_1 ... CM_0:
        case CM_MINS:
        case CM_EQL:
        case CM_GRV:
            return true;

        default:
            return false;
    }
}

static char keycode_to_char(uint16_t keycode) {
    switch (keycode) {
        case CM_A:
            return 'a';
        case CM_B:
            return 'b';
        case CM_C:
            return 'c';
        case CM_D:
            return 'd';
        case CM_E:
            return 'e';
        case CM_F:
            return 'f';
        case CM_G:
            return 'g';
        case CM_H:
            return 'h';
        case CM_I:
            return 'i';
        case CM_J:
            return 'j';
        case CM_K:
            return 'k';
        case CM_L:
            return 'l';
        case CM_M:
            return 'm';
        case CM_N:
            return 'n';
        case CM_O:
            return 'o';
        case CM_P:
            return 'p';
        case CM_Q:
            return 'q';
        case CM_R:
            return 'r';
        case CM_S:
            return 's';
        case CM_T:
            return 't';
        case CM_U:
            return 'u';
        case CM_V:
            return 'v';
        case CM_W:
            return 'w';
        case CM_X:
            return 'x';
        case CM_Y:
            return 'y';
        case CM_Z:
            return 'z';
        case CM_QUOT:
            return '\'';
        case CM_DOT:
            return '.';
        case CM_COMM:
            return ',';
        case CM_MINS:
            return '-';

        case CM_1:
            return '1';
        case CM_2:
            return '2';
        case CM_3:
            return '3';
        case CM_4:
            return '4';
        case CM_5:
            return '5';
        case CM_6:
            return '6';
        case CM_7:
            return '7';
        case CM_8:
            return '8';
        case CM_9:
            return '9';
        case CM_0:
            return '0';

        default:
            return ' ';
    }
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

static bool autocomplete_search(const char **words, const char *prefix_word, const size_t prefix_word_len, char *result) {
    for (size_t i = 0; i < MAX_WORDS; ++i) {
        const char *word = words[i];
        if (word == NULL) {
            return false;
        }
        const size_t word_len = strlen(word);
        if (word_len > prefix_word_len && strncasecmp(word, prefix_word, prefix_word_len) == 0) {
            // Set remaining characters to complete the word
            const char  *remaining = word + prefix_word_len;
            const size_t len       = strlen(remaining);
            strncpy(result, remaining, len);
            result[len] = '\0';
            return true;
        }
    }

    return false;
}

static bool autocomplete(const char *prefix_word, const uint8_t *word_mods, char *result) {
    const size_t prefix_word_len = strlen(prefix_word);

    if (prefix_word_len <= 0) {
        strcpy(result, "I ");
        return false;
    }

    const int index = prefix_word[0] - 'a';

    if (index < 0 || index >= ALPHABET_SIZE) {
        result[0] = '\0';
        return false; // Invalid prefix
    }

    // TODO: handle more cases via a lookup table
    if (prefix_word[0] == 'c' && (word_mods[0] & MOD_BIT(KC_RIGHT_ALT))) {
        const char *completion = "a va";
        strcpy(result, completion);
        return true;
    }

    bool found = autocomplete_search(autocomplete_list[index], prefix_word, prefix_word_len, result);

    if (!found) {
        found = autocomplete_search(extra_autocomplete_list[index], prefix_word, prefix_word_len, result);
        if (!found) {
            result[0] = '\0';
        }
    }

    return found;
}

bool process_autocomplete(uint16_t keycode, keyrecord_t *record, uint16_t autocomplete_keycode) {
    if (!record->event.pressed) {
        return true;
    }

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = mods | get_weak_mods() | get_oneshot_mods();

    // Reset if word tracking becomes uncertain.
    if ((all_mods & MOD_MASK_CG) || (all_mods & MOD_BIT(KC_LEFT_ALT))) {
        reset_word();
        return true;
    }

    // let through anything above that's normal keyboard keycode or a mod
    if (IS_MOD(keycode) || keycode == KC_ESCAPE) {
        return true;
    }

    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            if (record->tap.count == 0) {
                return true;
            }
            keycode = keycode & 0xFF;
    }

    if (keycode == autocomplete_keycode) {
        // Autocomplete the word based on the current input
        const size_t   word_pos  = find_last_word_pos(current_word);
        const char    *word      = current_word + word_pos;
        const uint8_t *word_mods = current_word_mods + word_pos;
        autocomplete(word, word_mods, autocomplete_result);

        // uprintf("current_word: %s, current_word_length: %d, word_pos: %d\n", current_word, current_word_length, word_pos);
        // uprintf("autocomplete_result: %s\n", autocomplete_result);

        if (autocomplete_result[0] != '\0') {
            SEND_STRING(autocomplete_result);
            const size_t autocomplete_len = strlen(autocomplete_result);
            const size_t new_len          = current_word_length + autocomplete_len;
            if (new_len > MAX_WORD_LENGTH) {
                // Rotate to make room.
                memmove(current_word, current_word + autocomplete_len, MAX_WORD_LENGTH - 1);
                current_word_length = MAX_WORD_LENGTH - autocomplete_len;
            }
            strncpy(current_word + current_word_length, autocomplete_result, autocomplete_len);
            current_word_length += autocomplete_len;
            current_word[current_word_length] = '\0';

            // uprintf("r: current_word: %s, current_word_length: %d\n", current_word, current_word_length);
        }
        return false;
    } else if (keycode == KC_BACKSPACE) {
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
        current_word_mods[current_word_length] = all_mods;
        current_word[current_word_length++]    = keycode_to_char(keycode);
        current_word[current_word_length]      = '\0'; // Null-terminate the word
    } else {
        // Non-alphanumeric key pressed
        reset_word();
    }

    return true;
}
