VIA_ENABLE  = yes    # Enable VIA
VIAL_ENABLE = yes    # Enable VIAL
AUTO_SHIFT_ENABLE = yes
CAPS_WORD_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
NKRO_ENABLE = yes
MOUSEKEY_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no
LTO_ENABLE = yes
UNICODE_ENABLE = yes
SRC += features/achordion.c
SRC += features/layer_lock.c
SRC += features/select_word.c
SRC += features/sentence_case.c
SRC += features/repeat_key.c
SRC += features/autocorrection.c
SRC += features/mouse_turbo_click.c
SRC += andrewjrae-features/casemodes.c
SRC += autocomplete.c
