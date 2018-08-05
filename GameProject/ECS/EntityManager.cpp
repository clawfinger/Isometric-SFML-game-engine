#include "stdafx.h"
#include "SFML/System/Vector2.hpp"
#include "../Utils/Logger.h"
#include "../Utils/Utility.h"
#include "../Utils/StructSerialization.h"
#include "../TextureManager.h"
#include "EntityContainer.h"
#include "../Events/Events.h"
#include "../Events/EventDispatcher.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Components/PositionComponent.h"
#include "../ECS/Components/SpriteOrientationComponent.h"
#include "../ECS/Components/VisionComponent.h"
#include "../Map.h"
#include "Entity.h"
#include "EntityManager.h"
#include <sstream>
#include <fstream>
#include <iterator>

EntityManager::EntityManager(std::shared_ptr<EntityContainer> entityContainer,
	std::shared_ptr<EventDispatcher> eventDispatcher,
	std::shared_ptr<TextureManager> textureManager,
	std::shared_ptr<Map> map):
	m_entityContainer(entityContainer),
	m_eventDispatcher(eventDispatcher),
	m_textureManager(textureManager),
	m_map(map)
{
	loadEntityTypes();
}


EntityManager::~EntityManager()
{
}

std::vector<EntityId> EntityManager::loadCharacters()
{
	std::ifstream charFile;
	std::string filename = "Characters.txt";

	charFile.open(filename);
	if (!charFile.is_open())
	{
		Logger::instance().log("ERROR: Characters file " + filename + " failed to load!");
		return std::vector<EntityId>();
	}

	std::string line;
	EntityId entity = m_entityContainer->createEntity(m_entityTypes[EntityType::player]);

	while (std::getline(charFile, line))
	{
		std::stringstream s_stream(line);
		std::string type;
		s_stream >> type;
		if (type == "Name") {
			std::string name;
			s_stream >> name;
			Logger::instance().log("Loaded character: " + name);
		}
		else if (type == "Component")
		{
			std::string comp;
			s_stream >> comp;
			if (comp == typeName<SpriteComponent>())
			{
				SpriteComponent* spriteComp = m_entityContainer->getComponent<SpriteComponent>(entity, comp);
				if (spriteComp)
				{
					s_stream >> comp;
					spriteComp->create(m_textureManager->get(comp));
					spriteComp->readData(s_stream);
				}
			}
			else
			{
				ComponentBase* component = m_entityContainer->getComponent<ComponentBase>(entity, comp);
				if (component)
					component->readData(s_stream);
				else
				{
					Logger::instance().log("ERROR: Cannot get component " + comp + " from entity container!");
				}
			}
		}
	}
	m_chacters.push_back(entity);
	charFile.close();
	return m_chacters;
}

void EntityManager::spawnCharacters()
{
	//change map for multiple characters spawn
	sf::Vector2f playerSpawn = m_map->getPlayerSpawnCoordinate();
	for (auto characterId : m_chacters)
	{
		PositionComponent* positionComponent =
			m_entityContainer->getComponent<PositionComponent>(characterId, typeName<PositionComponent>());
		positionComponent->setPosition(playerSpawn);
		m_eventDispatcher->dispatch(new EntityCreatedEvent(characterId, m_entityTypes[EntityType::player]));
	}
}

void EntityManager::spawnEnemy(LevelTypes mapType)
{
	loadEnemies();
	EnemyData data = getRandomEnemyData();

	EntityId entity = m_entityContainer->createEntity(m_entityTypes[EntityType::enemy]);

	SpriteComponent* spriteComp = m_entityContainer->getComponent<SpriteComponent>(entity, typeName<SpriteComponent>());
	if (spriteComp)
	{
		spriteComp->create(m_textureManager->get(data.textureId));
		spriteComp->getSprite().setOrigin(data.spriteOrigin);
	}
	PositionComponent* positionComponent =
		m_entityContainer->getComponent<PositionComponent>(entity, typeName<PositionComponent>());
	if (positionComponent)
	{
		positionComponent->setActorSpeed(data.movementSpeed);
		sf::Vector2f enemySpawn = m_map->getEnemySpawnCoordinate();
		positionComponent->setPosition(enemySpawn);
	}
	SpriteOrientationComponent* orientationComponent =
		m_entityContainer->getComponent<SpriteOrientationComponent>(entity, typeName<SpriteOrientationComponent>());
	if (orientationComponent)
	{
		orientationComponent->setRightTextureRect(data.defaultTextureRect);
	}
	VisionComponent* visionComponent =
		m_entityContainer->getComponent<VisionComponent>(entity, typeName<VisionComponent>());
	if (visionComponent)
	{
		visionComponent->setVision(data.vision);
	}
	m_eventDispatcher->dispatch(new EntityCreatedEvent(entity, m_entityTypes[EntityType::enemy]));
}

void EntityManager::loadEntityTypes()
{
	std::ifstream charFile;
	std::string filename = "EntityTypes.txt";

	charFile.open(filename);
	if (!charFile.is_open())
	{
		Logger::instance().log("ERROR: EntityTypes file " + filename + " failed to load!");
		return;
	}

	std::string line;
	StringList componentsList;

	while (std::getline(charFile, line))
	{
		std::stringstream s_stream(line);
		std::string type;
		s_stream >> type;
		std::string comp;
		while (s_stream >> comp)
			componentsList << comp;
		m_entityTypes.insert(std::make_pair(type, std::move(componentsList)));
	}
	charFile.close();
}

void EntityManager::loadEnemies()
{
	std::ifstream enemiesFile;
	std::string filename = "Enemies.txt";

	std::string line;
	enemiesFile.open(filename);

	while (std::getline(enemiesFile, line))
	{
		std::stringstream s_stream(line);
		std::string type;
		s_stream >> type;
		if (type == "#begin")
		{
			EnemyData data;
			std::stringstream ss;
			std::string name;
			std::getline(enemiesFile, line);
			while (line != "#end")
			{
				ss << line << std::endl;
				std::getline(enemiesFile, line);
			}
			ClassMetaInfo<EnemyData>::deserialize(data, ss);
			m_enemies.emplace(data.name, data);
		}
	}
	enemiesFile.close();
}

EnemyData & EntityManager::getRandomEnemyData()
{
	int max = m_enemies.size() - 1;
	auto random_it = std::next(std::begin(m_enemies), getRandomInRange<int>(0, max));
	return random_it->second;
}
