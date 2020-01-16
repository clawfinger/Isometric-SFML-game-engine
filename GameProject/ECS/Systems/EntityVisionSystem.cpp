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
	registerCallBack(typeName<EntityCreatedEvent>(), std::bind(&EntityVisionSystem::handleEntitySpawnEvent, this, std::placeholders::_1));
	registerCallBack(typeName<PlayerReachTileEvent>(), std::bind(&EntityVisionSystem::handleEntityReachTileEvent, this, std::placeholders::_1));
}


EntityVisionSystem::~EntityVisionSystem()
{
}


void EntityVisionSystem::update(sf::Time deltaTime)
{
}

//void EntityVisionSystem::notify(IEvent * event)
//{
//	if (event->name() == typeName<EntityCreatedEvent>())
//		handleEntitySpawnEvent(event);
//	else if (event->name() == typeName<PlayerReachTileEvent>())
//		handleEntityReachTileEvent(event);
//}

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
            LOG("Enemy " + std::to_string(currentEvent->entity) + " has reached coords " + std::to_string(currentEvent->pos.x) + ":" + std::to_string(currentEvent->pos.y));
        else
        {
            LOG("Player " + std::to_string(currentEvent->entity) + " has reached coords " + std::to_string(currentEvent->pos.x) + ":" + std::to_string(currentEvent->pos.y));

            std::vector<EntityId> enemiesInBattle = checkEnemyInSight(currentEvent->entity);
            if (!enemiesInBattle.empty())
            {
                LOG("Battle!");
                m_eventDispatcher->dispatch<BattleStartedEvent>(enemiesInBattle);
            }
        }
    }
}

std::vector<EntityId> EntityVisionSystem::checkEnemyInSight(EntityId character)
{
	std::vector<EntityId> enemiesInBattle;
	PositionComponent* characterPositionComponent =
        m_entityContainer->getComponent<PositionComponent>(character);
	for (EntityId enemy : m_enemies)
	{
		PositionComponent* enemyPositionComponent =
            m_entityContainer->getComponent<PositionComponent>(enemy);
		VisionComponent* enemyVisionComponent =
            m_entityContainer->getComponent<VisionComponent>(enemy);

		if (isVisible(characterPositionComponent->getPosition(), enemyPositionComponent->getPosition(), enemyVisionComponent->getVision()))
		{
			//if the character is in field of view if enemy
			enemiesInBattle.push_back(enemy);
			//check the other enemies in the field if view of the enemy that initiated the battle
			for (EntityId subEnemy : m_enemies)
			{
				if (subEnemy == enemy)
					continue;

				PositionComponent* subEnemyPositionComponent =
                    m_entityContainer->getComponent<PositionComponent>(subEnemy);
				VisionComponent* subEnemyVisionComponent =
                    m_entityContainer->getComponent<VisionComponent>(subEnemy);
				if (isVisible(enemyPositionComponent->getPosition(), subEnemyPositionComponent->getPosition(), subEnemyVisionComponent->getVision()))
				{
					enemiesInBattle.push_back(subEnemy);
				}
			}
			break;
		}
	}
	return enemiesInBattle;
}

bool EntityVisionSystem::isVisible(Vector2f & from, Vector2f & to, int lengthOfSight)
{
	Vector2f mapFrom = m_map->orthoXYfromIsometricCoords(from);
	Vector2f mapTo = m_map->orthoXYfromIsometricCoords(to);

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
			//LOG(std::to_string(steep ? mapFrom.y : mapFrom.x) + ':' + std::to_string(steep ? mapFrom.x : mapFrom.y));
			if (!m_map->getMapTile(steep? mapFrom.y: mapFrom.x, steep? mapFrom.x: mapFrom.y).isTransparent() || currentLengthOfSight >= lengthOfSight)
				return false;
			currentLengthOfSight++;
		}
	}

	return true;
}
