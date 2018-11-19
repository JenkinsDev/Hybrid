#ifndef __JINX_ENTITY_H_
#define __JINX_ENTITY_H_

#include <memory>
#include "Component.h"
#include "../Type.h"

class Entity
{
	typedef unsigned int ObjectID;
public:
	ObjectID getObjectId() { return m_id; };

	template <typename ComponentType>
	ComponentType* get() {
		auto found = m_components->find<ComponentType>();
		if (found != m_components->end()) {
			return static_cast<ComponentType*>(found->second.get());
		}

		return nullptr;
	}
protected:
	TypeMap<Component> m_components;
	ObjectID m_id;

	template <typename ComponentType>
	void registerComponent(std::unique_ptr<ComponentType> &&c) {
		m_components.registerType<ComponentType>(std::move(c));
	}
};

#endif