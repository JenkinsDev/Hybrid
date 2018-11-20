#ifndef __GAME_H_
#define __GAME_H_

#include <memory>
#include <string>
#include "Engine/ECS/Entity.h"
#include "Engine/ECS/System.h"

class MoveSystem : public System {
	void tick(float dt, Entity* entity);
};

class InputSystem : public System {
	void tick(float dt, Entity* entity);
};

class PlayerEntity : public Entity {
public:
	PlayerEntity();
};

#endif