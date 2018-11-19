#ifndef __JINX_SYSTEM_H_
#define __JINX_SYSTEM_H_

#include <string>
#include "Entity.h"

class System {
public:
	virtual void tick(float dt, Entity* entity) {};
	virtual std::string getTag() { return ""; };
};

#endif