#include "autocomplete.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LENGTH 20

static char    current_word[MAX_WORD_LENGTH + 1];      // Stores the current word being typed
static uint8_t current_word_mods[MAX_WORD_LENGTH + 1]; // Stores the mods in the current word
static uint8_t current_word_length = 0;                // Length of the current word

static char autocomplete_result[MAX_WORD_LENGTH + 1] = "";

struct last_autocomplete {
    ssize_t index;
    size_t  size;
};

static struct last_autocomplete last_autocomplete = {-1, 0};

#define ALPHABET_SIZE 26
#define MAX_AUTOCOMPLETE 105

static const char *PROGMEM autocomplete_list[ALPHABET_SIZE][MAX_AUTOCOMPLETE] = {
    {"async", "asynchronous", "asynchronously", "await", "add", "addition", "array", "arrays", "abstract", "and", "args", "arg", "arguments", "assert", "auto", "annotation", "actual", "alias", "abbr", "arrow", "alter", "average", "atom", "atomic", "abs", "absolute", "all", "allow", "allowed", "author", "authorize", "authorized", "affect", "affects", "affected", "app", "application", "applications", "also", "alternate", "alternative", "alternatives", "advanced", "adapt", "adaptor", "adaptors", "address", "addresses", "avatar", "animate", "animation", "align", "accent", "accents", "after", "area", "anomaly", /*extra*/ "android", "amazon", "apple", "axelor", "and you?", NULL},
    {"break", "breaks", "bool", "boolean", "byte", "bytes", "begin", "base", "basic", "become", "blank", "bad", "bisect", "branch", "branches", "back", "background", "backend", "between", "boot", "because", "bug", "bugfix", "block", "blocked", "build", "builder", "black", "blue", "border", "bottom", "before", /*extra*/ "bonjour", NULL},
    {"class", "classes", "const", "catch", "case", "cases", "child", "children", "char", "character", "cache", "close", "closed", "current", "col", "collect", "collection", "collections", "collector", "column", "columns", "continue", "content", "contents", "context", "contexts", "contains", "constructor", "comment", "comments", "compute", "computer", "computers", "cpu", "companion", "copy", "copyright", "copyleft", "commit", "commits", "command", "commands", "create", "count", "counts", "clone", "check", "call", "callback", "callbacks", "control", "controller", "controllers", "cancel", "cursor", "code", "custom", "condition", "conditional", "clear", "clean", "change", "changes", "calculate", "calculator", "calculators", "channel", "channels", "cast", "connect", "connection", "convert", "conversion", "compile", "compiler", "chat", "chatbot", "color", "colors", "collapse", "circle", "calendar", "card", "cards", "country", "countries", /*extra*/ "chrome", NULL},
    {"data", "def", "define", "definition", "definitions", "del", "delete", "deleted", "deletion", "default", "dict", "double", "dummy", "decimal", "debug", "debugger", "dynamic", "delegate", "duplicate", "domain", "domains", "done", "down", "download", "downloaded", "downloading", "divide", "diagonal", "diff", "difference", "drop", "distinct", "discard", "draft", "dev", "develop", "development", "developer", "developers", "design", "designer", "designers", "doc", "documentation", "decode", "decoder", "decoders", "day", "days", "dir", "direction", "directions", "directory", "directories", "device", "devices", "display", "dirty", "digit", "digits", "decoration", "dest", "destination", NULL},
    {"elem", "element", "elements", "else", "except", "exception", "expr", "expression", "enum", "end", "env", "environment", "echo", "event", "export", "exports", "error", "extends", "elif", "explicit", "extern", "external", "expect", "expected", "empty", "enter", "escape", "effect", "effects", "each", "extra", "extract", "example", "examples", "etc.", "effect", "effects", "engine", "engineer", "engineering", "even", "event", "events", "encoding", "encode", "encoder", "encoders", "encrypt", "encryption", "encryptions", "edit", "editor", "erase", "execute", "executor", NULL},
    {"final", "false", "for", "forEach", "function", "float", "from", "front", "frontend", "friend", "friends", "field", "fields", "file", "filename", "filenames", "filter", "filters", "full", "fetch", "forbid", "forbidden", "forward", "foreground", "free", "fail", "failure", "find", "found", "first", "feature", "features", "frame", "framework", "few", "fewer", "folder", "folders", "fast", "firmware", "focus", "fall", "fallback", "family", "future", "form", /*extra*/ "firefox", NULL},
    {"get", "getter", "getters", "group", "group by", "global", "generic", "git", "good", "gpu", "garbage", "graph", "graphic", "graphics", "giga", "gigabytes", "green", "gray", "grid", "gantt", /*extra*/ "google", "goto", NULL},
    {"hidden", "hello", "how", "has", "hash", "help", "header", "have", "having", "home", "hour", "hours", "host", "high", "html", "http", "https", "hard", "hardware", "heap", "hook", "hooks", "height", "history", /*extra*/ "how are you?", "hi, how are you?", "hello, World!", NULL},
    {"item", "items", "interface", "implement", "implements", "int", "integer", "index", "indexes", "input", "instance", "instanceof", "import", "imports", "include", "inline", "implicit", "intern", "internal", "international", "internationalization", "inner", "init", "initial", "initialize", "initialization", "insert", "invert", "issue", "issues", "instruction", "instructions", "image", "images", "inherit", "inheritance", /*extra*/ "i18n", "in progress", "i'm fine, thanks.", NULL},
    {"join", "json", "jump", "java", "javascript", "job", "jobs", /*extra*/ "jpql", "jpa", NULL},
    {"key", "keyword", "keywords", "kill", "killall", "kind", "keep", "keyboard", "kernel", "kanban", NULL},
    {"len", "length", "let", "list", "long", "lock", "locked", "lambda", "log", "login", "logout", "logger", "local", "location", "localization", "loop", "left", "line", "lines", "like", "likes", "layout", "layouts", "liquid", "load", "loading", "loader", "loaders", "low", "lower", "lowercase", "listen", "listener", "listeners", "lib", "library", "libraries", "little", "level", "levels", "less", "link", "linking", "last", /*extra*/ "l10n", "linux", NULL},
    {"map", "main", "module", "mutable", "match", "matches", "method", "menu", "menus", "month", "months", "master", "mutable", "max", "maximize", "maximum", "min", "minimize", "minimum", "minus", "merge", "multi", "multiply", "model", "models", "move", "memo", "memoize", "memoized", "memory", "mean", "malloc", "medium", "minute", "minutes", "milli", "millisecond", "milliseconds", "micro", "microsecond", "microseconds", "normal", "mouse", "mask", "maintain", "maintainance", "manage", "manager", "managers", "management", "material", "more", "manifest", "mega", "megabytes", "modify", "make", "margin", "monitor", "matrix", /*extra*/ "microsoft", NULL},
    {"null", "name", "namespace", "next", "none", "node", "number", "numbers", "numeric", "native", "nonlocal", "net", "nil", "npm", "not", "new", "nest", "nested", NULL},
    {"object", "override", "overridden", "output", "operator", "operators", "operation", "operations", "open", "order", "ordered", "old", "original", "optional", "org", "odd", "orange", NULL},
    {"public", "print", "println", "private", "protected", "push", "pop", "python", "package", "pointer", "position", "previous", "permits", "person", "personal", "provides", "parent", "pass", "property", "properties", "pseudo", "param", "parameter", "parameters", "prefix", "post", "pull", "prod", "production", "produce", "protocol", "password", "plus", "percent", "percentage", "parse", "parser", "play", "player", "platform", "put", "phone", "project", "projects", "purchase", "purchases", "program", "programming", "problem", "problems", "progress", "progressive", "press", "pressed", "publish", "published", "process", "processor", "processors", "processing", "procedure", "precision", "picture", "pink", "padding", "propose", "proposal", "popup", /*extra*/ "pnpm", "Phi-Long", "Phi-Long Do", "philong", "philong.do@gmail.com", "p.do@axelor.com", NULL},
    {"query", "queue", "quit", "quote", /*extra*/ "qmk", NULL},
    {"return", "returns", "read", "raise", "ref", "reference", "references", "require", "required", "run", "record", "records", "register", "receiver", "remote", "reduce", "reducer", "redo", "right", "range", "react", "remove", "removal", "restart", "reboot", "round", "random", "restrict", "restricted", "recipe", "retry", "retries", "reproduce", "request", "requests", "response", "responses", "responsive", "release", "released", "role", "roles", "replay", "rule", "rules", "root", "room", "rooms", "result", "results", "resume", "resource", "resources", "repo", "repository", "report", "reports", "resolution", "red", "regex", "row", "rows", "rgb", "reverse", "reversed", /*extra*/ "salut", NULL},
    {"str",    "string",  "strings",  "switch", "super",   "static", "stash",      "struct",      "self",   "system", "size",  "sizeof", "synchronized", "set",      "setting", "settings", "setter", "setters",  "success",   "successful", "successfully", "show",    "showcase",   "short",       "socket",         "select",  "selector", "selectors", "select * from ", "sealed", "signed", "suffix", "suspend", "status",       "shift",       "sql",           "sort",   "sorted", "solid",  "state",      "states",      "sum",      "summary", "start", "startup", "stop",   "stops", "shut",   "shutdown", "store",   "small",      "similar", "simple",
     "second", "seconds", "standard", "stage",  "staging", "smart",  "smartphone", "smartphones", "script", "split",  "space", "spacer", "search",       "searches", "soft",    "software", "seems",  "separate", "separator", "sound",      "sounds",       "special", "specialize", "specialized", "specialization", "service", "services", "speed",     "slice",          "splice", "scale",  "slow",   "sync",    "synchronized", "synchronous", "synchronously", "single", "should", "screen", "screenshot", "screenshots", "subtract", "swap",    "style", "strong",  "source", "src",   "square", "shell",    "suggest", "suggestion", NULL},
    {"this", "throw", "true", "type", "typeof", "typescript", "temp", "temporary", "transaction", "transactional", "transient", "transitive", "then", "template", "try", "table", "tuple", "title", "that", "those", "telephone", "telephones", "ticket", "tickets", "time", "times", "timer", "timers", "too", "tools", "transition", "transitioning", "tera", "terabytes", "thread", "threads", "threading", "translation", "translations", "task", "tasks", "trigger", "triggers", "total", "track", "tracking", "trackers", "trackers", "text", "transform", "transformation", "transparent", "transport", "top", "triangle", "tmp", NULL},
    {"undefined", "update", "updated", "updater", "use", "useState", "useEffect", "useMemo", "useCallback", "useRef", "useReducer", "useTransition", "useId", "useContext", "union", "url", "using", "user", "username", "unsigned", "undef", "unless", "upstream", "upsert", "util", "utils", "undo", "up", "upload", "uploaded", "uploading", "upper", "uppercase", "unicode", "utf-8", "unix", "ubuntu", NULL},
    {"value", "valueOf", "void", "var", "variable", "variables", "variant", "variants", "varchar", "volatile", "vector", "virtual", "via", "view", "views", "validate", "validator", "visible", "visibility", "video", "videos", "venv", NULL},
    {"while", "where", "write", "with", "warning", "week", "weeks", "weekend", "wide", "web", "www", "wchar_t", "word", "words", "world", "window", "windows", "work", "worker", "workers", "weak", "would", "will", "with", "within", "white", "width", "weight", /*extra*/ "work in progress", NULL},
    {"xml", "xor", "xpath", NULL},
    {"yield", "yarn", "year", "years", "yellow", "yes", NULL},
    {"zip", "zero", "zone", "zoom", NULL},
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

static char keycode_to_case_char(uint16_t keycode, bool shifted) {
    const char c = keycode_to_char(keycode);
    return shifted ? toupper(c) : c;
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

static bool has_upper(const char *str, const size_t len) {
    for (int i = 0; str[i] != '\0' || i < len; ++i) {
        if (isupper((unsigned char)str[i])) {
            return true;
        }
    }
    return false;
}

static int word_cmp(const char *word, const char *prefix_word, const size_t prefix_word_len) {
    if (has_upper(word, prefix_word_len)) {
        return strncmp(word, prefix_word, prefix_word_len);
    }
    return strncasecmp(word, prefix_word, prefix_word_len);
}

static ssize_t autocomplete_search(const char **words, const size_t max_size, const size_t start_index, const char *prefix_word, const size_t prefix_word_len, char *result) {
    for (size_t index = start_index; index < max_size; ++index) {
        const char *word = words[index];
        if (word == NULL) {
            break;
        }
        const size_t word_len = strlen(word);
        if (word_len > prefix_word_len && word_cmp(word, prefix_word, prefix_word_len) == 0) {
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

static ssize_t autocomplete(const char *prefix_word, const uint8_t *word_mods, char *result) {
    result[0]                    = '\0';
    const size_t prefix_word_len = strlen(prefix_word);
    size_t       start_index;

    if (last_autocomplete.index >= 0) {
        start_index = last_autocomplete.index + 1;
    } else {
        start_index = 0;
    }

    if (prefix_word_len <= 0) {
        strcpy(result, "I ");
        return 0;
    }

    const int index = tolower(prefix_word[0]) - 'a';

    if (index < 0 || index >= ALPHABET_SIZE) {
        return -1; // Invalid prefix
    }

    ssize_t found_index = -1;

    for (int i = 0; i < 2; ++i) {
        if (i != 0) {
            if (start_index == 0) {
                break;
            }
            start_index = 0;
        }

        // TODO: handle more special cases via a lookup table
        if (prefix_word[0] == 'c' && (word_mods[0] & MOD_BIT(KC_RIGHT_ALT))) {
            const char *PROGMEM words[]    = {"ca va", "ca va, et toi ?", NULL};
            const size_t        words_size = sizeof(words) / sizeof(words[0]);
            found_index                    = autocomplete_search(words, words_size, start_index, prefix_word, prefix_word_len, result);
            break;
        }

        if (found_index < 0) {
            found_index = autocomplete_search(autocomplete_list[index], MAX_AUTOCOMPLETE, start_index, prefix_word, prefix_word_len, result);
        }

        if (found_index >= 0) {
            break;
        }
    }

    return found_index;
}

//  Like strpbrk, but also takes camelCase into account.
static const char *strchr_multiple(const char *str) {
    static const char *char_set = " -_.";
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

        // const size_t   word_pos  = find_last_word_pos(current_word);
        // const char    *word      = current_word + word_pos;
        // const uint8_t *word_mods = current_word_mods + word_pos;
        // autocomplete(word, word_mods, autocomplete_result);

        if (last_autocomplete.index >= 0) {
            current_word_length -= last_autocomplete.size;
            current_word[current_word_length] = '\0';

            char backspace_str[MAX_WORD_LENGTH];
            memset(backspace_str, '\b', MIN(last_autocomplete.size, MAX_WORD_LENGTH));
            backspace_str[last_autocomplete.size] = '\0';
            SEND_STRING(backspace_str);
        }

        size_t      position    = 0;
        const char *token       = current_word;
        ssize_t     found_index = -1;

        while (1) {
            const uint8_t *word_mods = current_word_mods + position;

            if ((found_index = autocomplete(token, word_mods, autocomplete_result)) >= 0) {
                break;
            }

            token = strchr_multiple(token);

            if (token == NULL) {
                break;
            }

            position = ++token - current_word;
        }

        if (autocomplete_result[0] != '\0') {
            SEND_STRING(autocomplete_result);
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
        const bool shifted                     = all_mods & MOD_MASK_SHIFT;
        current_word_mods[current_word_length] = all_mods;
        current_word[current_word_length++]    = keycode_to_case_char(keycode, shifted);
        current_word[current_word_length]      = '\0'; // Null-terminate the word
    } else {
        // Non-alphanumeric key pressed
        reset_word();
    }

    return true;
}
