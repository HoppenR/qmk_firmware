/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

// TODO: make SHIFT+. be QK_REPEAT_KEY, also on . for vim layer(s)
//       REPEAT_KEY_ENABLE = yes

// clang-format off

#define LAYOUT_keymap(                                                          \
        k0A, k0B, k0C, k0D, k0E, k0F,             k4F, k4E, k4D, k4C, k4B, k4A, \
                                      k0G,   k4G,                               \
        k1A, k1B, k1C, k1D, k1E, k1F,             k5F, k5E, k5D, k5C, k5B, k5A, \
                                      k1G,   k5G,                               \
        k2A, k2B, k2C, k2D, k2E, k2F,             k6F, k6E, k6D, k6C, k6B, k6A, \
                            k3D, k3E, k3F,   k7F, k7E, k7D)                     \
    LAYOUT_split_3x6_3_ex2(                                                     \
        k0A, k0B, k0C, k0D, k0E, k0F, k0G,   k4G, k4F, k4E, k4D, k4C, k4B, k4A, \
        k1A, k1B, k1C, k1D, k1E, k1F, k1G,   k5G, k5F, k5E, k5D, k5C, k5B, k5A, \
        k2A, k2B, k2C, k2D, k2E, k2F,             k6F, k6E, k6D, k6C, k6B, k6A, \
                       k3D, k3E, k3F,             k7F, k7E, k7D)


#define SE_LDAQ ALGR(SE_Z)    // «
#define SE_RDAQ ALGR(SE_X)    // »

#define VIM_b LCTL(KC_LEFT)
#define VIM_d LCTL(SE_X)
#define VIM_e LCTL(KC_RGHT)
#define VIM_h KC_LEFT
#define VIM_j KC_DOWN
#define VIM_k KC_UP
#define VIM_l KC_RIGHT
#define VIM_p LCTL(SE_V)
#define VIM_r LCTL(LSFT(SE_Z))
#define VIM_u LCTL(SE_Z)
#define VIM_y LCTL(SE_C)

// clang-format on

const uint16_t PROGMEM arng_combo[] = {SE_P, SE_ADIA, COMBO_END};
const uint16_t PROGMEM scln_combo[] = {SE_COMM, SE_DOT, COMBO_END};
const uint16_t PROGMEM alt_combo[]  = {KC_LSFT, MO(2), COMBO_END};
const uint16_t PROGMEM gui_combo[]  = {MO(1), KC_LCTL, COMBO_END};

