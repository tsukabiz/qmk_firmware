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

// Custom
#define FUN_ESC LT(_FUNC, KC_ESC)
#define ALT_DEL ALT_T(KC_DEL)
#define CTL_SPC CTL_T(KC_SPC)
#define CTLSFTV LCTL(LSFT(KC_V))
#define CTLPGUP LCTL(KC_PGUP)
#define CTLPGDN LCTL(KC_PGDN)
#define CTLHOME LCTL(KC_HOME)
#define CTLEND  LCTL(KC_END)
#define CTLALTD LCTL(LALT(KC_DEL))
#define WINSFTS LGUI(LSFT(KC_S))

static bool another_key_pressed;

enum planck_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------. ,-----------------------------------------------.
 * |Fnc/Esc|  ' "  |  , <  |  . >  |   P   |   Y   | |   F   |   G   |   C   |   R   |   L   | Bspc  |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |  Tab  |   A   |   O   |   E   |   U   |   I   | |   D   |   H   |   T   |   N   |   S   | Enter |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * | Shift |  ; :  |   Q   |   J   |   K   |   X   | |   B   |   M   |   W   |   V   |   Z   | Shift |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------| 
 * |ScrShot|       | Left  | Right |Low/F13|Alt/Del| |Ctl/Spc|Rai/F14|   Up  |  Down |       |PastVlu|
 * `-----------------------------------------------' `-----------------------------------------------' 
 */
[_DVORAK] = KEYMAP( \
  FUN_ESC, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT,  \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
  WINSFTS, XXXXXXX, KC_LEFT, KC_RIGHT,LOWER,   ALT_DEL, CTL_SPC, RAISE,   KC_UP,   KC_DOWN, XXXXXXX, CTLSFTV  \
),

/* Lower
 * ,-----------------------------------------------. ,-----------------------------------------------.
 * |       |   ~   |   [   |   ]   |   %   |   $   | |  F12  |   F7  |   F8  |   F9  |       |       |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |       |   &   |   (   |   )   |   _   |   \   | |  F11  |   F4  |   F5  |   F6  |       |       |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |       |   !   |   {   |   }   |   ?   |   #   | |  F10  |   F1  |   F2  |   F3  |       |       |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |       |       | ^Home | ^End  | ***** |       | |       |       |  Home |  End  |       |       |
 * `-----------------------------------------------' `-----------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  XXXXXXX, KC_TILD, KC_LBRC, KC_RBRC, KC_PERC, KC_DLR,  KC_F12,  KC_F7,   KC_F8,   KC_F9,   XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_AMPR, KC_LPRN, KC_RPRN, KC_UNDS, KC_BSLS, KC_F11,  KC_F4,   KC_F5,   KC_F6,   XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_EXLM, KC_LCBR, KC_RCBR, KC_QUES, KC_HASH, KC_F10,  KC_F1,   KC_F2,   KC_F3,   XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, CTLHOME, CTLEND,  _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_END,  XXXXXXX, XXXXXXX  \
),

/* Raise
 * ,-----------------------------------------------. ,-----------------------------------------------.
 * |       |   `   |       |       |       |       | |   *   |   7   |   8   |   9   |   =   |  Del  |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |       |   @   |       |       |       |   |   | |   +   |   4   |   5   |   6   |   -   | Enter |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |   ^   | |   0   |   1   |   2   |   3   |   /   |       |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |       |       |  PgUp |  PgDn |       |       | |       | ***** | ^PgUp | ^PgDn |       |       |
 * `-----------------------------------------------' `-----------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  XXXXXXX, KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ASTR, KC_7,    KC_8,    KC_9,    KC_EQL,  KC_DEL,  \
  XXXXXXX, KC_AT,   XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS, _______, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CIRC, KC_0,    KC_1,    KC_2,    KC_3,    KC_SLSH, XXXXXXX, \
  XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, _______, CTLPGUP, CTLPGDN, XXXXXXX, XXXXXXX  \
),
    
/* Func
 * ,-----------------------------------------------. ,-----------------------------------------------.
 * | ***** |       |       |       |       |       | |       |       |       |       |       |CtAlDel|
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       | |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       | |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------| |-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       | |       |       |       |       |       | Reset |
 * `-----------------------------------------------' `-----------------------------------------------'
 */
[_FUNC] = KEYMAP( \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CTLALTD, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET    \
)

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
          register_code (KC_F14);   //Switch to English input mode
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
          register_code (KC_F13);   //Switch to Japanese input mode
          unregister_code (KC_F13);
        }
      }
      return false;
      break;

  }
  return true;
}