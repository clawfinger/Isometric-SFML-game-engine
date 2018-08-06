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

void EntityManager::spawnCharacters()
{
	//change map for multiple characters spawn
	sf::Vector2f playerSpawn = m_map->getPlayerSpawnCoordinate();
	for (auto characterId : m_charactersIds)
	{
		PositionComponent* positionComponent =
			m_entityContainer->getComponent<PositionComponent>(characterId, typeName<PositionComponent>());
		positionComponent->setPosition(playerSpawn);
		m_eventDispatcher->dispatch(new EntityCreatedEvent(characterId, m_entityTypes[EntityType::character]));
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

std::vector<EntityId> EntityManager::loadCharacters()
{

	std::ifstream charactersFile;
	std::string filename = "Characters.txt";

	std::string line;
	charactersFile.open(filename);

	while (std::getline(charactersFile, line))
	{
		std::stringstream s_stream(line);
		std::string type;
		s_stream >> type;
		if (type == "#begin")
		{
			CharacterData data;
			std::stringstream ss;
			std::getline(charactersFile, line);
			while (line != "#end")
			{
				ss << line << std::endl;
				std::getline(charactersFile, line);
			}
			ClassMetaInfo<CharacterData>::deserialize(data, ss);
			m_charactersData.emplace(data.name, data);
		}
	}
	charactersFile.close();

	for (const auto& character : m_charactersData)
	{
		m_charactersIds.push_back(createCharacterFromData(character.second));
	}
	return m_charactersIds;
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
			std::getline(enemiesFile, line);
			while (line != "#end")
			{
				ss << line << std::endl;
				std::getline(enemiesFile, line);
			}
			ClassMetaInfo<EnemyData>::deserialize(data, ss);
			m_enemiesData.emplace(data.name, data);
		}
	}
	enemiesFile.close();


}

EnemyData & EntityManager::getRandomEnemyData()
{
	int max = m_enemiesData.size() - 1;
	auto random_it = std::next(std::begin(m_enemiesData), getRandomInRange<int>(0, max));
	return random_it->second;
}

EntityId EntityManager::createCharacterFromData(const CharacterData & data) const
{
	EntityId entity = m_entityContainer->createEntity(m_entityTypes.at(EntityType::character));

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
	return entity;
}
