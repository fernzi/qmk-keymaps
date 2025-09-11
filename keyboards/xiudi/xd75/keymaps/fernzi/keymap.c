/* Copyright © 2021-2025 Fern Zapata
 * This file is under the terms of the GNU GPL version 3, or (at your
 * option) any later version. If you didn't receive a copy of the GPL
 * along with this file, see <https://www.gnu.org/licenses/>. */

#include QMK_KEYBOARD_H
#include "joystick.h"

enum my_layer
{
  LAYER_DVORAK,
  LAYER_QWERTY,
#if JOYSTICK_ENABLE
  LAYER_HITBOX,
#endif
  LAYER_LOWER,
  LAYER_UPPER,
  LAYER_FUNCT,
  LAYER_ADJUST,
};

enum my_keycode
{
  MKC_P00 = SAFE_RANGE,
#if JOYSTICK_ENABLE
  HB_MOD,
  HB_SWAP,
  HB_LEFT,
  HB_DOWN,
  HB_UP,
  HB_RGHT,
#endif
};

enum my_layer_keycode
{
  MY_DVRK = PDF(LAYER_DVORAK),
  MY_QRTY = PDF(LAYER_QWERTY),
#if JOYSTICK_ENABLE
  MY_HBOX = TG(LAYER_HITBOX),
#else
  MY_HBOX = _______,
#endif

  MY_LOWR = LT(LAYER_LOWER, KC_SPC),
  MY_UPPR = LT(LAYER_UPPER, KC_SPC),
  MY_FUNC = MO(LAYER_FUNCT),
};

#if JOYSTICK_ENABLE
enum my_hitbox_keycode
{
  HB_BTA = JS_0,
  HB_BTB,
  HB_BTX,
  HB_BTY,
  HB_BTL1,
  HB_BTR1,
  HB_BTL2,
  HB_BTR2,
  HB_BTL3,
  HB_BTR3,
  HB_BTSL,
  HB_BTHM,
  HB_BTST,
};

int8_t const HB_JHI = 127;

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
  [0] = JOYSTICK_AXIS_VIRTUAL,
  [1] = JOYSTICK_AXIS_VIRTUAL,
  [2] = JOYSTICK_AXIS_VIRTUAL,
  [3] = JOYSTICK_AXIS_VIRTUAL,
  [4] = JOYSTICK_AXIS_VIRTUAL,
  [5] = JOYSTICK_AXIS_VIRTUAL,
};
#endif // JOYSTICK_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_DVORAK] = LAYOUT_ortho_5x15(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_P7,   KC_P8,   KC_P9,
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL,  KC_P4,   KC_P5,   KC_P6,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, KC_P1,   KC_P2,   KC_P3,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT,  KC_P0,   MKC_P00, KC_PDOT,
    KC_LCTL, MY_FUNC, KC_LGUI, KC_LALT, MY_LOWR, KC_SPC,  KC_SPC,  MY_UPPR, KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  [LAYER_QWERTY] = LAYOUT_ortho_5x15(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_P7,   KC_P8,   KC_P9,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  KC_P4,   KC_P5,   KC_P6,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_P1,   KC_P2,   KC_P3,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  KC_P0,   MKC_P00, KC_PDOT,
    KC_LCTL, MY_FUNC, KC_LGUI, KC_LALT, MY_LOWR, KC_SPC,  KC_SPC,  MY_UPPR, KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

#if JOYSTICK_ENABLE
  [LAYER_HITBOX] = LAYOUT_ortho_5x15(
    MY_HBOX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HB_BTSL, HB_BTHM, HB_BTST,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HB_BTL1, HB_BTR1, HB_BTL2, HB_BTR2,
    HB_MOD,  HB_LEFT, HB_DOWN, HB_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HB_BTA,  HB_BTB,  HB_BTX,  HB_BTY,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    HB_SWAP, XXXXXXX, XXXXXXX, HB_UP,   HB_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HB_BTA,  HB_BTA,  HB_BTB,  HB_BTL3, HB_BTR3
  ),
#endif

  [LAYER_LOWER] = LAYOUT_ortho_5x15(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, KC_PSLS, KC_PAST, KC_PMNS,
    _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, KC_INS,  KC_NUM,  _______, KC_PPLS,
    KC_DEL,  _______, _______, KC_PLUS, KC_UNDS, _______, _______, KC_UNDS, KC_PLUS, _______, _______, KC_PIPE, _______, _______, KC_PENT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  [LAYER_UPPER] = LAYOUT_ortho_5x15(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, KC_PSLS, KC_PAST, KC_PMNS,
    _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______, KC_INS,  KC_NUM,  _______, KC_PPLS,
    KC_DEL,  _______, _______, KC_EQL,  KC_MINS, _______, _______, KC_MINS, KC_EQL,  _______, _______, KC_BSLS, _______, _______, KC_PENT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  [LAYER_FUNCT] = LAYOUT_ortho_5x15(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
    KC_PSCR, _______, KC_LPRN, KC_RPRN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT
  ),

  [LAYER_ADJUST] = LAYOUT_ortho_5x15(
    _______, MY_DVRK, MY_QRTY, MY_HBOX, _______, _______, _______, _______, _______, _______, _______, _______, DB_TOGG, EE_CLR,  QK_BOOT,
    _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state)
{
  return update_tri_layer_state(
    state, LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
}

#if JOYSTICK_ENABLE
static struct
{
  uint8_t swap;
  bool mod;
  bool l, r, u, d;
} axes = {0};

#define MY_CMP(x, y) ((x > y) - (x < y))

static int8_t to_axis(int8_t x)
{
  return MY_CMP(x, 0) * HB_JHI >> axes.mod;
}
#endif // JOYSTICK_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
  switch (keycode) {
#if JOYSTICK_ENABLE
    case HB_MOD:
      axes.mod = record->event.pressed;
      for (uint8_t i = 0; i < 2; ++i) {
        uint8_t ai = i + axes.swap;
        int8_t av = joystick_state.axes[ai];
        joystick_set_axis(ai, to_axis(av));
      }
      return false;
    case HB_SWAP:
      axes.swap += 2 * record->event.pressed;
      axes.swap %= JOYSTICK_AXIS_COUNT;
      return false;
    case HB_LEFT:
      axes.l = record->event.pressed;
      joystick_set_axis(0 + axes.swap, to_axis(-axes.l ?: +axes.r));
      return false;
    case HB_RGHT:
      axes.r = record->event.pressed;
      joystick_set_axis(0 + axes.swap, to_axis(+axes.r ?: -axes.l));
      return false;
    case HB_UP:
      axes.u = record->event.pressed;
      joystick_set_axis(1 + axes.swap, to_axis(-axes.u ?: +axes.d));
      return false;
    case HB_DOWN:
      axes.d = record->event.pressed;
      joystick_set_axis(1 + axes.swap, to_axis(+axes.d ?: -axes.u));
      return false;
#endif // JOYSTICK_ENABLE
    case MKC_P00:
      if (record->event.pressed) {
        SEND_STRING("00");
      }
      break;
  }
  return true;
}
