#pragma once
#include <memory>
#include <list>
#include "SystemBase.h"
#include "../../Events/Observer.h"

class EntityContainer;
class EventDispatcher;
class DiContainer;
class Map;

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
	std::vector<EntityId> checkEnemyInSight(EntityId character);
	bool isVisible(sf::Vector2f& from, sf::Vector2f& to, int lengthOfSight);

private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;

	std::list<EntityId> m_characters;
	std::list<EntityId> m_enemies;
	std::shared_ptr<Map> m_map;
};
REGISTER_TYPENAME(EntityVisionSystem)
