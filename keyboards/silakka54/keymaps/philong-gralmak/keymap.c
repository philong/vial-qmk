// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

// Silakka54-specific wrapper for the shared philong-gralmak keymap (users/philong-gralmak).
// The silakka54 has the full 4x12+6 layout, so LAYOUT_LR maps one to one.

#include QMK_KEYBOARD_H

#define LAYOUT_LR( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, \
                   t00, t01, t02, t03, t04, t05                 \
) LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B, \
                   t00, t01, t02, t03, t04, t05                 \
)

#include "philong-gralmak.c"
