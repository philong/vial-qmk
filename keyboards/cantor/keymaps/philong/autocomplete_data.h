#define ALPHABET_SIZE 26
#define MAX_AUTOCOMPLETE 168

static const char *autocomplete_data[ALPHABET_SIZE][MAX_AUTOCOMPLETE] PROGMEM = {
    {"async", "asynchronous", "asynchronously", "await", "add", "addition", "array",  "abstract", "and",  "args",  "arguments", "assert", "auto", "annotation", "action", "actual", "alias",   "abbr",       "arrow",  "alter",      "average", "atom",     "atomic",  "abs",      "absolute", "all", "allow",  "allowed",  "author",        "authorize", "archive",  "affect",  "affected",  "app",     "apply",    "application", "api",   "also",     "alternate", "alternative", "advanced",   "adapt",     "adapter",  "address", "addresses", "avatar",    "animate",    "animation", "align",      "accent",    "after",   "area",       "anomaly", "abort",  "are",   "about",   "around",   "against", "another", "among",    "along", "although", "above", "available",
     "again", "age",          "almost",         "able",  "air", "always",   "across", "aircraft", "away", "added", "army",      "attack", "art",  "according",  "amount", "album",  "already", "associated", "access", "additional", "appear",  "appeared", "attempt", "approach", "ability",  "act", "active", "activate", "approximately", "adopted",   "actually", "account", "announced", "applied", "accepted", "animal",      "asked", "activity", "analyze",   "analysis",    "activities", "appointed", "allowing", "ancient", "agreed",    "algorithm", "arithmetic", "assign",    "assignment", "aggregate", "augment", "autonomous", "android", "amazon", "apple", "america", "american", "azure",   "axelor",  "and you?", NULL},
    {"break", "bool", "boolean", "byte", "begin", "base", "basic", "become", "blank", "bad", "bisect", "branch", "branches", "back", "background", "backup", "backend", "bass", "between", "boot", "because", "bug", "bugfix", "block", "blocked", "box", "build", "builder", "black", "blue", "border", "bottom", "before", "bin", "binary", "by", "be", "but", "been", "both", "being", "became", "began", "based", "body", "book", "built", "best", "building", "below", "bar", "band", "brought", "believed", "business", "better", "beginning", "battle", "behind", "basis", "born", "blood", "billion", "ball", "believe", "buffer", "bit", "board", "bash", "bounce", "button", "bold", "bonjour", NULL},
    {"class", "classes",  "const",  "catch",    "case", "child",   "children",  "char",   "character", "cache",     "close",  "current", "col",      "collect", "collection", "collector", "column",  "continue",   "content", "context", "contains",  "constructor", "comment", "compute", "console", "config", "configuration", "configurator", "cpu",      "companion", "copy",    "copyright", "copyleft", "commit",  "command",      "create", "count",  "clone",   "check",  "call",      "callback",   "control",   "controller", "cancel", "cursor",  "code",    "custom",   "condition", "conditional", "clear", "clean",      "change",   "changelog", "calculate", "calculator", "channel",    "cast",  "connect", "connection", "convert",   "conversion", "compile", "compiler", "compatible", "compatibility", "chat", "chatbot",
     "color", "collapse", "circle", "calendar", "card", "country", "countries", "common", "complete",  "component", "chrome", "can",     "citation", "could",   "called",     "city",      "century", "considered", "came",    "created", "continued", "certain",     "company", "cause",   "cannot",  "come",   "culture",       "cities",       "computer", "community", "complex", "commonly",  "court",    "central", "construction", "cost",   "church", "capital", "career", "companies", "commercial", "christian", "course",     "center", "concept", "carried", "compared", "contain",   "cell",        "cut",   "completely", "campaign", "claimed",   "charge",    "cultural",   "constraint", "camel", "circuit", "clip",       "clipboard", "cable",      "chain",   "constant", "category",   "c++",           NULL},
    {"data",      "def",         "define", "definition", "del",   "delete", "deletion",   "default", "delay",       "dict",       "double",       "dummy",     "decimal",    "debug",  "debugger", "dynamic", "delegate", "duplicate", "domain", "done", "down", "download", "downloaded", "downloading", "debounce", "divide", "divider",     "diagonal",   "diff",     "difference", "drop",     "distinct",  "discard",  "disable", "draft",   "dev",    "develop",  "development", "developer", "design", "designer",   "doc",       "documentation", "decode",  "day",  "dir",           "direction",
     "directory", "directories", "device", "display",    "dirty", "digit",  "decoration", "dest",    "destination", "dependency", "dependencies", "deprecate", "deprecated", "deploy", "dry",      "dark",    "during",   "different", "did",    "do",   "due",  "death",    "does",       "developed",   "died",     "detail", "description", "descriptor", "describe", "described",  "designed", "difficult", "directly", "decided", "defined", "direct", "distance", "divided",     "date",      "degree", "discovered", "decrement", "dashboard",     "dialect", "demo", "demonstration", NULL},
    {"elem", "element", "else", "else if", "except", "exception", "expr", "expression", "enum", "end", "env", "environment", "echo", "enable", "even", "export", "error", "extends", "elif", "explicit", "extern", "external", "expect", "expected", "empty", "enter", "entry", "entries", "escape", "effect", "each", "extra", "extract", "extension", "example", "etc.", "engine", "engineer", "engineering", "encoding", "encode", "encrypt", "encryption", "edit", "editor", "erase", "exec", "execute", "executor", "exclude", "early", "eager", "eval", "evaluate", "either", "every", "energy", "especially", "established", "economic", "event", "eventually", "evidence", "enough", "education", "entire", "earlier", "ever", "experience", "economy", "exist", "elected", "electric", "ended", "eight", "estimated", "equipment", "edition", "easily", "extended", "equal", "effective", "elapsed", "easy", "easily", "emoji", "ethernet", "english", "et toi ?", NULL},
    {"final", "false", "for", "forEach", "function", "float", "from", "fix", "fixme", "front", "frontend", "friend", "field", "file", "filename", "filter", "full", "fetch", "forbid", "forbidden", "forward", "foreground", "free", "fail", "failure", "find", "found", "first", "feature", "frame", "framework", "few", "fewer", "folder", "fast", "firmware", "focus", "fall", "fallback", "family", "future", "firefox", "four", "film", "following", "further", "five", "force", "followed", "fact", "far", "food", "former", "father", "formed", "fire", "foreign", "frequently", "failed", "founded", "financial", "flow", "frequency", "female", "face", "flash", "fish", "factor", "font", "france", "french", NULL},
    {"get", "getter", "group", "group by", "global", "generic", "git", "good", "gpu", "garbage", "graph", "graphic", "giga", "gigabytes", "green", "gray", "grid", "gantt", "gradle", "google", "goto", "government", "given", "game", "generate", "generator", "generally", "general", "great", "gave", "give", "ground", "go", "greater", "growth", "gas", "going", NULL},
    {"hidden", "hide", "help", "hello", "has", "have", "having", "home", "hash", "header", "hour", "host", "high", "highlight", "html", "http", "https", "hard", "hardware", "heap", "hook", "height", "history", "his", "he", "hack", "hacker", "had", "him", "however", "held", "human", "himself", "higher", "hand", "half", "head", "house", "highly", "health", "highest", "heavy", "hold", "historical", "hit", "heat", "hex", "hexadecimal", "how", "hi, how are you?", "hi, I'm fine, thanks.", "hi, I'm fine, thanks. And you?", "how are you?", "hello, World!", NULL},
    {"item", "interface", "implement", "implementation", "int", "integer", "index", "indexes", "input", "instance", "instanceof", "import", "include", "inline", "implicit", "intern", "internal", "international", "internationalization", "inner", "init", "initial", "initialize", "initialization", "insert", "invert", "issue", "instruction", "image", "inherit", "inheritance", "install", "iter", "iterate", "iteration", "id", "i18n", "in", "is", "it", "into", "if", "including", "important", "information", "itself", "instead", "increased", "individual", "increase", "introduced", "influence", "industry", "interactive", "interest", "involved", "idea", "island", "independent", "intended", "income", "increasing", "inside", "immediately", "increment", "integrate", "intelligence", "improve", "improvement", "icon", "invisible", "italic", "in progress", "i'm fine, thanks.", "i'm fine, thanks. And you?", NULL},
    {"join", "json", "jump", "java", "javascript", "job", "jpql", "jpa", "just", "japan", NULL},
    {"key", "keyword", "kill", "killall", "kind", "keep", "keyboard", "kernel", "kanban", "known", "killed", "king", "knowledge", "know", "kebab", NULL},
    {"len", "length", "let", "list", "long", "lock", "locked", "lambda", "log", "login", "logout", "logger", "local", "locale", "location", "localization", "loop", "left", "line", "like", "label", "layout", "liquid", "load", "loading", "loader", "low", "lower", "lowercase", "listen", "listener", "lib", "library", "libraries", "little", "level", "less", "link", "linking", "last", "light", "l10n", "linux", "large", "lazy", "late", "latest", "later", "life", "lifecycle", "lightweight", "language", "led", "law", "land", "largest", "least", "lost", "longer", "limited", "lead", "located", "leading", "living", "likely", "legal", "largely", "loss", "lack", "love", "letter", "leave", "learn", "learning", "legacy", NULL},
    {"map", "main", "module", "mutable", "match", "matches", "method", "menu", "month", "master", "max", "maximize", "maximum", "min", "minimize", "minimum", "minus", "merge", "multi", "multiply", "mode", "model", "move", "memo", "memoize", "memory", "mean", "malloc", "medium", "minute", "milli", "millisecond", "micro", "microsecond", "mouse", "mask", "maintain", "maintenance", "manage", "management", "material", "more", "manifest", "mega", "megabytes", "modify", "make", "margin", "monitor", "matrix", "most", "may", "many", "made", "much", "must", "major", "music", "million", "member", "modern", "military", "men", "means", "making", "might", "man", "market", "moved", "movement", "my", "meaning", "money", "mostly", "mass", "majority", "me", "mother", "multiple", "matter", "married", "media", "machine", "marriage", "metal", "mainly", "microsoft", NULL},
    {"null", "name", "namespace", "next", "none", "node", "number", "numeric", "native", "nonlocal", "net", "nil", "npm", "not", "new", "nest", "nested", "night", "no", "never", "national", "natural", "need", "near", "network", "nature", "needed", "nearly", "north", "necessary", "numerous", "northern", "normal", "note", "noted", "notebook", "novel", "negative", "neural", "neuron", NULL},
    {"object", "output", "override", "overridden", "operator", "operation", "open", "order", "ordered", "old", "origin", "original", "option", "optional", "org", "odd", "orange", "of", "on", "or", "other", "only", "over", "out", "often", "own", "once", "outside", "official", "our", "office", "originally", "occur", "oil", "older", "opened", "operating", "offered", "online", "offline", "okay", NULL},
    {"public",  "print",    "println", "private", "protected", "push", "pop",    "python", "package", "pointer", "position", "previous", "permits", "person",    "personal",   "provides", "parent",   "pass",    "property", "properties", "pseudo",  "param",   "parameter", "prefix",   "post",     "pull",        "prod",         "production", "produce", "protocol", "password",  "plugin", "plus",     "percent",   "percentage", "parse", "play",     "player", "platform", "put",     "phone",   "project",  "purchase", "program", "programming", "problem",   "progress", "progressive", "press", "pressed", "publish", "published", "process",     "processor", "processing",           "procedure",       "precision", "picture", "pink", "padding",
     "propose", "proposal", "popup",   "preview", "panel",     "path", "plural", "people", "part",    "power",   "place",    "point",    "period",  "political", "population", "per",      "possible", "popular", "produced", "particular", "provide", "present", "played",    "practice", "pressure", "performance", "particularly", "physical",   "policy",  "primary",  "performed", "past",   "products", "president", "potential",  "plan",  "proposed", "passed", "parties",  "prevent", "playing", "probably", "paper",    "police",  "poor",        "primarily", "positive", "port",        "piece", "pascal",  "pnpm",    "Phi-Long",  "Phi-Long Do", "philong",   "philong.do@gmail.com", "p.do@axelor.com", NULL},
    {"query", "queries", "queue", "quit", "quote", "quick", "quickly", "quality", "question", "qmk", NULL},
    {"return", "read", "raise",   "ref",    "reference", "require",  "run",      "record", "register", "receiver", "remote",   "reduce", "red",     "right",    "range",    "react", "remove",   "removal", "restart", "reboot",   "round", "random", "restrict", "restricted",   "recipe",     "retry",   "retries",  "reproduce", "request", "response", "responsive", "release", "role",      "replay",    "rule",    "root",    "room",  "result",  "resume",  "resource", "repo",  "repository", "report", "rebase",   "resolution", "resolve",   "resolver", "regex",
     "row",    "rgb",  "reverse", "rather", "released",  "required", "received", "rate",   "research", "region",   "returned", "reload", "related", "referred", "remained", "real",  "recorded", "radio",   "remains", "reported", "rest",  "recent", "relation", "relationship", "relatively", "replace", "replaced", "reached",   "reason",  "reduced",  "remain",     "regular", "resulting", "remaining", "running", "removed", "reach", "refused", "reality", "refresh",  "reset", "regression", "rework", "refactor", "regarding",  "religious", NULL},
    {"str", "string", "self", "super", "state", "status", "switch", "static", "stash", "struct", "system", "size", "sizeof", "sync", "synchronized", "synchronous", "synchronously", "set", "setting", "setter", "setup", "success", "successful", "successfully", "show", "shown", "showcase", "short", "socket", "select", "selector", "select * from ", "sealed", "signed", "suffix", "suspend", "shift", "sql", "sort", "sorted", "solid", "statement", "sum", "summary", "start", "startup", "stop", "shut", "shutdown", "store", "small", "similar", "simple", "second", "standard", "stage", "staging", "smart", "smartphone", "script", "split", "space", "search", "searches", "soft", "software", "seems", "separate", "separator", "sound", "special", "specialize", "specialization", "service", "speed", "slice", "splice", "scale", "slow", "single", "should", "screen", "screenshot", "subtract", "swap", "style", "stream", "strong", "source", "src", "square", "shell", "suggest", "suggestion", "subscribe", "substitute", "syntax", "singular", "such", "some", "so", "save", "same", "several", "since", "she", "still", "said", "support", "see", "sometimes", "species", "side", "social", "season", "school", "six", "surface", "significant", "study", "structure", "started", "sent", "story", "storybook", "specific", "student", "smaller", "subject", "south", "saw", "soon", "sold", "science", "society", "simply", "sense", "site", "served", "seven", "sea", "supported", "summer", "studies", "say", "signal", "southern", "section", "stories", "ship", "security", "scientific", "serve", "supply", "soldier", "spread", "suggested", "sign", "studio", "step", "snake", "solution", "shop", "schedule", "span", "salut", "salut, tu vas bien ?", NULL},
    {"this", "throw", "true",  "type", "typeof", "typescript", "temp",  "temporary", "transaction", "transactional", "transient", "transitive", "then", "template", "try",  "table",  "tablet",     "tuple", "title",    "that",  "those",     "telephone",   "ticket",     "time",  "too",         "tool",      "toolbar",    "transition", "transitioning", "tera", "terabytes",  "thread",  "threading", "translate", "translation", "task",   "trigger", "total",     "track",  "tracking", "tracker", "text", "top",       "theme",    "transform", "transformation", "transparent", "transport", "transfer", "triangle", "tmp",     "todo",
     "the",  "to",    "their", "two",  "than",   "these",      "there", "throttle",  "through",     "three",         "took",      "take",       "term", "though",   "team", "theory", "throughout", "thus",  "together", "third", "typically", "traditional", "themselves", "trade", "temperature", "therefore", "television", "town",       "today",         "turn", "technology", "towards", "test",      "train",     "training",    "taking", "thing",   "treatment", "turned", "ten",      "troops",  "told", "tradition", "terminal", "tree",      "touch",          "thanks",      "thank you", "typo",     "tweet",    "tweeter", NULL},
    {"undefined", "update", "use", "using", "union", "url", "username", "unsigned", "undef", "unless", "up", "upstream", "util", "undo", "uninstall", "upload", "uploaded", "uploading", "upper", "uppercase", "upsert", "unsubscribe", "unicode", "unable", "utf-8", "unix", "used", "under", "until", "usually", "unit", "united", "upon", "unique", "ubuntu", "usa", NULL},
    {"value", "valueOf", "void", "var", "variable", "variant", "varchar", "volatile", "vector", "virtual", "via", "view", "viewer", "validate", "validator", "visible", "visibility", "video", "venv", "version", "very", "various", "variety", "visual", "vintage", "vacuum", NULL},
    {"while", "where", "with", "within", "write", "warning", "week", "weekend", "wide", "web", "www", "wchar_t", "word", "world", "window", "work", "worker", "wrap", "wrapper", "weak", "would", "will", "white", "width", "weight", "was", "were", "which", "who", "when", "well", "what", "without", "water", "way", "war", "we", "wrote", "written", "woman", "women", "went", "won", "whether", "working", "writing", "widely", "whole", "whose", "worked", "wife", "wanted", "west", "wire", "wireless", "Wi-Fi", "wifi", "wiki", "wikipedia", "work in progress", NULL},
    {"xml", "xor", "xpath", "xxx", NULL},
    {"yield", "year", "yellow", "yes", "you", "young", "yet", "yaml", "yarn", NULL},
    {"zip", "zero", "zone", "zoom", "zsh", NULL},
};
