#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "quantum.h"
#include "./keymap_portuguese_mac_iso.h"
#include "gpio.h"

// clang-format off
enum layers {
	_COLEMAK_DH = 0,
	_NUMNAV,
  _SYM
};

enum {
	TD_LEFT_HOME,
	TD_RIGHT_END,
	TD_UP_PGUP,
	TD_DOWN_PGDN,
	TD_SPACE_1,
	TD_SPACE_2,
	TD_BSPACE_1,
	TD_BSPACE_2,
	CT_LBRK,
	CT_RBRK
};

int   current_wpm = 0;
led_t led_usb_state;
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

// Aliases for readability
#define ___ KC_NO

void left_brackets_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(PT_LCBR); //{
    } else if (state->count == 2) {
        register_code16(PT_LBRC); //[
    } else {
        register_code16(PT_LPRN); //(
    }
}

void left_brackets_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(PT_LCBR);
    } else if (state->count == 2) {
        unregister_code16(PT_LBRC);
    } else {
        unregister_code16(PT_LPRN);
    }
}

void right_brackets_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(PT_RCBR); //}
    } else if (state->count == 2) {
        register_code16(PT_RBRC); //]
    } else {
        register_code16(PT_RPRN); //)
    }
}

void right_brackets_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(PT_RCBR);
    } else if (state->count == 2) {
        unregister_code16(PT_RBRC);
    } else {
        unregister_code16(PT_RPRN);
    }
}
// clang-format off
tap_dance_action_t tap_dance_actions[] = {
	[TD_LEFT_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME), 
	[TD_RIGHT_END] = ACTION_TAP_DANCE_DOUBLE(KC_RGHT, KC_END), 
	[TD_UP_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP), 
	[TD_DOWN_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN), 
	
	[TD_SPACE_1] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_SPC, _NUMNAV), 
	[TD_SPACE_2] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_SPC, _SYM), 

	[CT_LBRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_brackets_finished, left_brackets_reset), 
	[CT_RBRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_brackets_finished, right_brackets_reset), 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
