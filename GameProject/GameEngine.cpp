#include "stdafx.h"
#include "GameEngine.h"
#include "ActorManager.h"
#include "Window.h"
#include "Map.h"
#include "Events/Events.h"
#include <iostream>

GameEngine::GameEngine(StateSharedContext* context) : m_actorManager(context), m_sharedContext(context)
{
	setActiveCharacter(CharacterId::swordsman());
	m_activeCharacter->setPosition(m_sharedContext->map->getPlayerSpawnCoordinate());
	sf::Vector2f enemySpawn = m_sharedContext->map->getEnemySpawnCoordinate();
	Actor* enemy = m_actorManager.createEnemy(EnemyId::enemy());
	enemy->setPosition(enemySpawn);
	m_enemies.insert({ EnemyId::enemy(), enemy });
	//
	m_sharedContext->eventDispatcher->subscribe(typeName<TestEvent>(), this);
	//
}


GameEngine::~GameEngine()
{
}

void GameEngine::draw(Window* window)
{
	for (auto& enemy : m_enemies)
	{
		enemy.second->draw(m_sharedContext->window);
	}
	for (auto& character : m_team)
	{
		character.second->draw(m_sharedContext->window);
	}
}

void GameEngine::update(sf::Time deltaTime)
{
	for (auto& enemy : m_enemies)
	{
		enemy.second->update(deltaTime);
	}
	for (auto& character : m_team)
	{
		character.second->update(deltaTime);
	}
}

void GameEngine::setActiveCharacter(std::string id)
{
	auto character = m_team.find(id);
	if (character != m_team.end())
		m_activeCharacter = m_team[id];
	else
	{
		std::cout << "ERROR: Requested character not created! Creating and setting active" << std::endl;
		Actor* newChar = m_actorManager.createCharacter(id);
		m_team[id] = newChar;
		m_activeCharacter = newChar;
	}
}

void GameEngine::createCharacter(std::string id)
{
}

void GameEngine::createEnemy(std::string id)
{
}

Actor * GameEngine::activeCharacter()
{
	return m_activeCharacter;
}

void GameEngine::notify(IEvent * event)
{
	std::cout << "GameEngine: " << event->name() << std::endl;
}

