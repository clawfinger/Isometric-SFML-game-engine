#pragma once
#include "Events\Observer.h"
#include "SFML\System\Time.hpp"
#include "ECS/Entity.h"
#include <memory>
#include <unordered_map>

class Window;
class SystemBase;
class EntityContainer;
class EventDispatcher;
class DiContainer;

class GameEngine :	public Observer
{
public:
	GameEngine(DiContainer* container);
	~GameEngine();
	void draw(std::shared_ptr<Window> window);
	void update(sf::Time deltaTime);
	void notify(IEvent* event);

private:
	void initSystems();

private:
	EntityId m_player;
	DiContainer* m_container;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::unordered_map<std::string, SystemBase*> m_systems;
};

