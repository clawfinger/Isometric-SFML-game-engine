#pragma once
#include <memory>
#include "SystemBase.h"
#include "../../Events/Observer.h"

class EntityContainer;
class EventDispatcher;
class DiContainer;
class Map;

class EntityMapPositionSystem : public SystemBase, public Observer
{
public:
	EntityMapPositionSystem(DiContainer* container);
	~EntityMapPositionSystem();
	void update(sf::Time deltaTime);
	void notify(IEvent* event);
    EntityId getEntityAtMapXY(int x, int y);

private:
	void handleEntitySpawnEvent(IEvent* event);

private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<Map> m_map;
};
REGISTER_TYPENAME(EntityMapPositionSystem)