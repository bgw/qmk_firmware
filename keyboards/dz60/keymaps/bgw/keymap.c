#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
  _BA = 0,
  _FN,
  _PN,
  _FP,
  _CL,
};

enum custom_keycodes {
  CA_MPLY = SAFE_RANGE,
  CA_MPRV,
  CA_MNXT,
  // Super + Up/Down/Left/Right: window snapping
  SP_UP,
  SP_DOWN,
  SP_LEFT,
  SP_RGHT,
  // Ctrl+Alt + Up/Down/Left/Right: workspace switching
  CA_UP,
  CA_DOWN,
  CA_LEFT,
  CA_RGHT,
  // prints the version of the firmare
  VRSN,
  // This must come last
  DYNAMIC_MACRO_RANGE,
};

// Must come after custom_keycodes
#include "dynamic_macro.h"
#define DYN_REC DYN_REC_START1
#define DYN_STP DYN_REC_STOP
#define DYN_PLY DYN_MACRO_PLAY1

// SEND_MACRO is just SEND_STRING with a delay between each keypress
#define MACRO_TIMER 5
#define SEND_MACRO(str) send_string_with_delay_P(PSTR(str), MACRO_TIMER)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  if (!record->event.pressed) {
    return true;
  }
  switch (keycode) {
    case CA_MPLY:
      SEND_MACRO(SS_LCTRL(SS_LALT("p")));
      break;
    case CA_MPRV:
      SEND_MACRO(SS_LCTRL(SS_LALT("[")));
      break;
    case CA_MNXT:
      SEND_MACRO(SS_LCTRL(SS_LALT("]")));
      break;
    case SP_UP:
      SEND_MACRO(SS_LGUI(SS_TAP(X_UP)));
      break;
    case SP_DOWN:
      SEND_MACRO(SS_LGUI(SS_TAP(X_DOWN)));
      break;
    case SP_LEFT:
      SEND_MACRO(SS_LGUI(SS_TAP(X_LEFT)));
      break;
    case SP_RGHT:
      SEND_MACRO(SS_LGUI(SS_TAP(X_RIGHT)));
      break;
    case CA_UP:
      SEND_MACRO(SS_LCTRL(SS_LALT(SS_TAP(X_UP))));
      break;
    case CA_DOWN:
      SEND_MACRO(SS_LCTRL(SS_LALT(SS_TAP(X_DOWN))));
      break;
    case CA_LEFT:
      SEND_MACRO(SS_LCTRL(SS_LALT(SS_TAP(X_LEFT))));
      break;
    case CA_RGHT:
      SEND_MACRO(SS_LCTRL(SS_LALT(SS_TAP(X_RIGHT))));
      break;
    case VRSN:
      SEND_STRING(
        QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION
        ", Built on: " QMK_BUILDDATE
      );
      break;
    default:
      return true;
  }
  return false;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Base/default layer
	[_BA] = LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		MO(_CL),          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FN),          MO(_PN), KC_GRV),

  // Fn Layer: WASD, F1-F12, Backlight
	[_FN] = LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		XXXXXXX,          XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
		XXXXXXX,          KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_HOME, KC_PGUP, XXXXXXX,
		XXXXXXX,          XXXXXXX, XXXXXXX, BL_DEC,  BL_TOGG, BL_INC,  BL_BRTG, XXXXXXX, KC_DEL,  KC_END,  KC_PGDN,          XXXXXXX,
		XXXXXXX, XXXXXXX,          XXXXXXX,                   XXXXXXX,                            XXXXXXX, XXXXXXX,          MO(_FP), XXXXXXX),

  // Pn Layer: Media, RGB, Window snapping
	[_PN] = LAYOUT_60_ansi(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
		XXXXXXX,          XXXXXXX, SP_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CA_MPLY, CA_MPRV, CA_MNXT, XXXXXXX,
		XXXXXXX,          SP_LEFT, SP_DOWN, SP_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, XXXXXXX,
		XXXXXXX,          XXXXXXX, XXXXXXX, RGB_VAD, RGB_TOG, RGB_VAI, RGB_MOD, XXXXXXX, RGB_SPD, RGB_SPI, XXXXXXX,          XXXXXXX,
		XXXXXXX, XXXXXXX,          XXXXXXX,                   XXXXXXX,                            XXXXXXX, MO(_FP),          XXXXXXX, XXXXXXX),

  // Fn+Pn Layer: Workspace switching, macros
  [_FP] = LAYOUT_60_ansi(
		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
		XXXXXXX,          XXXXXXX, CA_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX,          CA_LEFT, CA_DOWN, CA_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
		XXXXXXX, XXXXXXX,          XXXXXXX,                   XXXXXXX,                            XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX),

  // Capslock Layer: Numpad, macros
	[_CL] = LAYOUT_60_ansi(
		VRSN,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAST, XXXXXXX, XXXXXXX, KC_PMNS, KC_PPLS,          XXXXXXX,
		XXXXXXX,          DYN_REC, DYN_STP, DYN_PLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_PSLS,
		XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_PENT,
		XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3,          XXXXXXX,
		XXXXXXX, XXXXXXX,          XXXXXXX,                   XXXXXXX,                            KC_KP_0, XXXXXXX,          XXXXXXX, KC_PDOT),
};
