#include "stdafx.h"
#include "GameEngine.h"
#include "Events/Events.h"
#include "Utils/Logger.h"

GameEngine::GameEngine(DiContainer* container): m_container(container)
{
	m_eventDispatcher = m_container->get<EventDispatcher>();
	m_entityManager = m_container->get<EntityManager>();
	subscribe();
}


GameEngine::~GameEngine()
{
}

void GameEngine::draw(std::shared_ptr<Window> window)
{
}

void GameEngine::update(sf::Time deltaTime)
{
}

void GameEngine::notify(IEvent * event)
{
	Logger::instance().log(event->name());
}

void GameEngine::subscribe()
{
	m_eventDispatcher->subscribe(typeName<FloorTileClickedEvent>(), this);
}
