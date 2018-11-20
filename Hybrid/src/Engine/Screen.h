#ifndef __JINX_SCREEN_H_
#define __JINX_SCREEN_H_

#include <string>
#include "GLFW/glfw3.h"
#include "Exceptions.h"

class Screen {
public:
	GLFWwindow* m_window;
	Screen(int width, int height, std::string title, GLFWmonitor* monitor);
	~Screen();

	GLFWwindow* getWindow() { return m_window; }
	static void windowResize(GLFWwindow* window, int width, int height);
};

#endif