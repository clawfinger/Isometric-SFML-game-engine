#include "stdafx.h"
#include "GameEngine.h"
#include "Events/Events.h"
#include "Utils/Logger.h"
#include "EntityLoader.h"

GameEngine::GameEngine(DiContainer* container): m_container(container)
{
	m_eventDispatcher = m_container->get<EventDispatcher>();
	m_entityManager = m_container->get<EntityManager>();
	std::shared_ptr<EntityLoader> loader = m_container->get<EntityLoader>();
	m_player = loader->load("Player.txt");

	//
	m_eventDispatcher->dispatch(new CurrentPlayerChangedEvent(m_player));
	//
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
}

void GameEngine::initSystems()
{
}
