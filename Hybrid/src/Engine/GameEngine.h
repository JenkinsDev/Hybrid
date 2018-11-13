#ifndef __JINX_GAMEENGINE_H_
#define __JINX_GAMEENGINE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <vector>
#include "Screen.h"
#include "Exceptions.h"

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	void changeActiveScreen(Screen* screen);
	bool isRunning();
private:
	bool m_isGLInitialized = false;
	Screen* m_screen;
	void initializeGlew();
};

#endif