*BaseLayer:ColemakDH
*,------------------------.								.-----------------------.
*|ESC|	Q	|	W	|	F	|	P	|	B	|								|	J	|	L	|	U	|	Y	|	ºª|	´`|
*|---+----+---+---+---+---|								|---+---+---+---+---+---|
*|TAB|	A	|	R	|	S	|	T	|	G	|								|	M	|	N	|	E	|	I	|	O	| ^~|
*|---+----+---+---+---+---|         			|---+---+---+---+---+---|
*|SHF|	Z	|	X	|	C	|	D	|	V	|         			|	K	|	H	|,;	|.:	|	-_|HYP|
*'----------------+---+---+-----.	.-------+---+---+---------------'
*									|cmd|([{| SPC	|	|       |}])|ENT|
*									'-------------'	'---------------'
*/
	[_COLEMAK_DH]=LAYOUT_split_3x6_3(
	KC_ESC, KC_Q,KC_W,KC_F, KC_P,       KC_B,																								KC_J,				KC_L,	KC_U,		KC_Y,		TD(O_A),	PT_ACUT,	
	KC_TAB, KC_A,KC_R,KC_S, KC_T,       KC_G,																								KC_M,				KC_N,	KC_E,		KC_I,		KC_O,			PT_TILD,
	KC_LSFT,KC_Z,KC_X,KC_C, KC_D,       KC_V,																								KC_K,				KC_H,	PT_COMM,PT_DOT,	PT_MINS,  KC_HYPR,
											    KC_LEFT_GUI,TD(CT_LBRK),TD(TD_SPACE_2),        TD(TD_SPACE_1),	TD(CT_RBRK),KC_ENT
	),

/*
*NumNav:Numeration,navigation
*
*,------------------------.							,-----------------------.
*|		|	%	|	9	|	8	|	7	|	+	|							|		|		|	↑	|		|		|   |
*|----+---+---+---+---+---|							|---+---+---+---+---+---|
*|		|	=	|	6	|	5	|	4	|	-	|							|		|	←	|	↓	|	→	|		|		|
*|----+---+---+---+---+---|             |---+---+---+---+---+---|
*|		|		|	3	|	2	|	1	|	*	|             |		|		|		|		|		|		|
*'----------------+---+---+-----. .-----|---+---+---------------'
*									|	0	|	/	|_SYM	|	|_CK	|   |ENT|
*									'-------------'	'-------------'
*/
	[_NUMNAV]=LAYOUT_split_3x6_3(
	KC_NO,KC_PERC,KC_9,  KC_8,KC_7,  KC_PLUS,                            			KC_NO,  KC_NO,			    	TD(TD_UP_PGUP),		KC_NO,						KC_NO,KC_NO,
	KC_NO,KC_EQL,	KC_6,  KC_5,KC_4,  KC_MINS,                            			KC_NO,  TD(TD_LEFT_HOME),	TD(TD_DOWN_PGDN),	TD(TD_RIGHT_END),	KC_NO,KC_NO,
	KC_NO,KC_NO,  KC_3,  KC_2,KC_1,  KC_PAST,                            			KC_NO,  KC_NO,			    	KC_NO,            KC_NO,		        KC_NO,KC_NO,
														KC_0,  KC_PSLS,TD(TD_SPACE_2),  TO(_COLEMAK_DH),KC_NO,  KC_ENT
	),



// /*
// *SymLayer:Symbols
// *
// *,-----------------------.						,-----------------------.
// *|		|	!	|	"	|	#	|	$	|	@	|						|	&	|	\	|	|	|	'	|	?	|		|
// *|---+---+---+---+---+---|						|---+---+---+---+---+---|
// *|		|		|		|		|		|		|						|		|		|		|		|		|		|
// *|---+---+---+---+---+---|						|---+---+---+---+---+---|
// *|		|	<	|	>	|	ç	|		|		|						|		|		|		|		|		|		|
// *'---------------+---+---+----.	.---+---+---+---------------'
// *								|		|		|_FUN|	|_CK|		|		|
// *								'------------'	'-----------'
// */
 	[_SYM]=LAYOUT_split_3x6_3(
 	KC_NO,KC_EXLM,KC_DQUO,KC_HASH,  KC_DLR,	KC_AT,																		KC_AMPR,KC_BSLS,KC_PIPE,KC_QUOT,KC_QUES,KC_NO,
 	KC_NO,KC_NO,	KC_NO,	KC_NO,	  KC_NO,	KC_NO,																		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
 	KC_NO,KC_LT,	KC_GT,	PT_CCED,	KC_NO,	KC_NO,        														KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
 																  KC_NO,	KC_NO,TO(_COLEMAK_DH),		TO(_COLEMAK_DH),KC_NO,	KC_NO
 	),

/*
*FunctionLayer:Functionkeys
*
*,--------------------------------------.					,---------------------------------------.
*|	F9	|	F10	|	F11	|	F12	|		|					|		|		|		|		|		|
*|------+---+---+---+-------|					|---+---+---+---+-------|
*|	F5	|	F6	|	F7	|	F8	|		|					|		|Shift	|Ctrl	|Alt	|GUI	|
*|------+---+---+---+-------|                   |---+---+---+---+-------|
*|	F1	|	F2	|	F3	|	F4	|		|                   |		|		|		|		|		|
*'------------------+---+---+-------.	.---+---+---+-----------------------'
*						|		|		|		|	|		|_CK	|		|
*						'-----------------------'	'-----------------------'
*/
//	[_FUNCTION]=LAYOUT_split_3x6_3(
//	KC_F9,KC_F10,	KC_F11,	KC_F12,	KC_NO,					    KC_NO,              KC_NO,	    KC_NO,	KC_NO,	KC_NO,
//	KC_F5,KC_F6,	KC_F7,	KC_F8,	KC_NO,						KC_NO,              KC_RSFT,	KC_RCTL,KC_LALT,KC_RGUI,
//	KC_F1,KC_F2,	KC_F3,	KC_F4,	KC_NO,                      KC_NO,              KC_NO,	    KC_NO,	KC_NO,	KC_NO,
//							KC_NO,	KC_NO,	KC_NO,		KC_NO,  TO(_COLEMAK_DH),	KC_NO
//	),

///*
//	*Layertemplate
//	*
//	*
//	*,-------------------------.				,-----------------------.
//	*|		|		|		|		|		|		|					|		|		|		|		|		|		|
//	*|----+---+---+---+---+---|					|---+---+---+---+---+---|
//	*|		|		|		|		|		|		|					|		|		|		|		|		|		|
//	*|----+---+---+---+---+---|       	|---+---+---+---+---+---|
//	*|		|		|		|		|		|		|       	|		|		|		|		|		|		|
//	*'----------------+---+---+---.	.---+---+---+---------------'
//	*						      |		|		|		|	|		|		|		|
//	*				    		  '-----------'	'-----------'
//	*/
//	*/
//		[_LAYERINDEX]=LAYOUT(
//		_______,_______,_______,_______,_______,_______,										_______,_______,_______,_______,_______,_______,
//		_______,_______,_______,_______,_______,_______,										_______,_______,_______,_______,_______,_______,
//		_______,_______,_______,_______,_______,_______,                    _______,_______,_______,_______,_______,_______,
//																		_______,_______,_______,    _______,_______,_______
//		),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _COLEMAK_DH:
            rgb_matrix_sethsv(0, 255, 255);
            break;
        case _NUMNAV:
            rgb_matrix_sethsv(169, 255, 255);
            break;
        case _SYM:
            rgb_matrix_sethsv(180, 255, 255);
            break;
            // case _FUNCTION:
            //     rgb_matrix_sethsv(85, 255, 100);
            //     break;
    }
    return state;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    rgb_matrix_sethsv(0, 255, 255);
    return OLED_ROTATION_270;
}

static void render_logo(void) {
    static const char PROGMEM hexagram_logo[] = {0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x70, 0x18, 0x06, 0x06, 0x18, 0x70, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1f, 0x32, 0x66, 0xc4, 0x6c, 0x38, 0x1e, 0x37, 0x61, 0xc0, 0x80, 0x80, 0x80, 0x80, 0xc0, 0x61, 0x37, 0x1e, 0x38, 0x6c, 0xc4, 0x66, 0x32, 0x1f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0x4c, 0x66, 0x23, 0x36, 0x1c, 0x78, 0xec, 0x86, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x86, 0xec, 0x78, 0x1c, 0x36, 0x23, 0x66, 0x4c, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0e, 0x18, 0x60, 0x60, 0x18, 0x0e, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00};
    oled_write_raw_P(hexagram_logo, sizeof(hexagram_logo));
}

static void print_status_narrow(void) {
    /* Print current layer */
    oled_write("LAYER", false);

    oled_set_cursor(0, 6);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK_DH:
            oled_write("_COL", false);
            break;
        case _NUMNAV:
            oled_write("_NUM ", false);
            break;
        case _SYM:
            oled_write("_SYM", false);
            break;
    }
    // render_luna(0, 13);
}

static void print_logo_narrow(void) {
    render_logo();
    if (current_wpm > 0) {
        anim_sleep = timer_read32();
        /* wpm counter */
        oled_set_cursor(0, 14);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);
        oled_set_cursor(0, 15);
        oled_write(" wpm", false);
    } else if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
        /* clear */
        oled_set_cursor(0, 0);
        oled_write("                                                                                                                        ", false);
        oled_off();
    }
}

bool oled_task_user(void) {
    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
    return false;
}