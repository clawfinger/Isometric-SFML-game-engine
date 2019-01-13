#pragma once
#include <memory>
#include "SystemBase.h"
#include "../../Utils/Meta.h"
#include "../../Events/Observer.h"

class EntityContainer;
class EventDispatcher;
class DiContainer;
class AnimationSystem :	public SystemBase, public Observer
{
public:
	AnimationSystem(DiContainer* container);
	~AnimationSystem();
	void update(sf::Time deltaTime);
private:
	void handleEntitySpawnEvent(IEvent* event);
private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
};
REGISTER_TYPENAME(AnimationSystem)
