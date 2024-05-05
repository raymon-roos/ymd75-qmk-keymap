/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2018 Wayne K Jones <github.com/WarmCatUK>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

// Layers
#define _MAIN 0  // Colemak_DH, with home row mods
#define _FN 1    // LED controls and bootmagic
#define _NAV 2   // Navigation/edit layer. Put arrow keys, backspace/delete, and modifiers right on the home row
#define _SYM 3   // Numbers and symbols
#define _QWER 4  // Layer with stock qwerty, for use with plover

enum custom_keycodes {
    P_MACRO = SAFE_RANGE
};

// Left-hand home row mods
#define NAV_W LT(_NAV,KC_W)
#define GUI_A LGUI_T(KC_A)
#define ALT_R LALT_T(KC_R)
#define SFT_S LSFT_T(KC_S)
#define CTRL_T LCTL_T(KC_T)

#define SYM_SPC LT(_SYM, KC_SPC)

// Right-hand home row mods
#define CTRL_N RCTL_T(KC_N)
#define SFT_E RSFT_T(KC_E)
#define ALT_I LALT_T(KC_I)
#define GUI_O RGUI_T(KC_O)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_S:
        case SFT_E:
            return TAPPING_TERM - 35;

        case NAV_W:
        case CTRL_T:
        case CTRL_N:
        case SYM_SPC:
            return TAPPING_TERM - 25;

        default:
            return TAPPING_TERM;
    }
}

