#include "stdafx.h"
#include <iostream>
#include "TextureManager.h"
#include "Map.h"
#include "ActorManager.h"

ActorManager::ActorManager(StateSharedContext* context) : m_sharedContext(context)
{
	registerCharacterFactory<Player>(CharacterId::swordsman());
	registerEnemyFactory<Enemy>(EnemyId::enemy());
}

ActorManager::~ActorManager()
{
}

Actor* ActorManager::createCharacter(std::string id)
{
	Actor* character = nullptr;
	auto factory = m_characterFactories.find(id);
	if (factory != m_characterFactories.end())
	{
		character = factory->second();
		if (id == CharacterId::swordsman())
		{
			character->create(m_sharedContext->textureManager->get(CharacterId::swordsman()));
		}
	}
	else
	{
		std::cout << "ERROR: cannot find factory for character id=" << id << std::endl;
	}
	return character;
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
			enemy->create(m_sharedContext->textureManager->get(EnemyId::enemy()));
		}
	}
	else
	{
		std::cout << "ERROR: cannot find factory for character id=" << id << std::endl;
	}
	return enemy;
}
