#include "stdafx.h"
#include "../../ECS/EntityManager.h"
#include "../../Utils/Meta.h"
#include "../Components/PathComponent.h"
#include "../Components/PositionComponent.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Map.h"
#include "../../Utils/Logger.h"
#include "MovementSystem.h"


MovementSystem::MovementSystem(DiContainer* container, std::string name):
	SystemBase(name)
{
	m_requirements << typeName<PathComponent>();
	m_requirements << typeName<PositionComponent>();

	m_entityManager = container->get<EntityManager>();
	m_eventDispatcher = container->get<EventDispatcher>();
	m_map = container->get<Map>();

	m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
	m_eventDispatcher->subscribe(typeName<FloorTileClickedEvent>(), this);
	m_eventDispatcher->subscribe(typeName<CurrentPlayerChangedEvent>(), this);
}

void MovementSystem::update(sf::Time deltatime)
{
	for (EntityId entity : m_entities)
	{
		PathComponent* pathComponent =
			m_entityManager->getComponent<PathComponent>(entity, typeName<PathComponent>());
		PositionComponent* positionComponent =
			m_entityManager->getComponent<PositionComponent>(entity, typeName<PositionComponent>());

		if (pathComponent->isPathSet())
		{
			if (pathComponent->getPath().top() != positionComponent->getPosition())
			{
				sf::Vector2f playerMoveVector = pathComponent->getPath().top() - positionComponent->getPosition();
				sf::Vector2f normalazedVector = Vector::normalize<sf::Vector2f>(playerMoveVector);
				sf::Vector2f movement = normalazedVector * deltatime.asSeconds() * positionComponent->actorSpeed();
				if (Vector::length<sf::Vector2f>(playerMoveVector) < Vector::length<sf::Vector2f>(movement))
				{
					positionComponent->setPosition(pathComponent->getPath().top());
					m_eventDispatcher->dispatch(new PlayerReachTileEvent(pathComponent->getPath().top()));
					pathComponent->getPath().pop();
				}
				else
				{
					positionComponent->move(movement);
				}

			}
			else
			{
				m_eventDispatcher->dispatch(new PlayerReachTileEvent(pathComponent->getPath().top()));
				pathComponent->getPath().pop();
			}
		}
	}
}

void MovementSystem::notify(IEvent * event)
{
	if (event->name() == typeName<EntityCreatedEvent>())
		handleEntitySpawnEvent(event);
	else if (event->name() == typeName<FloorTileClickedEvent>())
		handleTileClickedEvent(event);
	else if (event->name() == typeName<CurrentPlayerChangedEvent>())
		handlePlayerChangedEvent(event);
}

void MovementSystem::handleEntitySpawnEvent(IEvent * event)
{	
	EntityCreatedEvent *currentEvent = dynamic_cast<EntityCreatedEvent *>(event);
	if (nullptr != currentEvent)
	{
		if (fitsRequirements(currentEvent->components))
			addEntity(currentEvent->id);
	}
}

void MovementSystem::handleTileClickedEvent(IEvent * event)
{
	FloorTileClickedEvent *currentEvent = dynamic_cast<FloorTileClickedEvent *>(event);
	if (nullptr != currentEvent)
	{
		PathComponent* pathComponent = 
			m_entityManager->getComponent<PathComponent>(m_currentPlayer, typeName<PathComponent>());
		PositionComponent* positionComponent = 
			m_entityManager->getComponent<PositionComponent>(m_currentPlayer, typeName<PositionComponent>());
		pathComponent->setPath(m_map->calculatePath(
			m_map->mapFromWindow(positionComponent->getPosition()), currentEvent->mapIndex), currentEvent->mapIndex);
	}
}

void MovementSystem::handlePlayerChangedEvent(IEvent * event)
{
	CurrentPlayerChangedEvent *currentEvent = dynamic_cast<CurrentPlayerChangedEvent *>(event);
	if (nullptr != currentEvent)
	{
		m_currentPlayer = currentEvent->id;
	}
}

MovementSystem::~MovementSystem()
{
}
