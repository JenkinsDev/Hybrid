#include "Screen.h"

Screen::Screen(int width, int height, std::string title, GLFWmonitor* monitor) {
	if (monitor == nullptr) {
		//monitor = glfwGetPrimaryMonitor();
	}

	m_window = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);
	if (m_window == NULL) {
		fprintf(stderr, "ERROR: could not open glfw window.");
		throw GLFWResourceFailedException();
	}
}

Screen::~Screen() {
	glfwDestroyWindow(m_window);
}