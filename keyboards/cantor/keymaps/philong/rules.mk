VIA_ENABLE  = yes    # Enable VIA
VIAL_ENABLE = yes    # Enable VIAL

# VIAL_INSECURE = yes
# CONSOLE_ENABLE = yes
# UNICODE_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
CAPS_WORD_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
LTO_ENABLE = yes
AUTOCORRECT_ENABLE = yes

ifeq ($(CONSOLE_ENABLE), yes)
	NKRO_ENABLE = no
	EXTRAKEY_ENABLE = no
	MOUSEKEY_ENABLE = no
else
	NKRO_ENABLE = yes
	EXTRAKEY_ENABLE = yes
	MOUSEKEY_ENABLE = yes
endif

SRC += features/achordion.c
SRC += features/layer_lock.c
SRC += features/select_word.c
SRC += features/sentence_case.c
SRC += features/repeat_key.c
SRC += features-andrewjrae/casemodes.c
SRC += features-treeman/layermodes.c
SRC += autocomplete.c

ifeq ($(MOUSEKEY_ENABLE), yes)
    SRC += features/mouse_turbo_click.c
endif

ifneq ($(AUTOCORRECT_ENABLE), yes)
	SRC += features/autocorrection.c
endif
