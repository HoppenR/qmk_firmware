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
#include "send_string.h"

// clang-format off

#define LAYOUT_visual( \
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

#define SE_LDAQ S(A(SE_V))    // «
#define SE_RDAQ S(A(SE_B))    // »

// TODO: COMBO SE_P    + SE_ADIA = SE_ARNG
// TODO: COMBO KC_LSFT + MO(2)   = KC_LALT
// TODO: COMBO MO(2)   + KC_ALGR = KC_GUI
// TODO: COMBO SE_COMM + SE_DOT  = SE_SCLN
// TODO: SENDSTRING("`") for non-dead `
// TODO: SENDSTRING("~") for non-dead ~
// TODO: custom mode: MO(3) -> KC_LCTL = MOVEMENT_MODE
// TODO: CW_TOGG: add whitelisted characters for swedish keys and more
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_visual(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,     SE_Q,    SE_W,    SE_E,    SE_R,    SE_T,                         SE_Y,    SE_U,    SE_I,    SE_O,   SE_P,  SE_ADIA,
  /*|--------+--------+--------+--------+--------+-------*/ SE_PLUS,   SE_SLSH,/*-------+--------+--------+--------+--------+-------*/
      KC_ESC,     SE_A,    SE_S,    SE_D,    SE_F,    SE_G,                         SE_H,    SE_J,    SE_K,    SE_L, SE_ODIA, KC_BSPC,
  /*|--------+--------+--------+--------+--------+-------*/ SE_QUOT,   SE_COLN,/*-------+--------+--------+--------+--------+-------*/
      KC_PSCR,    SE_Z,    SE_X,    SE_C,    SE_V,    SE_B,                         SE_N,    SE_M, SE_COMM,  SE_DOT, SE_MINS, KC_ALGR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_LCTL
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_visual(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,   KC_0,  XXXXXXX,
  /*|--------+--------+--------+--------+--------+-------*/  KC_F11,    KC_F12,/*-------+--------+--------+--------+--------+-------*/
      KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_BSPC,
  /*|--------+--------+--------+--------+--------+-------*/ KC_HOME,    KC_END,/*-------+--------+--------+--------+--------+-------*/
      KC_PSCR, A(KC_1), A(KC_2), A(KC_3), A(KC_4), A(KC_5),                      A(KC_6), A(KC_7), A(KC_8), A(KC_9), A(KC_0), KC_ALGR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, _______,  KC_SPC,     KC_ENT,   MO(3), KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_visual(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      SE_SECT, SE_EXLM, SE_DQUO, SE_HASH, SE_CURR, SE_PERC,                      SE_AMPR, SE_BSLS,  SE_EQL, SE_QUES, SE_ACUT,  KC_DEL,
  /*|--------+--------+--------+--------+--------+-------*/ KC_PGDN,   KC_PGUP,/*-------+--------+--------+--------+--------+-------*/
      KC_LCTL, SE_LDAQ, SE_LCBR, SE_LBRC, SE_LPRN, SE_LABK,                      SE_RABK, SE_RPRN, SE_RBRC, SE_RCBR, SE_RDAQ, KC_BSPC,
  /*|--------+--------+--------+--------+--------+-------*/ SE_CIRC,   SE_DLR, /*-------+--------+--------+--------+--------+-------*/
      KC_LSFT, SE_EURO,  SE_PND,   SE_AT, SE_HALF, XXXXXXX,                      SE_ASTR, SE_TILD, SE_PIPE, _______, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT,   MO(3),  KC_SPC,     KC_ENT, _______, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  ),


    [3] = LAYOUT_visual(

  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      RM_TOGG, RM_PREV, RM_NEXT, KC_CAPS, KC_MUTE, KC_SLEP,                      MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX, QK_BOOT,
  /*|--------+--------+--------+--------+--------+-------*/ MS_BTN3,   MS_BTN4,/*-------+--------+--------+--------+--------+-------*/
      RM_SPDU, RM_HUEU, RM_SATU, RM_VALU, KC_VOLU, KC_BRIU,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, QK_REBOOT,
  /*|--------+--------+--------+--------+--------+-------*/ MS_BTN1,   MS_BTN2, /*-------+--------+--------+--------+--------+-------*/
      RM_SPDD, RM_HUED, RM_SATD, RM_VALD, KC_VOLD, KC_BRID,                      MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CW_TOGG, _______,  KC_SPC,     KC_ENT, _______, KC_LCTL
                                      //`--------------------------'  `--------------------------'
  )
};

// clang-format on
