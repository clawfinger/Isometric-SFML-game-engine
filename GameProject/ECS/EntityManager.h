#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "../Utils/Utility.h"
#include "../Utils/Meta.h"
#include "../ActorsIds.h"

class EntityContainer;
class EventDispatcher;
class TextureManager;
class Map;

class EntityManager
{
public:
	EntityManager(std::shared_ptr<EntityContainer> entityContainer,
		std::shared_ptr<EventDispatcher> eventDispatcher,
		std::shared_ptr<TextureManager> textureManager,
		std::shared_ptr<Map> map);
	~EntityManager();
	std::vector<EntityId> loadCharacters();
	void spawnCharacters();
	void spawnEnemy(LevelTypes mapType);

private:
	void loadEntityTypes();
	void loadEnemies();
	EnemyData& getRandomEnemyData();
	EntityId createCharacterFromData(const CharacterData& data) const;

private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<TextureManager> m_textureManager;
	std::shared_ptr<Map> m_map;

	std::vector<EntityId> m_charactersIds;
	std::unordered_map<std::string, EnemyData> m_enemiesData;
	std::unordered_map<std::string, CharacterData> m_charactersData;
	std::unordered_map<std::string, StringList> m_entityTypes;

};
REGISTER_TYPENAME(EntityManager)
