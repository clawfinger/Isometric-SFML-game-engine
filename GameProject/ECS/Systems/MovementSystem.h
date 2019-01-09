#pragma once
#include <memory>
#include "SystemBase.h"
#include "../../Events/Observer.h"
#include "../../Utils/Vector2D.h"

class PositionComponent;
class EntityContainer;
class EventDispatcher;
class DiContainer;
class Map;

class MovementSystem : public SystemBase, public Observer
{
public:
	MovementSystem(DiContainer* container);
	~MovementSystem();

	void update(sf::Time deltaTime);
	//void notify(IEvent* event);
private:
	void handleEntitySpawnEvent(IEvent* event);
	void handleSetDestinationEvent(IEvent* event);
	void updateOrientation(const Vector2f& movement, EntityId id);

private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<Map> m_map;

	sf::Time m_reachTilePauseTime;
};
REGISTER_TYPENAME(MovementSystem)
