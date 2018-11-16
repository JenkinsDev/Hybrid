#ifndef __JINX_INPUT_H_
#define __JINX_INPUT_H_

#include <Windows.h>

enum class Key {
	// Mouse Keys
	LEFT_MOUSE_BUTTON = VK_LBUTTON,
	RIGHT_MOUSE_BUTTON = VK_RBUTTON,
	MIDDLE_MOUSE_BUTTON = VK_MBUTTON,

	// Modifiers
	SHIFT = VK_SHIFT,
	LEFT_SHIFT = VK_LSHIFT,
	RIGHT_SHIFT = VK_RSHIFT,

	CONTROL = VK_CONTROL,
	LEFT_CONTROL = VK_LCONTROL,
	RIGHT_CONTROL = VK_RCONTROL,

	ALT = VK_MENU,
	LEFT_ALT = VK_LMENU,
	RIGHT_ALT = VK_RMENU,

	LEFT_WINDOWS = VK_LWIN,
	RIGHT_WINDOWS = VK_RWIN,

	CAPS_LOCK = VK_CAPITAL,

	// Keyboard Keys
	ESCAPE = VK_ESCAPE,
	ENTER = VK_RETURN,
	SPACE = VK_SPACE,
	LEFT_ARROW = VK_LEFT,
	RIGHT_ARROW = VK_RIGHT,
	UP_ARROW = VK_UP,
	DOWN_ARROW = VK_DOWN,

	ZERO = 0x30,
	ONE = 0x31,
	TWO = 0x32,
	THREE = 0x33,
	FOUR = 0x34,
	FIVE = 0x35,
	SIX = 0x36,
	SEVEN = 0x37,
	EIGHT = 0x38,
	NINE = 0x39,

	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A
};

int keyToKeyCode(Key key);

bool isKeyToggled(Key key);
bool isKeyUp(Key key);
bool isKeyDown(Key key);

#endif