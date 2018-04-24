#pragma once
#include "Events\Observer.h"
#include "SFML\System\Time.hpp"
#include "DiContainer\DiContainer.h"
#include "Events\EventDispatcher.h"
#include "ECS\EntityManager.h"
#include <memory>

class Window;

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
	std::shared_ptr<EntityManager> m_entityManager;
};

