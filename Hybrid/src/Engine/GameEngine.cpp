#include "GameEngine.h"

GameEngine::GameEngine() {
	glewExperimental = GL_TRUE;
	if (glfwInit() != GLFW_TRUE) {
		// Graphics engine initialization failed
		fprintf(stderr, "ERROR: could not initialize OpenGL with GLFW.");
		glfwTerminate();
		throw GameEngineInitializationException();
	}

	glfwWindowHint(GLFW_SAMPLES, 0); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GameEngine::~GameEngine() {
	glfwTerminate();
}

void GameEngine::initializeGlew() {
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error:\nCould not initialize glew.\n%s\n", glewGetErrorString(err));
		glfwTerminate();
		throw GameEngineInitializationException();
	}

	m_isGLInitialized = true;

	// Get OpenGL Version Info
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL Version Supported %s\n", version);
}

void GameEngine::changeActiveScreen(Screen* screen) {
	m_screen = screen;
	glfwMakeContextCurrent(screen->getWindow());

	if (!m_isGLInitialized) initializeGlew();
}
