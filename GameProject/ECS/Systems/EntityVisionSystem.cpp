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

		if (checkEnemyInSight(currentEvent->entity))
			Logger::instance().log("Battle!");
	}
}

bool EntityVisionSystem::checkEnemyInSight(EntityId character)
{
	PositionComponent* characterPositionComponent =
		m_entityContainer->getComponent<PositionComponent>(character, typeName<PositionComponent>());
	for (EntityId enemy : m_enemies)
	{
		PositionComponent* enemyPositionComponent =
			m_entityContainer->getComponent<PositionComponent>(enemy, typeName<PositionComponent>());
		VisionComponent* enemyVisionComponent =
			m_entityContainer->getComponent<VisionComponent>(enemy, typeName<VisionComponent>());

		if (isVisible(characterPositionComponent->getPosition(), enemyPositionComponent->getPosition(), enemyVisionComponent->getVision()))
		{
			return true;
		}
	}
	return false;
}

bool EntityVisionSystem::isVisible(sf::Vector2f & from, sf::Vector2f & to, int lengthOfSight)
{
	sf::Vector2i mapFrom = m_map->XYfromWindow(from);
	sf::Vector2i mapTo = m_map->XYfromWindow(to);

	int lenX = mapFrom.x - mapTo.x;
	int lenY = mapFrom.y - mapTo.y;

	int currentLengthOfSight = 0;
	if (lenX == 0)
	{
		if (lenY > 0)
			std::swap(mapFrom.y, mapTo.y);
		while (mapFrom.y != mapTo.y)
		{
			if (!m_map->getMapTile(mapFrom.x, mapFrom.y).isTransparent() || currentLengthOfSight > lengthOfSight)
				return false;
			currentLengthOfSight++;
			mapFrom.y++;
		}
	}
	else if (lenY == 0)
	{
		if (lenX > 0)
			std::swap(mapFrom.x, mapTo.x);
		while (mapFrom.x != mapTo.x)
		{
			if (!m_map->getMapTile(mapFrom.x, mapFrom.y).isTransparent() || currentLengthOfSight > lengthOfSight)
				return false;
			currentLengthOfSight++;
			mapFrom.x++;
		}
	}
	else
	{
		bool steep = std::abs(lenY) > std::abs(lenX);
		float error = 0;
		float coefficient = 0;
		if(std::abs(lenY) < std::abs(lenX))
			coefficient = std::abs(float(lenY) / lenX);
		else
			coefficient = std::abs(float(lenX) / lenY);

		if (steep)
		{
			std::swap(mapFrom.x, mapFrom.y);
			std::swap(mapTo.x, mapTo.y);
		}

		if (mapFrom.x - mapTo.x > 0)
		{
			std::swap(mapFrom.x, mapTo.x);
			std::swap(mapFrom.y, mapTo.y);
		}

		int Ysign = (mapFrom.y - mapTo.y > 0) ? -1 : 1;

		while (mapFrom.x != mapTo.x)
		{
			mapFrom.x++;
			error += coefficient;
			if (error > 0.5)
			{
				mapFrom.y += Ysign;
				error -= 1;
			}
			//Logger::instance().log(std::to_string(steep ? mapFrom.y : mapFrom.x) + ':' + std::to_string(steep ? mapFrom.x : mapFrom.y));
			if (!m_map->getMapTile(steep? mapFrom.y: mapFrom.x, steep? mapFrom.x: mapFrom.y).isTransparent() || currentLengthOfSight >= lengthOfSight)
				return false;
			currentLengthOfSight++;
		}
	}

	return true;
}
