#include "stdafx.h"
#include "EntityMapPositionSystem.h"
#include "../../ECS/EntityContainer.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../Components/PathComponent.h"
#include "../Components/SpriteComponent.h"
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

bool isInside(float pointX, float pointY, float top, float left, int width, int height)
{
	//TODO: redo the isInside check
	bool Xok = (pointX >= left) && (pointX <= (left + width));
	bool Yok = (pointY >= top) && (pointY <= (top + width));
	return Xok && Yok;
}

EntityId EntityMapPositionSystem::getEntityAtCoordinates(const sf::Vector2f & mouse)
{
	for (EntityId entity : m_entities)
	{
		PositionComponent* positionComponent =
			m_entityContainer->getComponent<PositionComponent>(entity, typeName<PositionComponent>());
		SpriteComponent* spriteComponent =
			m_entityContainer->getComponent<SpriteComponent>(entity, typeName<SpriteComponent>());

		if (isInside(mouse.x, mouse.y,
			positionComponent->getPosition().y,
			positionComponent->getPosition().x,
			spriteComponent->getSprite().getGlobalBounds().width,
			spriteComponent->getSprite().getGlobalBounds().height))
			return entity;

	}
	return -1;
}