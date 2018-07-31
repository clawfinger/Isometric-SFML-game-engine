#include "stdafx.h"
#include "EntityVisionSystem.h"
#include "../Components/PositionComponent.h"
#include "../Components/VisionComponent.h"
#include "../Components/AIControlledComponent.h"
#include "../../ECS/EntityContainer.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../../Utils/Logger.h"

EntityVisionSystem::EntityVisionSystem(DiContainer* container): SystemBase(typeName<EntityVisionSystem>())
{
	m_requirements << typeName<PositionComponent>();
	m_requirements << typeName<VisionComponent>();


	m_entityContainer = container->get<EntityContainer>();
	m_eventDispatcher = container->get<EventDispatcher>();

	m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
	m_eventDispatcher->subscribe(typeName<PlayerReachTileEvent>(), this);
}


EntityVisionSystem::~EntityVisionSystem()
{
}


void EntityVisionSystem::update(sf::Time deltaTime)
{
}

void EntityVisionSystem::notify(IEvent * event)
{
	if (event->name() == typeName<EntityCreatedEvent>())
		handleEntitySpawnEvent(event);
	else if (event->name() == typeName<PlayerReachTileEvent>())
		handleEntityReachTileEvent(event);
}

void EntityVisionSystem::handleEntitySpawnEvent(IEvent * event)
{
	EntityCreatedEvent *currentEvent = dynamic_cast<EntityCreatedEvent *>(event);
	if (nullptr != currentEvent)
	{
		if (fitsRequirements(currentEvent->components))
		{
			if (m_entityContainer->HasComponent(currentEvent->id, typeName<AIControlledComponent>()))
				m_enemies.push_back(currentEvent->id);
			else
				m_characters.push_back(currentEvent->id);
		}
	}
}

void EntityVisionSystem::handleEntityReachTileEvent(IEvent * event)
{
	PlayerReachTileEvent *currentEvent = dynamic_cast<PlayerReachTileEvent *>(event);
	if (nullptr != currentEvent)
	{
		if (m_entityContainer->HasComponent(currentEvent->entity, typeName<AIControlledComponent>()))
			Logger::instance().log("Enemy " + std::to_string(currentEvent->entity) + " has reached coords " + std::to_string(currentEvent->pos.x) + ":" + std::to_string(currentEvent->pos.y));
		else
			Logger::instance().log("Player " + std::to_string(currentEvent->entity) + " has reached coords " + std::to_string(currentEvent->pos.x) + ":" + std::to_string(currentEvent->pos.y));
	}
}
