#include "stdafx.h"
#include "../../ECS/EntityContainer.h"
#include "../Components/PathComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteOrientationComponent.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Map.h"
#include "../../Utils/Logger.h"
#include "MovementSystem.h"


MovementSystem::MovementSystem(DiContainer* container):
	SystemBase(typeName<MovementSystem>())
{
	m_requirements << typeName<PathComponent>();
	m_requirements << typeName<PositionComponent>();

	m_entityContainer = container->get<EntityContainer>();
	m_eventDispatcher = container->get<EventDispatcher>();
	m_map = container->get<Map>();

	m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
	m_eventDispatcher->subscribe(typeName<SetDestinationForEntityEvent>(), this);
}

void MovementSystem::update(sf::Time deltatime)
{
	sf::Time time = sf::seconds(0.15f);
	for (EntityId entity : m_entities)
	{
		PathComponent* pathComponent =
			m_entityContainer->getComponent<PathComponent>(entity, typeName<PathComponent>());
		PositionComponent* positionComponent =
			m_entityContainer->getComponent<PositionComponent>(entity, typeName<PositionComponent>());

		//If entity reach tile pause is not finished
		if (positionComponent->getPauseClock().getElapsedTime() < time)
			return;

		if (pathComponent->isPathSet())
		{
			if (pathComponent->getPath().top() != positionComponent->getPosition())
			{
				sf::Vector2f playerMoveVector = pathComponent->getPath().top() - positionComponent->getPosition();
				sf::Vector2f normalazedVector = Vector::normalize<sf::Vector2f>(playerMoveVector);

				//Update sprite orientation if needed
				if (m_entityContainer->HasComponent(entity, typeName<SpriteOrientationComponent>()))
					updateOrientation(normalazedVector, entity);

				sf::Vector2f movement = normalazedVector * deltatime.asSeconds() * positionComponent->actorSpeed();

				//Entity reach tile on current move
				if (Vector::length<sf::Vector2f>(playerMoveVector) < Vector::length<sf::Vector2f>(movement))
				{
					positionComponent->setPosition(pathComponent->getPath().top());
					m_eventDispatcher->dispatch(new PlayerReachTileEvent(pathComponent->getPath().top()));
					pathComponent->getPath().pop();
					//restart entity tile reach pause
					positionComponent->getPauseClock().restart();
				}
				else
				{
					positionComponent->move(movement);
				}

			}
			else
			{
				pathComponent->getPath().pop();
			}
		}
	}
}

void MovementSystem::notify(IEvent * event)
{
	if (event->name() == typeName<EntityCreatedEvent>())
		handleEntitySpawnEvent(event);
	else if (event->name() == typeName<SetDestinationForEntityEvent>())
		handleSetDestinationEvent(event);
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

void MovementSystem::handleSetDestinationEvent(IEvent * event)
{
	SetDestinationForEntityEvent *currentEvent = dynamic_cast<SetDestinationForEntityEvent *>(event);
	if (nullptr != currentEvent)
	{
		PathComponent* pathComponent = 
			m_entityContainer->getComponent<PathComponent>(currentEvent->entity, typeName<PathComponent>());
		PositionComponent* positionComponent = 
			m_entityContainer->getComponent<PositionComponent>(currentEvent->entity, typeName<PositionComponent>());

		//player clicked on the same destination tile twice
		if (pathComponent->getPathEnd() == currentEvent->mapIndex)
			return;

		//player reset entity path while it was moving, finishing current movement
		if (pathComponent->isPathSet())
		{
			std::stack<sf::Vector2f> tempPath;
			tempPath.push(pathComponent->getPath().top());
			pathComponent->setPath(tempPath, m_map->mapFromWindow(pathComponent->getPath().top()));
			return;
		}
		pathComponent->setPath(m_map->calculatePath(
			m_map->mapFromWindow(positionComponent->getPosition()), currentEvent->mapIndex), currentEvent->mapIndex);
	}
}

void MovementSystem::updateOrientation(const sf::Vector2f & movement, EntityId id)
{
	SpriteOrientationComponent* orientationComponent =
		m_entityContainer->getComponent<SpriteOrientationComponent>(id, typeName<SpriteOrientationComponent>());

	if (orientationComponent->orientation() == SpriteOrientation::left && movement.x > 0)
	{
		orientationComponent->setOrientation(SpriteOrientation::right);
		m_eventDispatcher->dispatch(new EntityChangedOrientationEvent(id));
	}
	else if (orientationComponent->orientation() == SpriteOrientation::right && movement.x < 0)
	{
		orientationComponent->setOrientation(SpriteOrientation::left);
		m_eventDispatcher->dispatch(new EntityChangedOrientationEvent(id));
	}
}

MovementSystem::~MovementSystem()
{
}
