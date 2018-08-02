#include "stdafx.h"
#include "EntityVisionSystem.h"
#include "../Components/PositionComponent.h"
#include "../Components/VisionComponent.h"
#include "../Components/AIControlledComponent.h"
#include "../../ECS/EntityContainer.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../../Map.h"
#include "../../Utils/Logger.h"

EntityVisionSystem::EntityVisionSystem(DiContainer* container): SystemBase(typeName<EntityVisionSystem>())
{
	m_requirements << typeName<PositionComponent>();
	m_requirements << typeName<VisionComponent>();


	m_entityContainer = container->get<EntityContainer>();
	m_eventDispatcher = container->get<EventDispatcher>();
	m_map = container->get<Map>();

	//TODO: get this from settings
	m_tileHeight = 128;
	m_tileWidth = 128;

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

		checkEnemyInSight();
	}
}

bool EntityVisionSystem::checkEnemyInSight()
{
	for (EntityId character : m_characters)
	{
		PositionComponent* characterPositionComponent =
			m_entityContainer->getComponent<PositionComponent>(character, typeName<PositionComponent>());
		for (EntityId enemy : m_enemies)
		{
			PositionComponent* enemyPositionComponent =
				m_entityContainer->getComponent<PositionComponent>(enemy, typeName<PositionComponent>());
			if (isVisible(characterPositionComponent->getPosition(), enemyPositionComponent->getPosition()))
			{
				return true;
			}
		}
	}
	return false;
}

bool EntityVisionSystem::isVisible(sf::Vector2f & from, sf::Vector2f & to)
{
	int fromX = int(from.x / m_tileWidth);
	int fromY = int(from.y / m_tileHeight);
	int toX = int(to.x / m_tileWidth);
	int toY = int(to.y / m_tileHeight);

	int lenX = std::abs(toX - fromX);
	int lenY = std::abs(toY - fromY);

	int currentX = fromX;
	int currentY = fromY;

	if (lenX >= lenY)
	{
		float error = 0;
		float coefficient = float(lenY) / lenX;

		for (int i = 0; i <= lenX; i++)
		{

		}
	}
	else
	{
		float error = 0;
		float coefficient = float(lenX) / lenY;

		for (int i = 0; i <= lenY; i++)
		{

		}
	}

	return false;
}
