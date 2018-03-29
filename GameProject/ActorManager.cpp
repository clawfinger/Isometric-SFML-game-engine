#include "stdafx.h"
#include <iostream>
#include "TextureManager.h"
#include "Map.h"
#include "ActorManager.h"

ActorManager::ActorManager()
{
	registerCharacterFactory<Player>(CharacterId::swordsman());
	registerEnemyFactory<Enemy>(EnemyId::enemy());
}

ActorManager::~ActorManager()
{
}

void ActorManager::createCharacter(std::string id)
{
	Actor* character = nullptr;
	auto factory = m_characterFactories.find(id);
	if (factory != m_characterFactories.end())
	{
		character = factory->second();
		if (id == CharacterId::swordsman())
		{
			character->create(m_sharedContext.textureManager->get(CharacterId::swordsman()));
			character->setPosition(m_sharedContext.map->getPlayerSpawnCoordinate());
		}
		m_team[id] = character;
	}
	else
	{
		std::cout << "ERROR: cannot find factory for character id=" << id << std::endl;
	}
}

Actor * ActorManager::createEnemy(std::string id)
{
	Actor* enemy = nullptr;
	auto factory = m_enemyFactories.find(id);
	if (factory != m_enemyFactories.end())
	{
		enemy = factory->second();
		if (id == EnemyId::enemy())
		{
			enemy->create(m_sharedContext.textureManager->get(EnemyId::enemy()));
		}
	}
	else
	{
		std::cout << "ERROR: cannot find factory for character id=" << id << std::endl;
	}
	return enemy;
}

void ActorManager::setActiveCharacter(std::string id)
{
	auto character = m_team.find(id);
	if (character != m_team.end())
		m_activeCharacter = m_team[id];
	else
	{
		std::cout << "ERROR: Requested character not created! Creating and setting active" << std::endl;
		createCharacter(id);
		m_activeCharacter = m_team[id];
	}
}

Actor * ActorManager::activeCharacter()
{
	if (!m_activeCharacter)
		std::cout << "ERROR: cannot get active character! Returned nullptr" << std::endl;

	return m_activeCharacter;
}

void ActorManager::setSharedContext(StateSharedContext context)
{
	m_sharedContext = context;
}
