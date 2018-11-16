// Copyright 2018 David Jenkins <djenkinsdev@gmail.com>
#include "Input.h"

int keyToKeyCode(Key key) {
	return (int)key;
}

bool isKeyToggled(Key key) {
	short state = GetKeyState(keyToKeyCode(key));
	return LOBYTE(state);
}

bool isKeyDown(Key key) {
	short state = GetKeyState(keyToKeyCode(key));
	return HIBYTE(state);
}

bool isKeyUp(Key key) {
	return !isKeyDown(key);
}
