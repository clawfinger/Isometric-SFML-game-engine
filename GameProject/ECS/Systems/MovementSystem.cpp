#include "../../ECS/EntityContainer.h"
#include "../Components/PathComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteOrientationComponent.h"
#include "../Components/EntityStateComponent.h"
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
	registerCallBack(typeName<EntityCreatedEvent>(), std::bind(&MovementSystem::handleEntitySpawnEvent, this, std::placeholders::_1));
	registerCallBack(typeName<SetDestinationForEntityEvent>(), std::bind(&MovementSystem::handleSetDestinationEvent, this, std::placeholders::_1));
}

void MovementSystem::update(sf::Time deltatime)
{	
	for (EntityId entity : m_entities)
	{
		PathComponent* pathComponent =
			m_entityContainer->getComponent<PathComponent>(entity, typeName<PathComponent>());
		PositionComponent* positionComponent =
			m_entityContainer->getComponent<PositionComponent>(entity, typeName<PositionComponent>());

		if (pathComponent->isPathSet())
		{
			if (pathComponent->getPath().top() != positionComponent->getPosition())
			{
				Vector2f playerMoveVector = pathComponent->getPath().top() - positionComponent->getPosition();
				Vector2f normalazedVector = Vector::normalize<Vector2f>(playerMoveVector);

				//Update sprite orientation if needed
				if (m_entityContainer->HasComponent(entity, typeName<SpriteOrientationComponent>()))
					updateOrientation(normalazedVector, entity);

				Vector2f movement = normalazedVector * deltatime.asSeconds() * positionComponent->actorSpeed();

				//Entity reach tile on current move
				if (Vector::length<Vector2f>(playerMoveVector) < Vector::length<Vector2f>(movement))
				{
					positionComponent->setPosition(pathComponent->getPath().top());
					//m_eventDispatcher->dispatch(new PlayerReachTileEvent(pathComponent->getPath().top(), entity));
                    m_eventDispatcher->dispatch<PlayerReachTileEvent>(
                                m_map->orthoXYfromIsometricCoords(pathComponent->getPath().top()), entity);
					pathComponent->getPath().pop();
					//if entity is reached destination setting state to idle
					if (!pathComponent->isPathSet())
					{
						EntityStateComponent* stateComponent =
							m_entityContainer->getComponent<EntityStateComponent>(entity, typeName<EntityStateComponent>());
						stateComponent->setState(EntityState::idle);
						LOG("Entity " + std::to_string(entity) + " state is set to idle");
					}
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

//void MovementSystem::notify(IEvent * event)
//{
//	if (event->name() == typeName<EntityCreatedEvent>())
//		handleEntitySpawnEvent(event);
//	else if (event->name() == typeName<SetDestinationForEntityEvent>())
//		handleSetDestinationEvent(event);
//}

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
    if (nullptr == currentEvent)
        return;

    PathComponent* pathComponent =
        m_entityContainer->getComponent<PathComponent>(currentEvent->entity, typeName<PathComponent>());
    PositionComponent* positionComponent =
        m_entityContainer->getComponent<PositionComponent>(currentEvent->entity, typeName<PositionComponent>());

    //player clicked on the same destination tile twice
    if (pathComponent->getPathEnd() == currentEvent->destination)
        return;

    //player reset entity path while it was moving, finishing current movement
    if (pathComponent->isPathSet())
    {
        std::stack<Vector2f> tempPath;
        tempPath.push(pathComponent->getPath().top());
        pathComponent->setPath(tempPath, pathComponent->getPath().top());
        return;
    }
    pathComponent->setPath(m_map->calculatePath(m_map->orthoXYfromIsometricCoords(positionComponent->getPosition()), currentEvent->destination),
        currentEvent->destination);
    //Entity started moving. Setting state to moving
    EntityStateComponent* stateComponent =
        m_entityContainer->getComponent<EntityStateComponent>(currentEvent->entity, typeName<EntityStateComponent>());
    stateComponent->setState(EntityState::moving);
    LOG("Entity " + std::to_string(currentEvent->entity) + " state is set to moving");
}

void MovementSystem::updateOrientation(const Vector2f & movement, EntityId id)
{
	SpriteOrientationComponent* orientationComponent =
		m_entityContainer->getComponent<SpriteOrientationComponent>(id, typeName<SpriteOrientationComponent>());

	if (orientationComponent != nullptr)
	{
		if (orientationComponent->orientation() == SpriteOrientation::left && movement.x > 0)
		{
			orientationComponent->setOrientation(SpriteOrientation::right);
			m_eventDispatcher->dispatch<EntityChangedOrientationEvent>(id);
		}
		else if (orientationComponent->orientation() == SpriteOrientation::right && movement.x < 0)
		{
			orientationComponent->setOrientation(SpriteOrientation::left);
			m_eventDispatcher->dispatch<EntityChangedOrientationEvent>(id);
		}
	}
	else
	{
		LOG("Movement system: entity " + std::to_string(id) + " has no orientation component");
	}
}

MovementSystem::~MovementSystem()
{
}
