#include "stdafx.h"
#include "GameEngine.h"
#include "Events/Events.h"
#include "Utils/Logger.h"
#include "EntityLoader.h"
#include "DiContainer\DiContainer.h"
#include "Events\EventDispatcher.h"
#include "ECS\EntityContainer.h"
#include "ECS\Systems\MovementSystem.h"
#include "ECS\Systems\RenderSystem.h"

GameEngine::GameEngine(DiContainer* container): m_container(container)
{
	initSystems();
	m_eventDispatcher = m_container->get<EventDispatcher>();
	m_entityContainer = m_container->get<EntityContainer>();
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
	auto system = m_systems.find(typeName<RenderSystem>());
	if (system != m_systems.end())
	{
		RenderSystem *render = dynamic_cast<RenderSystem *>(system->second);
		if (NULL != render)
		{
			render->draw(window);
		}
	}
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
	m_systems[typeName<RenderSystem>()] = new RenderSystem(m_container, typeName<RenderSystem>());
}
