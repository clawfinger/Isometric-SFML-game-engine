#include "stdafx.h"
#include "EntityMapPositionSystem.h"
#include "../../ECS/EntityContainer.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../Components/PathComponent.h"
#include "../Components/PositionComponent.h"
#include "../../Map.h"

EntityMapPositionSystem::EntityMapPositionSystem(DiContainer* container): SystemBase(typeName<EntityMapPositionSystem>())
{
	m_entityContainer = container->get<EntityContainer>();
	m_eventDispatcher = container->get<EventDispatcher>();
	m_map = container->get<Map>();

	m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
}

EntityMapPositionSystem::~EntityMapPositionSystem()
{
}


void EntityMapPositionSystem::update(sf::Time deltaTime)
{
}

void EntityMapPositionSystem::notify(IEvent * event)
{
	if (event->name() == typeName<EntityCreatedEvent>())
		handleEntitySpawnEvent(event);
}

void EntityMapPositionSystem::handleEntitySpawnEvent(IEvent* event)
{
	EntityCreatedEvent *currentEvent = dynamic_cast<EntityCreatedEvent *>(event);
	if (nullptr != currentEvent)
	{
		addEntity(currentEvent->id);
	}
}

EntityId EntityMapPositionSystem::getEntityAtMapXY(int x, int y)
{
	sf::Vector2f mapPosition = m_map->windowFromMap(x, y);
	for (EntityId entity: m_entities)
	{
		PositionComponent* positionComponent =
			m_entityContainer->getComponent<PositionComponent>(entity, typeName<PositionComponent>());

		
		if(m_entityContainer->HasComponent(entity, typeName<PathComponent>()))
		PathComponent* pathComponent =
			m_entityContainer->getComponent<PathComponent>(entity, typeName<PathComponent>());
	}
	return -1;
}