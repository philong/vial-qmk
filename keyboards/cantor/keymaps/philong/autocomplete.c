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
#define MAX_AUTOCOMPLETE 159

static const char *PROGMEM autocomplete_list[ALPHABET_SIZE][MAX_AUTOCOMPLETE] = {
    {"async", "asynchronous", "asynchronously", "await", "add", "addition", "array",  "abstract", "and",  "args",  "arguments", "assert", "auto", "annotation", "actual",    "alias",  "abbr",  "arrow",   "alter",      "average", "atom",       "atomic", "abs",      "absolute", "all",      "allow",   "allowed", "author", "authorize",     "affect",  "affected", "app",     "application", "also",    "alternate", "alternative", "advanced", "adapt",    "adapter",  "address",    "addresses", "avatar",   "animate", "animation", "align",     "accent",     "after",  "area",       "anomaly",   "are",     "about",      "around",  "against", "another", "among",  "along",    "although", "above", "available",
     "again", "age",          "almost",         "able",  "air", "always",   "across", "aircraft", "away", "added", "army",      "attack", "art",  "action",     "according", "amount", "album", "already", "associated", "access",  "additional", "appear", "appeared", "attempt",  "approach", "ability", "act",     "active", "approximately", "adopted", "actually", "account", "announced",   "applied", "accepted",  "animal",      "asked",    "activity", "analysis", "activities", "appointed", "allowing", "ancient", "agreed",    "algorithm", "arithmetic", "assign", "assignment", "aggregate", "augment", "autonomous", "android", "amazon",  "apple",   "axelor", "and you?", NULL},
    {"break", "bool", "boolean", "byte", "begin", "base", "basic", "become", "blank", "bad", "bisect", "branch", "branches", "back", "background", "backend", "between", "boot", "because", "bug", "bugfix", "block", "blocked", "build", "builder", "black", "blue", "border", "bottom", "before", "bin", "binary", "by", "be", "but", "been", "both", "being", "became", "began", "based", "body", "book", "built", "best", "building", "below", "band", "brought", "believed", "business", "better", "beginning", "battle", "behind", "basis", "born", "blood", "billion", "ball", "believe", "bit", "buffer", "bonjour", NULL},
    {"class",   "classes", "const",    "catch",  "case",     "child", "children", "char",      "character", "cache",    "close",  "current", "col",      "collect", "collection", "collector", "column",  "continue",   "content", "context", "contains",  "constructor", "comment", "compute", "console", "cpu",  "companion", "copy",   "copyright", "copyleft",  "commit",  "command",  "create", "count",   "clone",        "check", "call",   "callback", "control", "controller", "cancel",     "cursor",    "code",   "custom", "condition", "conditional", "clear",    "clean",   "change", "changelog", "calculate",  "calculator", "channel", "cast",   "connect",  "connection", "convert", "conversion", "compile", "chat",
     "chatbot", "color",   "collapse", "circle", "calendar", "card",  "country",  "countries", "common",    "complete", "chrome", "can",     "citation", "could",   "called",     "city",      "century", "considered", "came",    "created", "continued", "certain",     "company", "cause",   "cannot",  "come", "culture",   "cities", "computer",  "community", "complex", "commonly", "court",  "central", "construction", "cost",  "church", "capital",  "career",  "companies",  "commercial", "christian", "course", "center", "concept",   "carried",     "compared", "contain", "cell",   "cut",       "completely", "campaign",   "claimed", "charge", "cultural", "camel",      "circuit", "c++",        NULL},
    {"data", "def", "define", "definition", "del", "delete", "deletion", "default", "dict", "double", "dummy", "decimal", "debug", "debugger", "dynamic", "delegate", "duplicate", "domain", "done", "down", "download", "downloaded", "downloading", "divide", "diagonal", "diff", "difference", "drop", "distinct", "discard", "draft", "dev", "develop", "development", "developer", "design", "designer", "doc", "documentation", "decode", "day", "dir", "direction", "directory", "directories", "device", "display", "dirty", "digit", "decoration", "dest", "destination", "dry", "dark", "during", "different", "did", "do", "due", "death", "does", "developed", "died", "detail", "description", "describe", "described", "designed", "difficult", "directly", "decided", "defined", "direct", "distance", "divided", "date", "degree", "discovered", "decrement", NULL},
    {"elem", "element", "else", "except", "exception", "expr", "expression", "enum", "end", "env", "environment", "echo", "even", "export", "error", "extends", "elif", "explicit", "extern", "external", "expect", "expected", "empty", "enter", "escape", "effect", "each", "extra", "extract", "example", "etc.", "engine", "engineer", "engineering", "encoding", "encode", "encrypt", "encryption", "edit", "editor", "erase", "exec", "execute", "executor", "exclude", "early", "either", "every", "energy", "especially", "established", "economic", "event", "eventually", "evidence", "enough", "education", "entire", "earlier", "ever", "experience", "economy", "exist", "elected", "ended", "eight", "estimated", "equipment", "edition", "easily", "extended", "equal", "effective", "easy", "easily", "emoji", "et toi ?", NULL},
    {"final", "false", "for", "forEach", "function", "float", "from", "front", "frontend", "friend", "field", "file", "filename", "filter", "full", "fetch", "forbid", "forbidden", "forward", "foreground", "free", "fail", "failure", "find", "found", "first", "feature", "frame", "framework", "few", "fewer", "folder", "fast", "firmware", "focus", "fall", "fallback", "family", "future", "firefox", "four", "film", "following", "further", "five", "force", "followed", "fact", "far", "food", "former", "father", "formed", "fire", "foreign", "frequently", "failed", "founded", "financial", "flow", "frequency", "female", "face", "flash", NULL},
    {"get", "getter", "group", "group by", "global", "generic", "git", "good", "gpu", "garbage", "graph", "graphic", "giga", "gigabytes", "green", "gray", "grid", "gantt", "google", "goto", "government", "given", "game", "generally", "general", "great", "gave", "give", "ground", "go", "greater", "growth", "gas", "going", NULL},
    {"hidden", "hello", "how", "has", "help", "header", "have", "having", "home", "hour", "host", "high", "highlight", "html", "http", "hard", "hardware", "heap", "hook", "height", "history", "his", "he", "had", "him", "however", "held", "human", "himself", "higher", "hand", "half", "head", "house", "highly", "health", "highest", "heavy", "hold", "historical", "hit", "heat", "hex", "hexadecimal", "hi, how are you?", "hi, I'm fine, thanks.", "hi, I'm fine, thanks. And you?", "how are you?", "hello, World!", NULL},
    {"item", "interface", "implement", "int", "integer", "index", "indexes", "input", "instance", "instanceof", "import", "include", "inline", "implicit", "intern", "internal", "international", "internationalization", "inner", "init", "initial", "initialize", "initialization", "insert", "invert", "issue", "instruction", "image", "inherit", "inheritance", "install", "iter", "iterate", "iteration", "id", "i18n", "in", "is", "it", "into", "if", "including", "important", "information", "itself", "instead", "increased", "individual", "increase", "introduced", "influence", "industry", "interest", "involved", "idea", "island", "independent", "intended", "income", "increasing", "inside", "immediately", "increment", "integrate", "intelligence", "improve", "improvement", "icon", "in progress", "i'm fine, thanks.", "i'm fine, thanks. And you?", NULL},
    {"join", "json", "jump", "java", "javascript", "job", "jpql", "jpa", "just", "japan", NULL},
    {"key", "keyword", "kill", "killall", "kind", "keep", "keyboard", "kernel", "kanban", "known", "killed", "king", "knowledge", "know", "kebab", NULL},
    {"len", "length", "let", "list", "long", "lock", "locked", "lambda", "log", "login", "logout", "logger", "local", "location", "localization", "loop", "left", "line", "like", "layout", "liquid", "load", "loading", "loader", "low", "lower", "lowercase", "listen", "listener", "lib", "library", "libraries", "little", "level", "less", "link", "linking", "last", "light", "l10n", "linux", "later", "large", "life", "language", "led", "law", "late", "land", "largest", "least", "lost", "longer", "limited", "lead", "located", "leading", "living", "likely", "legal", "largely", "loss", "lack", "love", "letter", "leave", "learn", "learning", NULL},
    {"map", "main", "module", "mutable", "match", "matches", "method", "menu", "month", "master", "max", "maximize", "maximum", "min", "minimize", "minimum", "minus", "merge", "multi", "multiply", "mode", "model", "move", "memo", "memoize", "memory", "mean", "malloc", "medium", "minute", "milli", "millisecond", "micro", "microsecond", "mouse", "mask", "maintain", "maintenance", "manage", "management", "material", "more", "manifest", "mega", "megabytes", "modify", "make", "margin", "monitor", "matrix", "most", "may", "many", "made", "much", "must", "major", "music", "million", "members", "modern", "military", "men", "means", "making", "might", "man", "market", "moved", "movement", "my", "meaning", "money", "mostly", "mass", "majority", "me", "mother", "multiple", "matter", "married", "media", "machine", "marriage", "metal", "mainly", "microsoft", NULL},
    {"null", "name", "namespace", "next", "none", "node", "number", "numeric", "native", "nonlocal", "net", "nil", "npm", "not", "new", "nest", "nested", "night", "no", "never", "national", "natural", "need", "near", "network", "nature", "needed", "nearly", "north", "necessary", "numerous", "northern", "normal", "note", "noted", "notebook", "novel", "negative", "neural", "neuron", NULL},
    {"object", "override", "overridden", "output", "operator", "operation", "open", "order", "ordered", "old", "origin", "original", "optional", "org", "odd", "orange", "of", "on", "or", "other", "only", "over", "out", "often", "own", "once", "outside", "official", "our", "office", "originally", "occur", "oil", "older", "opened", "operating", "offered", NULL},
    {"public",  "print", "println", "private", "protected", "push",  "pop",     "python", "package", "pointer", "position", "previous", "permits", "person", "personal",  "provides",   "parent", "pass",     "property", "properties", "pseudo",     "param",   "parameter", "prefix", "post",     "pull",     "prod",        "production",   "produce",  "protocol", "password", "plus",      "percent", "percentage", "parse",     "play",      "player", "platform", "put",    "phone",   "project", "purchase", "program",  "programming", "problem", "progress", "progressive", "press",    "pressed", "publish", "published", "process",     "processor", "processing",           "procedure",       "precision",
     "picture", "pink",  "padding", "propose", "proposal",  "popup", "preview", "plural", "people",  "part",    "power",    "place",    "point",   "period", "political", "population", "per",    "possible", "popular",  "produced",   "particular", "provide", "present",   "played", "practice", "pressure", "performance", "particularly", "physical", "policy",   "primary",  "performed", "past",    "products",   "president", "potential", "plan",   "proposed", "passed", "parties", "prevent", "playing",  "probably", "paper",       "police",  "poor",     "primarily",   "positive", "pascal",  "pnpm",    "Phi-Long",  "Phi-Long Do", "philong",   "philong.do@gmail.com", "p.do@axelor.com", NULL},
    {"query", "queries", "queue", "quit", "quote", "quick", "quickly", "quality", "question", "qmk", NULL},
    {"return", "read", "raise", "ref", "reference", "require", "run", "record", "register", "receiver", "remote", "reduce", "red", "right", "range", "react", "remove", "removal", "restart", "reboot", "round", "random", "restrict", "restricted", "recipe", "retry", "retries", "reproduce", "request", "response", "responsive", "release", "role", "replay", "rule", "root", "room", "result", "resume", "resource", "repo", "repository", "report", "resolution", "regex", "row", "rgb", "reverse", "rather", "released", "required", "received", "rate", "research", "region", "returned", "religious", "referred", "remained", "real", "related", "recorded", "radio", "remains", "reported", "rest", "recent", "relationship", "relatively", "replaced", "reached", "reason", "reduced", "remain", "regular", "resulting", "remaining", "running", "removed", "reach", "refused", "reality", "reset", "regression", NULL},
    {"str",    "string",     "switch",   "super", "static", "stash",  "struct", "self", "system", "size",  "sizeof",  "sync",       "synchronized", "synchronous", "synchronously", "set",      "setting", "setter", "success", "successful", "successfully", "show",  "showcase", "short", "socket", "select",  "selector", "select * from ", "sealed",  "signed", "suffix", "suspend", "status", "shift", "sql",     "sort",        "sorted", "solid",     "state",   "statement", "sum",   "summary",  "start",   "startup", "stop",    "shut",  "shutdown", "store", "small", "similar", "simple",  "second", "standard", "stage", "staging", "smart", "smartphone", "script",    "split",  "space",   "search", "searches", "soft",     "software", "seems",   "separate", "separator", "sound",      "special", "specialize", "specialization", "service", "speed",     "slice", "splice", "scale", "slow",     "single", "should",
     "screen", "screenshot", "subtract", "swap",  "style",  "strong", "source", "src",  "square", "shell", "suggest", "suggestion", "subscribe",    "substitute",  "syntax",        "singular", "such",    "some",   "so",      "same",       "several",      "since", "she",      "still", "said",   "support", "see",      "sometimes",      "species", "side",   "social", "season",  "school", "six",   "surface", "significant", "study",  "structure", "started", "sent",      "story", "specific", "student", "smaller", "subject", "south", "saw",      "soon",  "sold",  "science", "society", "simply", "sense",    "site",  "served",  "seven", "sea",        "supported", "summer", "studies", "say",    "signal",   "southern", "section",  "stories", "ship",     "security",  "scientific", "serve",   "supply",     "soldier",        "spread",  "suggested", "sign",  "studio", "snake", "solution", "salut", "salut, tu vas bien ?",  NULL},
    {"this", "throw", "true",  "type", "typeof", "typescript", "temp",  "temporary", "transaction", "transactional", "transient", "transitive", "then",   "template", "try",    "table",      "tuple", "title",    "that",  "those",     "telephone",   "ticket",     "time",  "too",         "tool",      "transition", "transitioning", "tera",  "terabytes", "thread",     "threading", "translation", "task",  "trigger",  "total",  "track", "tracking",  "tracker", "text", "top",    "theme", "transform", "transformation", "transparent", "transport", "transfer",  "triangle", "tmp",     "todo",
     "the",  "to",    "their", "two",  "than",   "these",      "there", "through",   "three",       "took",          "take",      "term",       "though", "team",     "theory", "throughout", "thus",  "together", "third", "typically", "traditional", "themselves", "trade", "temperature", "therefore", "television", "town",          "today", "turn",      "technology", "towards",   "test",        "train", "training", "taking", "thing", "treatment", "turned",  "ten",  "troops", "told",  "tradition", "terminal",       "tree",        "thanks",    "thank you", "tweet",    "tweeter", NULL},
    {"undefined", "update", "use", "using", "union", "url", "username", "unsigned", "undef", "unless", "up", "upstream", "util", "undo", "uninstall", "upload", "uploaded", "uploading", "upper", "uppercase", "upsert", "unsubscribe", "unicode", "utf-8", "unix", "used", "under", "until", "usually", "united", "upon", "unit", "ubuntu", NULL},
    {"value", "valueOf", "void", "var", "variable", "variant", "varchar", "volatile", "vector", "virtual", "via", "view", "validate", "validator", "visible", "visibility", "video", "venv", "very", "various", "version", "variety", "visual", NULL},
    {"while", "where", "write", "with", "within", "warning", "week", "weekend", "wide", "web", "www", "wchar_t", "word", "world", "window", "work", "worker", "weak", "would", "will", "white", "width", "weight", "was", "were", "which", "who", "when", "well", "what", "without", "water", "way", "war", "we", "wrote", "written", "woman", "women", "went", "won", "whether", "working", "writing", "widely", "whole", "whose", "worked", "wife", "wanted", "west", "work in progress", NULL},
    {"xml", "xor", "xpath", "xxx", NULL},
    {"yield", "yarn", "year", "yellow", "yes", "you", "young", "yet", "yaml", NULL},
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

    char      start_letter = tolower(prefix_word[0]);
    const int index        = start_letter - 'a';

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
        if (start_letter == 'c' && (word_mods[0] & MOD_BIT(KC_RIGHT_ALT))) {
            static const char *PROGMEM words[]    = {"ca va", "ca va, et toi ?", NULL};
            static const size_t        words_size = sizeof(words) / sizeof(words[0]);
            found_index                           = autocomplete_search(words, words_size, start_index, prefix_word, prefix_word_len, result);
        } else {
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
            const bool shifted = (all_mods && MOD_MASK_SHIFT) || is_caps_word_on();
            char      *result;

            if (shifted) {
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
