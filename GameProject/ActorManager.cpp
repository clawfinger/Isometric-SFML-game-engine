#include "stdafx.h"
#include "ActorManager.h"

ActorManager::ActorManager(StateSharedContext & context): m_sharedContext(context)
{
	registerCharacterFactory<Player>(CharacterId::swordsman);
}

ActorManager::~ActorManager()
{
}

void ActorManager::createCharacter(CharacterId id)
{
	Actor* character = nullptr;
	auto factory = m_characterFactories.find(id);
	if (factory != m_characterFactories.end())
	{
		character = factory->second();
	}
	else
	{
		std::cout << "ERROR: cannot find factory for character id=" << id << std::endl;
	}
}

void ActorManager::setActiveCharacter(CharacterId id)
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