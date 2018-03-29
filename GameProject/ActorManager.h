#pragma once
#include <unordered_map>
#include <functional>
#include "Player.h"
#include "SharedContext.h"
#include "ActorsIds.h"

class ActorManager
{
public:
	ActorManager();
	~ActorManager();
	void createCharacter(std::string id);
	Actor* createEnemy(std::string id);
	void setActiveCharacter(std::string id);
	Actor* activeCharacter();
	void setSharedContext(StateSharedContext context);

private:
	template <typename T>
	void registerCharacterFactory(std::string id);
	template <typename T>
	void registerEnemyFactory(std::string id);

private:
	Actor* m_activeCharacter;
	std::unordered_map<std::string, Actor*> m_team;
	StateSharedContext m_sharedContext;
	std::unordered_map<std::string, std::function<Actor*()>> m_characterFactories;
	std::unordered_map<std::string, std::function<Actor*()>> m_enemyFactories;
};

template<typename T>
inline void ActorManager::registerCharacterFactory(std::string id)
{
	m_characterFactories[id] = []()->Actor*
	{
		return new T();
	};
}

template<typename T>
inline void ActorManager::registerEnemyFactory(std::string id)
{
	m_enemyFactories[id] = []()->Actor*
	{
		return new T();
	};
}
