/* Copyright © 2021-2023 Fern Zapata
 * This program is subject to the terms of the GNU GPL, either
 * version 3 of the License or (at your option) any later version.
 * You should have received a copy of the License along with
 * this program. If not, see <https://www.gnu.org/licenses/>. */

#include QMK_KEYBOARD_H
#include "joystick.h"
#if STENO_ENABLE
#include "keymap_steno.h"
#endif

enum xd75_layers {
	_DV,
	_QW,
#if JOYSTICK_ENABLE
	_HB,
#endif
#if STENO_ENABLE
	_PV,
#endif
	_L0,
	_R0,
	_F0,
	_CF,
};

enum xd75_keycodes {
	DVORAK = SAFE_RANGE,
	QWERTY,
#if JOYSTICK_ENABLE
	HB_MOD,
	HB_SWAP,
	HB_LEFT,
	HB_DOWN,
	HB_UP,
	HB_RGHT,
#endif
	MKC_P00,
};

#define LOWER   LT(_L0, KC_SPC)
#define RAISE   LT(_R0, KC_SPC)
#define FUNCT   MO(_F0)

#if JOYSTICK_ENABLE
#define HITBOX  TG(_HB)
#define HB_JHI  127
#define HB_BTA  JS_0
#define HB_BTB  JS_1
#define HB_BTX  JS_2
#define HB_BTY  JS_3
#define HB_BTL1 JS_4
#define HB_BTR1 JS_5
#define HB_BTL2 JS_6
#define HB_BTR2 JS_7
#define HB_BTL3 JS_8
#define HB_BTR3 JS_9
#define HB_BTSL JS_10
#define HB_BTHM JS_11
#define HB_BTST JS_12

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
	[0] = JOYSTICK_AXIS_VIRTUAL,
	[1] = JOYSTICK_AXIS_VIRTUAL,
	[2] = JOYSTICK_AXIS_VIRTUAL,
	[3] = JOYSTICK_AXIS_VIRTUAL,
	[4] = JOYSTICK_AXIS_VIRTUAL,
	[5] = JOYSTICK_AXIS_VIRTUAL,
};
#else
#define HITBOX  XXXXXXX
#endif // JOYSTICK_ENABLE

#if STENO_ENABLE
#define PLOVER  TG(_PV)
#else
#define PLOVER  XXXXXXX
#endif // STENO_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DV] = LAYOUT_ortho_5x15( // DVORAK
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_P7,   KC_P8,   KC_P9,
		KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL,  KC_P4,   KC_P5,   KC_P6,
		KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, KC_P1,   KC_P2,   KC_P3,
		KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT,  KC_P0,   MKC_P00, KC_PDOT,
		KC_LCTL, FUNCT,   KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
	),

	[_QW] = LAYOUT_ortho_5x15( // QWERTY
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, KC_P7,   KC_P8,   KC_P9,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  KC_P4,   KC_P5,   KC_P6,
		KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_P1,   KC_P2,   KC_P3,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  KC_P0,   MKC_P00, KC_PDOT,
		KC_LCTL, FUNCT,   KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
	),

#if JOYSTICK_ENABLE
	[_HB] = LAYOUT_ortho_5x15( // HITBOX
		HITBOX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HB_BTSL, HB_BTHM, HB_BTST,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HB_BTL1, HB_BTR1, HB_BTL2, HB_BTR2,
		HB_MOD,  HB_LEFT, HB_DOWN, HB_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HB_BTA,  HB_BTB,  HB_BTX,  HB_BTY,
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		HB_SWAP, XXXXXXX, XXXXXXX, HB_UP,   HB_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HB_BTA,  HB_BTA,  HB_BTB,  HB_BTL3, HB_BTR3
	),
#endif

#if STENO_ENABLE
	[_PV] = LAYOUT_ortho_5x15( // PLOVER
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC,  XXXXXXX, XXXXXXX, XXXXXXX,
		STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,  XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,  XXXXXXX, XXXXXXX, XXXXXXX,
		PLOVER,  XXXXXXX, XXXXXXX, STN_A,   STN_O,   XXXXXXX, XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2, XXXXXXX, XXXXXXX, XXXXXXX
	),
