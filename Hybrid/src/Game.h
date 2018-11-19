#ifndef __GAME_H_
#define __GAME_H_

#include <memory>
#include <string>
#include "Engine/ECS/Entity.h"
#include "Engine/ECS/Component.h"
#include "Engine/ECS/System.h"

class PositionComponent : public Component {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
public:
	PositionComponent() {};
};

class VelocityComponent : public Component {
	float m_xVelocity = 0.0f;
	float m_yVelocity = 0.0f;
public:
	VelocityComponent() {};

	float getXVelocity() { return m_xVelocity; };
	float getYVelocity() { return m_yVelocity; };
};

class MoveSystem : public System {
	void tick(float dt, Entity* entity);
	std::string getTag() { return "MoveSystem"; };
};

class PlayerEntity : public Entity {
public:
	PlayerEntity();
};

#endif