// A short tap of a second key will still resolve as a modified key, as long as
// the mod-tap key is hold for at least as long as TAPPING_TERM. Whithout this,
// a mod-tap hold must be held for as long as TAPPING_TERM, and only after that
// do other keys resolve with a modifier. Enabled only for shift-taps, because
// those are the only modifiers playing a role in regular typing, so I want as
// immediate access to them as possible.
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_S):
            return true;
        case RSFT_T(KC_E):
            return true;
        default:
            return false;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 0: Main Layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │ ESC │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │ FN  │QWER │HOME │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
     * │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │ BACKSPACE │PGUP │
     * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
     * │  TAB   │  Q  │NAV(W)│  F │  P  │  B  │  J  │  L  │  U  │  Y  │  ;  │  [  │  ]  │   \    │PGDN │
     * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
     * │  LCTRL  │G(A) │A(R) │S(S) │C(T) │  G  │  M  │C(N) │S(E) │A(I) │G(O) │  '  │    RETURN   │ DEL │
     * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴─────────────┼─────┤
     * │   LSHIFT   │  X  │  C  │  D  │  V  │  Z  │  K  │  H  │  ,  │  .  │  /  │  RSHIFT        │ END │
     * ├──────┬─────┴┬────┴─┬───┴─────┴─────┴─────┴─────┴─────┴────┬┴─────┤─────┴┬────┬─────┬────┼─────┼
     * │LCTRL │L_GUI │L_ALT │              SYM(SPACE)              │R_ALT │R_CTRL│LEFT│DOWN │ UP │RIGHT│
     * └──────┴──────┴──────┴──────────────────────────────────────┴──────┴──────┴────┴─────┴────┘─────┘
     */
    [_MAIN] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   MO(_FN),   TO(_QWER),  KC_HOME,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,               KC_PGUP,
        KC_TAB,    KC_Q,   NAV_W,   KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_LBRC,  KC_RBRC,   KC_BSLS,             KC_PGDN,
        KC_LCTL,    GUI_A,  ALT_R,   SFT_S,   CTRL_T,  KC_G,    KC_M,    CTRL_N,  SFT_E,   ALT_I,   GUI_O,    KC_QUOT,  KC_ENT,                         KC_DEL,
        KC_LSFT,     KC_X,   KC_C,    KC_D,    KC_V,    KC_Z,    KC_K,    KC_H,    KC_COMM,  KC_DOT, KC_SLSH,    KC_RSFT,           KC_NO,              KC_END,
        KC_LCTL,  KC_LGUI,  KC_LALT,                    SYM_SPC,                        KC_RALT,  KC_RCTL,          KC_LEFT,   KC_DOWN,  KC_UP,         KC_RGHT
    ),

    /* 1: Function Layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │R_TOG│R_MOD│R_HUI│R_SAI│R_VAI│R_HUD│R_SAD│R_VAD│     │     │     │VOL- │VOL+ │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
     * │BLTOG│BLINC│BLDEC│     │     │     │     │     │     │     │     │     │     │           │     │
     * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
     * │        │TG(QWER)│  │     │     │     │     │     │     │     │     │     │     │        │     │
     * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
     * │         │     │     │     │     │     │     │     │     │     │     │     │             │     │
     * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴─────────────┼─────┤
     * │            │     │     │     │     │     │     │     │     │     │     │                │     │
     * ├────┬──────┬┴────┬┴─────┴─────┴─────┴─────┴─────┴─────┴─┬───┴─┬───┴─┬───┴┬────┬────┬─────┼─────┤
     * │BOOT│      │     │                                      │     │     │    │    │    │     │     │
     * └────┴──────┴─────┴──────────────────────────────────────┴─────┴─────┴────┴────┴────┴─────┴─────┘
     */
    [_FN] = LAYOUT(
        RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_HUD,  RGB_SAD,  RGB_VAD,  _______,  _______,  _______,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,
        BL_TOGG,  BL_UP,    BL_DOWN,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        BL_STEP, TG(_QWER), _______,  _______  ,_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
        QK_BOOTLOADER,  _______,  _______,                     _______,                                     _______,  _______,  _______,  _______,  _______,  _______
    ),

    /* 2: Nav/edit layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │           │     │
     * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
     * │        │     │L(NAV)│PGUP│PGDN │     │     │HOME │ ESC │ END │     │     │     │        │     │
     * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
     * │         │L_GUI│L_ALT│SHIFT│L_CTL│     │ ENT │LEFT │DOWN │ UP  │RIGHT│     │             │     │
     * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴─────────────┼─────┤
     * │            │     │     │     │     │     │     │BSPC │ DEL │     │     │                │     │
     * ├────┬──────┬┴────┬┴─────┴─────┴─────┴─────┴─────┴─────┴─┬───┴─┬───┴─┬───┴┬────┬────┬─────┼─────┤
     * │    │      │     │               RETURN                 │     │     │    │    │    │     │     │
     * └────┴──────┴─────┴──────────────────────────────────────┴─────┴─────┴────┴────┴────┴─────┴─────┘
     */
    [_NAV] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  NAV_W,    KC_PGUP,  KC_PGDN,  _______,  _______,  KC_HOME,  KC_ESC,   KC_END,   _______,  _______,  _______,  _______,            _______,
        _______,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_LCTL,  _______,  KC_ENT,   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,                      _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_BSPC,  KC_DEL,   _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  _______,                       KC_ENT,                                          _______,  _______,  _______,  _______,  _______,  _______
    ),

    /* 3: Numbers/symbols layer
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┤
     * │     │     │     │     │     │     │     │     │     │     │     │     │     │           │     │
     * ├─────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬────────┼─────┤
     * │        │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │     │     │        │     │
     * ├────────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴────────┼─────┤
     * │         │  =  │  [  │  {  │  (  │  |  │  *  │  )  │  }  │  ]  │  $  │     │             │     │
     * ├─────────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴─────────────┼─────┤
     * │            │  \  │  %  │  -  │  _  │     │  &  │  >  │  +  │     │     │                │     │
     * ├────┬──────┬┴────┬┴─────┴─────┴─────┴─────┴─────┴─────┴─┬───┴─┬───┴─┬───┴┬────┬────┬─────┼─────┤
     * │    │      │     │                                      │     │     │    │    │    │     │     │
     * └────┴──────┴─────┴──────────────────────────────────────┴─────┴─────┴────┴────┴────┴─────┴─────┘
     */
    [_SYM] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,  _______,  _______,            _______,
        _______,  KC_EQL,   KC_LBRC,  KC_LCBR,  KC_LPRN,  KC_PIPE,  KC_ASTR,  KC_RPRN,  KC_RCBR,  KC_RBRC,  KC_DLR,   _______,  _______,                      _______,
        _______,  KC_BSLS,  KC_PERC,  KC_MINS,  KC_UNDS,  _______,  KC_AMPR,  KC_GT,    KC_PLUS,  _______,  _______,  _______,  _______,                      _______,
        _______,  _______,  _______,                                SYM_SPC,                                _______,  _______,  _______,  _______,  _______,  _______
    ),

    /*
     * Qwerty layer, just for use with plover.
     */
    [_QWER] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,  MO(_FN),  TO(_MAIN), KC_HOME,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,      KC_BSPC,        KC_PGUP,
        KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,       KC_PGDN,
        KC_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN  ,KC_QUOT,        KC_ENT,              KC_DEL,
        KC_LSFT,       KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,      KC_NO,               KC_END,
        KC_LCTL,  KC_LGUI,  KC_LALT,                  KC_SPC,                                  KC_RALT,  KC_RCTL,          KC_LEFT,   KC_DOWN,  KC_UP,         KC_RGHT
    ),
};