#endif

	[_L0] = LAYOUT_ortho_5x15( // LOWER
		KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, KC_PSLS, KC_PAST, KC_PMNS,
		_______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, KC_INS,  KC_NUM,  _______, KC_PPLS,
		KC_DEL,  _______, _______, KC_PLUS, KC_UNDS, _______, _______, KC_UNDS, KC_PLUS, _______, _______, KC_PIPE, _______, _______, KC_PENT,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
	),

	[_R0] = LAYOUT_ortho_5x15( // RAISE
		_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, KC_PSLS, KC_PAST, KC_PMNS,
		_______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______, KC_INS,  KC_NUM,  _______, KC_PPLS,
		KC_DEL,  _______, _______, KC_EQL,  KC_MINS, _______, _______, KC_MINS, KC_EQL,  _______, _______, KC_BSLS, _______, _______, KC_PENT,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
	),

	[_F0] = LAYOUT_ortho_5x15( // FUNCTION
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
		KC_PSCR, _______, KC_LPRN, KC_RPRN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT
	),

	[_CF] = LAYOUT_ortho_5x15( // CONFIGRURE
		_______, DVORAK,  QWERTY,  HITBOX,  PLOVER,  _______, _______, _______, _______, _______, _______, _______, DB_TOGG, EE_CLR,  QK_BOOT,
		_______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	),
};

#if STENO_ENABLE
void matrix_init_user() {
	steno_set_mode(STENO_MODE_GEMINI);
}
#endif // STENO_ENABLE

layer_state_t layer_state_set_user(layer_state_t state) {
	return update_tri_layer_state(state, _L0, _R0, _CF);
}

#if JOYSTICK_ENABLE
static struct {
	uint8_t swap;
	uint8_t mod;
	uint8_t left;
	uint8_t down;
	uint8_t up;
	uint8_t rght;
} axes = {0};

#define SIGN(x) ((x > 0) - (x < 0))
#endif // JOYSTICK_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case DVORAK:
			if (record->event.pressed)
				set_single_persistent_default_layer(_DV);
			return false;
		case QWERTY:
			if (record->event.pressed)
				set_single_persistent_default_layer(_QW);
			return false;
#if JOYSTICK_ENABLE
		case HB_MOD:
			axes.mod = record->event.pressed;
			int16_t ax = joystick_state.axes[0 + axes.swap];
			joystick_set_axis(0 + axes.swap, SIGN(ax) * HB_JHI >> axes.mod);
			ax = joystick_state.axes[1 + axes.swap];
			joystick_set_axis(1 + axes.swap, SIGN(ax) * HB_JHI >> axes.mod);
			return false;
		case HB_SWAP:
			if (record->event.pressed) {
				axes.swap = (axes.swap + 2) % JOYSTICK_AXIS_COUNT;
			}
			return false;
		case HB_LEFT:
			axes.left = record->event.pressed;
			joystick_set_axis(0 + axes.swap, (-axes.left ?: axes.rght) * HB_JHI >> axes.mod);
			return false;
		case HB_RGHT:
			axes.rght = record->event.pressed;
			joystick_set_axis(0 + axes.swap, (axes.rght ?: -axes.left) * HB_JHI >> axes.mod);
			return false;
		case HB_UP:
			axes.up = record->event.pressed;
			joystick_set_axis(1 + axes.swap, (-axes.up ?: axes.down) * HB_JHI >> axes.mod);
			return false;
		case HB_DOWN:
			axes.down = record->event.pressed;
			joystick_set_axis(1 + axes.swap, (axes.down ?: -axes.up) * HB_JHI >> axes.mod);
			return false;
#endif
		case MKC_P00:
			if (record->event.pressed) {
				SEND_STRING("00");
			}
			break;
	}
	return true;
}
