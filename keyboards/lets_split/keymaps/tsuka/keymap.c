#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _DVORAK  0
#define _RAISE   1
#define _LOWER   2
#define _FUNC    3

enum planck_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
};

static bool another_key_pressed;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] = KEYMAP( \
  F(1),     KC_QUOT, KC_COMM, KC_DOT,   KC_P,  KC_Y,         KC_F,          KC_G,   KC_C,   KC_R,   KC_L,    KC_BSPC, \
  KC_TAB,   KC_A,    KC_O,    KC_E,     KC_U,  KC_I,         KC_D,          KC_H,   KC_T,   KC_N,   KC_S,    KC_ENT,  \
  KC_LSFT,  KC_SCLN, KC_Q,    KC_J,     KC_K,  KC_X,         KC_B,          KC_M,   KC_W,   KC_V,   KC_Z,    KC_RSFT, \
  KC_LGUI,  _______, KC_LEFT, KC_RIGHT, LOWER, ALT_T(KC_DEL),CTL_T(KC_SPC), RAISE,  KC_UP,  KC_DOWN,_______, LCTL(LSFT(KC_V)) \
),
 
[_RAISE] = KEYMAP( \
  _______, KC_GRV,  KC_LCBR, KC_RCBR, KC_PERC, KC_DLR,  KC_ASTR, KC_7,    KC_8,         KC_9,         KC_EQL,  KC_DEL,  \
  _______, KC_AT,   KC_LPRN, KC_RPRN, KC_AMPR, KC_PIPE, KC_PLUS, KC_4,    KC_5,         KC_6,         KC_MINS, _______, \
  _______, KC_EXLM, KC_LBRC, KC_RBRC, KC_HASH, KC_CIRC, KC_0,    KC_1,    KC_2,         KC_3,         KC_SLSH, _______, \
  _______, _______, KC_HOME, KC_END,  _______, _______, _______,  _______,LCTL(KC_PGUP),LCTL(KC_PGDN),_______, _______  \
),

[_LOWER] = KEYMAP( \
  _______, KC_GRV,  KC_LCBR,      KC_RCBR,     KC_PERC, KC_DLR,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_TILD, KC_DEL,  \
  _______, KC_AT,   KC_LPRN,      KC_RPRN,     KC_AMPR, KC_BSLS,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, _______, \
  _______, KC_EXLM, KC_LBRC,      KC_RBRC,     KC_HASH, KC_CIRC,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_QUES, _______, \
  _______, _______, LCTL(KC_HOME),LCTL(KC_END),_______, _______ , _______,  _______, KC_PGUP, KC_PGDN, _______, _______  \
),
 
[_FUNC] = KEYMAP( \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX,  KC_F12,  KC_F7,   KC_F8,   KC_F9,   XXXXXXX, LCTL(LALT(KC_DEL)) , \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F11,  KC_F4,   KC_F5,   KC_F6,   XXXXXXX, XXXXXXX            , \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   XXXXXXX, XXXXXXX            , \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______,  _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, RESET                \
)

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_KEY(_FUNC, KC_ESC),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) { another_key_pressed = true; }

  switch (keycode) {

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        another_key_pressed = false;
      } else {
        layer_off(_RAISE);
        if (another_key_pressed == false) {
          register_code (KC_F14);
          unregister_code (KC_F14);
        }
      }
      return false;
      break;

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        another_key_pressed = false;
      } else {
        layer_off(_LOWER);
        if (another_key_pressed == false) {
          register_code (KC_F13);
          unregister_code (KC_F13);
        }
      }
      return false;
      break;

  }
  return true;
}