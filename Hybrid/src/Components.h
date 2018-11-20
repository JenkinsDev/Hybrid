#ifndef __GAME_COMPONENTS_H_
#define __GAME_COMPONENTS_H_

#include "Engine/ECS/Component.h"

class RectangleDrawableComponent : public Component {
	float m_width = 0.2f;
	float m_height = 0.5f;
public:
	float getWidth() { return m_width; };
	float getHeight() { return m_height; };
};

class PlayerComponent : public Component {
public:
	PlayerComponent() {};
};

class PositionComponent : public Component {
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_z = 0.0f;
public:
	PositionComponent() {};
	PositionComponent(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {};

	void setPosition(float x, float y = 0.0f) {
		m_x = x;
		m_y = y;
	}

	void setPosition(float x, float y, float z) {
		m_x = x;
		m_y = y;
		m_z = z;
	}

	float getX() {
		return m_x;
	};

	float getY() {
		return m_y;
	}
};

class VelocityComponent : public Component {
	float m_xVelocity = 0.0f;
	float m_yVelocity = 0.0f;
public:
	VelocityComponent() {};

	float getXVelocity() { return m_xVelocity; };
	float getYVelocity() { return m_yVelocity; };

	void setXVelocity(float xVelocity) { m_xVelocity = xVelocity; }
	void setYVelocity(float yVelocity) { m_yVelocity = yVelocity; }
};

#endif