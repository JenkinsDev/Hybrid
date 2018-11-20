#include "Screen.h"

Screen::Screen(int width, int height, std::string title, GLFWmonitor* monitor) {
	if (monitor == nullptr) {
		//monitor = glfwGetPrimaryMonitor();
	}

	m_window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
	if (m_window == nullptr) {
		fprintf(stderr, "ERROR: could not open glfw window.");
		throw GLFWResourceFailedException();
	}

	glfwSetWindowSizeCallback(m_window, Screen::windowResize);
}

Screen::~Screen() {
	glfwDestroyWindow(m_window);
}

void Screen::windowResize(GLFWwindow* window, int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
}