#include "stdafx.h"
#include "GameEngine.h"
#include "Events/Events.h"
#include "Utils/Logger.h"
#include "EntityLoader.h"
#include "DiContainer\DiContainer.h"
#include "Events\EventDispatcher.h"
#include "ECS\EntityManager.h"
#include "ECS\Systems\MovementSystem.h"
#include "ECS\Systems\RenderSystem.h"
#include "ECS\Systems\SpriteOrientationSystem.h"
#include "ECS\Systems\EntityVisionSystem.h"

GameEngine::GameEngine(DiContainer* container): m_container(container)
{
	initSystems();
	m_eventDispatcher = m_container->get<EventDispatcher>();
	m_entityManager = m_container->get<EntityManager>();
	m_characters = m_entityManager->loadCharacters();

	if (!m_characters.empty())
		m_activeCharacter = m_characters[0];

	m_eventDispatcher->subscribe(typeName<MapCreatedEvent>(), this);
}


GameEngine::~GameEngine()
{
}

void GameEngine::draw(std::shared_ptr<Window> window)
{
	m_render->draw(window);
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
	if (event->name() == typeName<MapCreatedEvent>())
	{
		handleMapCreatedEvent(event);
	}
}

EntityId GameEngine::getActiveCharacter()
{
	return m_activeCharacter;
}

void GameEngine::initSystems()
{
	m_render = new RenderSystem(m_container);
	m_systems[typeName<RenderSystem>()] = m_render;

	m_systems[typeName<MovementSystem>()] = new MovementSystem(m_container);
	m_systems[typeName<SpriteOrientationSystem>()] = new SpriteOrientationSystem(m_container); 
	m_systems[typeName<EntityVisionSystem>()] = new EntityVisionSystem(m_container);
}

void GameEngine::handleMapCreatedEvent(IEvent * event)
{
	MapCreatedEvent *currentEvent = dynamic_cast<MapCreatedEvent *>(event);
	if (nullptr != currentEvent)
	{
		m_entityManager->spawnCharacters();
		m_entityManager->spawnEnemy(currentEvent->mapType);
	}
}
