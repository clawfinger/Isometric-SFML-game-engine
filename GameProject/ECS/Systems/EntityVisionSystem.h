#pragma once
#include <memory>
#include <list>
#include "SystemBase.h"
#include "../../Events/Observer.h"

class EntityContainer;
class EventDispatcher;
class DiContainer;

class EntityVisionSystem : public SystemBase, public Observer
{
public:
	EntityVisionSystem(DiContainer* container);
	~EntityVisionSystem();
	void update(sf::Time deltaTime);
	void notify(IEvent* event);

private:
	void handleEntitySpawnEvent(IEvent* event);
	void handleEntityReachTileEvent(IEvent * event);

private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;

	std::list<EntityId> m_characters;
	std::list<EntityId> m_enemies;
};
REGISTER_TYPENAME(EntityVisionSystem)
