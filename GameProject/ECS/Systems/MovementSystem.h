#pragma once
#include <memory>
#include "SystemBase.h"
#include "../../Events/Observer.h"

class EntityManager;
class EventDispatcher;
class DiContainer;
class Map;

class MovementSystem : public SystemBase, public Observer
{
public:
	MovementSystem(DiContainer* container, std::string name);
	~MovementSystem();

	void update(sf::Time deltaTime);
	void notify(IEvent* event);
private:
	void handleEntitySpawnEvent(IEvent* event);
	void handleTileClickedEvent(IEvent* event);
	void handlePlayerChangedEvent(IEvent* event);

private:
	EntityId m_currentPlayer;
	std::shared_ptr<EntityManager> m_entityManager;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<Map> m_map;
};

