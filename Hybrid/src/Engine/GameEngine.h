#ifndef __JINX_GAMEENGINE_H_
#define __JINX_GAMEENGINE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include "Screen.h"
#include "Exceptions.h"
#include "ECS/System.h"

typedef std::chrono::high_resolution_clock GameClock;
typedef std::chrono::seconds GameClockDuration;
typedef GameClock::time_point GameClockTimePoint;

class GameEngine {
	std::vector<std::shared_ptr<System>> m_systems;
	std::vector<std::unique_ptr<Entity>> m_entities;
public:
	GameEngine();
	~GameEngine();
	void changeActiveScreen(Screen* screen);
	bool isRunning();
	void addSystem(std::shared_ptr<System> system);
	void addEntity(std::unique_ptr<Entity> &&entity);
	void tick();
private:
	GameClockTimePoint m_prevClock = GameClock::now();
	GameClockTimePoint m_currClock = GameClock::now();
	bool m_isGLInitialized = false;
	Screen* m_screen;
	void initializeGlew();
};

#endif