combo_t key_combos[] = {
    [0] = COMBO(arng_combo, SE_ARNG), // P + Ä = Å
    [1] = COMBO(scln_combo, SE_SCLN), // , + . = ;
    [2] = COMBO(alt_combo, KC_LALT),  // Shift + Layer 2 = Alt
    [3] = COMBO(gui_combo, KC_LGUI),  // Layer 2 + AltGr = SUPER
};
uint16_t COMBO_LEN = ARRAY_SIZE(key_combos);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case SE_GRV:
                SEND_STRING("`");
                return false;
            case SE_CIRC:
                SEND_STRING("^");
                return false;
            case SE_TILD:
                SEND_STRING("~");
                return false;
        }
    }
    return true;
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case SE_A ... SE_Z:
        case SE_ADIA:
        case SE_ARNG:
        case SE_MINS:
        case SE_ODIA:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        case KC_BACKSPACE:
        case KC_DELETE:
        case KC_UNDERSCORE:
        case KC_SPACE:
            return true;

        default:
            return false;
    }
}

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_keymap(                                  /*    Base layer    */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,     SE_Q,    SE_W,    SE_E,    SE_R,    SE_T,                         SE_Y,    SE_U,    SE_I,    SE_O,   SE_P,  SE_ADIA,
  /*|--------+--------+--------+--------+--------+-------*/ SE_PLUS,   SE_SLSH,/*-------+--------+--------+--------+--------+-------*/
      KC_ESC,     SE_A,    SE_S,    SE_D,    SE_F,    SE_G,                         SE_H,    SE_J,    SE_K,    SE_L, SE_ODIA, KC_BSPC,
  /*|--------+--------+--------+--------+--------+-------*/ SE_QUOT,   SE_COLN,/*-------+--------+--------+--------+--------+-------*/
      KC_PSCR,    SE_Z,    SE_X,    SE_C,    SE_V,    SE_B,                         SE_N,    SE_M, SE_COMM,  SE_DOT, SE_MINS, KC_ALGR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT,   MO(1),  KC_SPC,    KC_ENT,    MO(2), KC_LCTL
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_keymap(                                  /*  Numeric  layer  */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,   KC_0,  XXXXXXX,
  /*|--------+--------+--------+--------+--------+-------*/  KC_F11,    KC_F12,/*-------+--------+--------+--------+--------+-------*/
      KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_BSPC,
  /*|--------+--------+--------+--------+--------+-------*/ KC_HOME,    KC_END,/*-------+--------+--------+--------+--------+-------*/
      KC_PSCR, A(KC_1), A(KC_2), A(KC_3), A(KC_4), A(KC_5),                      A(KC_6), A(KC_7), A(KC_8), A(KC_9), A(KC_0), KC_ALGR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, _______,  KC_SPC,    KC_ENT,    MO(3), KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_keymap(                                  /*   Symbol layer   */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      SE_SECT, SE_EXLM, SE_DQUO, SE_HASH, SE_CURR, SE_PERC,                      SE_AMPR, SE_BSLS,  SE_EQL, SE_QUES, SE_ACUT,  KC_DEL,
  /*|--------+--------+--------+--------+--------+-------*/ KC_PGDN,   KC_PGUP,/*-------+--------+--------+--------+--------+-------*/
      KC_LCTL, SE_LDAQ, SE_LCBR, SE_LBRC, SE_LPRN, SE_LABK,                      SE_RABK, SE_RPRN, SE_RBRC, SE_RCBR, SE_RDAQ, KC_BSPC,
  /*|--------+--------+--------+--------+--------+-------*/ SE_CIRC,    SE_DLR,/*-------+--------+--------+--------+--------+-------*/
      KC_LSFT, SE_EURO,  SE_PND,   SE_AT, SE_HALF, XXXXXXX,                      SE_ASTR, SE_TILD, SE_PIPE,  SE_GRV, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT,   MO(3),  KC_SPC,    KC_ENT,  _______, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),


    [3] = LAYOUT_keymap(                                  /*    QMK  layer    */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      RM_TOGG, RM_PREV, RM_NEXT, KC_CAPS, KC_MUTE, KC_SLEP,                      MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX, QK_BOOT,
  /*|--------+--------+--------+--------+--------+-------*/ MS_BTN3,   MS_BTN4,/*-------+--------+--------+--------+--------+-------*/
      RM_SPDU, RM_HUEU, RM_SATU, RM_VALU, KC_VOLU, KC_BRIU,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,  QK_RBT,
  /*|--------+--------+--------+--------+--------+-------*/ MS_BTN1,   MS_BTN2,/*-------+--------+--------+--------+--------+-------*/
      RM_SPDD, RM_HUED, RM_SATD, RM_VALD, KC_VOLD, KC_BRID,                      MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, XXXXXXX,  EE_CLR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CW_TOGG, _______,  KC_SPC,    KC_ENT,  _______,   TG(4)
                                      //`--------------------------'  `--------------------------'
  ),

    [4] = LAYOUT_keymap(                                  /* Vim normal layer */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX,   VIM_e,   VIM_r, XXXXXXX,                        VIM_y,   VIM_u, XXXXXXX, XXXXXXX,   VIM_p, XXXXXXX,
  /*|--------+--------+--------+--------+--------+-------*/ XXXXXXX,   SE_SLSH,/*-------+--------+--------+--------+--------+-------*/
        TG(4), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        VIM_h,   VIM_j,   VIM_k,   VIM_l, SE_COLN, XXXXXXX,
  /*|--------+--------+--------+--------+--------+-------*/ KC_HOME,    KC_END,/*-------+--------+--------+--------+--------+-------*/
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TG(5),   VIM_b,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
    [5] = LAYOUT_keymap(                                  /* Vim visual layer */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX,S(VIM_e), XXXXXXX, XXXXXXX,                        VIM_y, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  /*|--------+--------+--------+--------+--------+-------*/ XXXXXXX,   XXXXXXX,/*-------+--------+--------+--------+--------+-------*/
        TG(5), XXXXXXX, XXXXXXX,   VIM_d, XXXXXXX, XXXXXXX,                     S(VIM_h),S(VIM_j),S(VIM_k),S(VIM_l), XXXXXXX, XXXXXXX,
  /*|--------+--------+--------+--------+--------+------*/S(KC_HOME), S(KC_END),/*------+--------+--------+--------+--------+-------*/
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TG(5),S(VIM_b),                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};

// clang-format on
