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

void GameEngine::changeActiveScreen(Screen* screen) {
	m_screen = screen;
	glfwMakeContextCurrent(screen->getWindow());

	if (!m_isGLInitialized) initializeGlew();
}

bool GameEngine::isRunning() {
	return !glfwWindowShouldClose(m_screen->getWindow());
}

void GameEngine::addSystem(std::shared_ptr<System> system) {
	m_systems.push_back(std::move(system));
}

void GameEngine::addEntity(std::unique_ptr<Entity> &&entity) {
	m_entities.push_back(std::move(entity));
}

void GameEngine::tick() {
	m_prevClock = m_currClock;
	m_currClock = clock();
	float dt = (m_currClock - m_prevClock) / (float)CLOCKS_PER_SEC;

	// Run all systems against all entities. We'll start with a
	// very naive systems approach.
	for (int i = 0; i < m_systems.size(); i++) {
		for (int j = 0; j < m_entities.size(); j++) {
			m_systems[i]->tick(dt, m_entities[j].get());
		}
	}
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