#pragma once
#include <unordered_map>
#include <functional>
#include "Player.h"
#include "SharedContext.h"
#include "TeamAndEnemies.h"

class ActorManager
{
public:
	ActorManager(StateSharedContext& context);
	~ActorManager();
	template <typename T>
	void registerCharacterFactory(CharacterId id);
	template <typename T>
	void registerEnemyFactory(EnemyId id);
	void createCharacter(CharacterId id);
	void setActiveCharacter(CharacterId id);
	Actor* activeCharacter();
private:
	Actor* m_activeCharacter;
	std::unordered_map<CharacterId, Actor*> m_team;
	std::unordered_map<EnemyId, Actor*> m_enemies;
	StateSharedContext m_sharedContext;
	std::unordered_map<CharacterId, std::function<Actor*()>> m_characterFactories;
	std::unordered_map<EnemyId, std::function<Actor*()>> m_enemyFactories;
};

template<typename T>
inline void ActorManager::registerCharacterFactory(CharacterId id)
{
	m_characterFactories[id] = []()->Actor*
	{
		return new T();
	}
}

template<typename T>
inline void ActorManager::registerEnemyFactory(EnemyId id)
{
	m_enemyFactories[id] = []()->Actor*
	{
		return new T();
	}
}
