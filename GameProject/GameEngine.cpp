#include "stdafx.h"
#include "GameEngine.h"
#include "Events/Events.h"
#include "Utils/Logger.h"
#include "EntityLoader.h"
#include "DiContainer\DiContainer.h"
#include "Events\EventDispatcher.h"
#include "ECS\EntityManager.h"
#include "ECS\Systems\MovementSystem.h"

GameEngine::GameEngine(DiContainer* container): m_container(container)
{
	initSystems();
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
	for (auto& system : m_systems)
	{
		system.second->update(deltaTime);
	}
}

void GameEngine::notify(IEvent * event)
{
}

void GameEngine::initSystems()
{
	m_systems[typeName<MovementSystem>()] = new MovementSystem(m_container, typeName<MovementSystem>());
}
