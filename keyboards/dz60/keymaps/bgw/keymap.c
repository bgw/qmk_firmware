#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
  _BA = 0,
  _FN,
  _PN,
  _FP,
  _CL,
  _EM,
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
  // Multi-character emoji
  E_SHRUG,  // https://emojipedia.org/shrug/
  E_BMOJI,  // B button (meme)
  E_TFLIP,  // Table flip
  E_FFLIP,  // Facebook flip
  E_TDOWN,  // Setting table down
  // This must come last
  DYNAMIC_MACRO_RANGE,
};

enum unicode_names {
  ANGR,
  FIRE,
  THIK,
  CRY,
  UPDN,
  POOP,
  _100,
};

const uint32_t PROGMEM unicode_map[] = {
  [ANGR] = 0x1F620,  // https://emojipedia.org/angry-face/
  [FIRE] = 0x1F525,  // https://emojipedia.org/fire/
  [THIK] = 0x1F914,  // https://emojipedia.org/thinking-face/
  [CRY]  = 0x1F622,  // https://emojipedia.org/crying-face/
  [UPDN] = 0x1F643,  // https://emojipedia.org/upside-down-face/
  [POOP] = 0x1F4A9,  // https://emojipedia.org/pile-of-poo/
  [_100] = 0x1F4AF,  // https://emojipedia.org/hundred-points-symbol/
};

// Must come after custom_keycodes
#include "dynamic_macro.h"
#define DYN_REC DYN_REC_START1
#define DYN_STP DYN_REC_STOP
#define DYN_PLY DYN_MACRO_PLAY1

// SEND_MACRO is just SEND_STRING with a delay between each keypress
#define MACRO_TIMER 5
#define SEND_MACRO(str) send_string_with_delay_P(PSTR(str), MACRO_TIMER)

void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
}

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
    case E_SHRUG:
      send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
      break;
    case E_BMOJI:
      send_unicode_hex_string("1F171 FE0F");
      break;
    case E_TFLIP:
      send_unicode_hex_string(
        "0028 256F 00B0 25A1 00B0 FF09 256F FE35 0020 253B 2501 253B"
      );
      break;
    case E_FFLIP:
      send_unicode_hex_string(
        "0028 256F 00B0 25A1 00B0 0029 256F FE35 0020 029E 006F 006F 0071 01DD "
        "0254 0250 2132"
      );
      break;
    case E_TDOWN:
      send_unicode_hex_string(
        "252C 2500 252C 30CE 0028 0020 00BA 0020 005F 0020 00BA 30CE 0029"
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
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
    _______,          XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, RESET,
    XXXXXXX,          KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_HOME, KC_PGUP, _______,
    _______,          XXXXXXX, XXXXXXX, BL_DEC,  BL_TOGG, BL_INC,  XXXXXXX, XXXXXXX, KC_DEL,  KC_END,  KC_PGDN,          _______,
    _______, _______,          _______,                   _______,                            _______, XXXXXXX,          MO(_FP), XXXXXXX),

  // Pn Layer: Media, RGB, Window snapping
  [_PN] = LAYOUT_60_ansi(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
    _______,          XXXXXXX, SP_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CA_MPLY, CA_MPRV, CA_MNXT, XXXXXXX,
    XXXXXXX,          SP_LEFT, SP_DOWN, SP_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, _______,
    _______,          XXXXXXX, XXXXXXX, RGB_VAD, RGB_TOG, RGB_VAI, RGB_MOD, XXXXXXX, RGB_SPD, RGB_SPI, XXXXXXX,          _______,
    _______, _______,          _______,                   _______,                            _______, MO(_FP),          XXXXXXX, XXXXXXX),

  // Fn+Pn Layer: Workspace switching, macros
  [_FP] = LAYOUT_60_ansi(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
    _______,          XXXXXXX, CA_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,          CA_LEFT, CA_DOWN, CA_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,
    _______, _______,          _______,                   _______,                            MO(_EM), XXXXXXX,          XXXXXXX, XXXXXXX),

  // Capslock Layer: Numpad, macros
  [_CL] = LAYOUT_60_ansi(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
    _______,          DYN_REC, DYN_STP, DYN_PLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, _______,
    _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,
    _______, _______,          _______,                   _______,                            _______, XXXXXXX,          XXXXXXX, XXXXXXX),

  // emoji layer
  [_EM] = LAYOUT_60_ansi(
    VRSN,    X(_100), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, X(THIK), XXXXXXX, X(UPDN), XXXXXXX, E_FFLIP, X(POOP), XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,          X(ANGR), E_SHRUG, E_TDOWN, X(FIRE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, E_TFLIP, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,          XXXXXXX, XXXXXXX, X(CRY),  XXXXXXX, E_BMOJI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
    XXXXXXX, XXXXXXX,          XXXXXXX,                   XXXXXXX,                            XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX),
};
