#include "GameLevelState.h"
#include "../Events/Events.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

GameLevelState::GameLevelState(DiContainer* container): m_container(container)
{	
	m_gameEngine = std::make_shared<GameEngine>(container);
	m_window = m_container->get<Window>();
	m_map = m_container->get<Map>();
	m_eventDispatcher = m_container->get<EventDispatcher>();

	m_map->loadLevel(LevelTypes::dungeon);
}


GameLevelState::~GameLevelState()
{
}

void GameLevelState::update(sf::Time deltaTime)
{
	m_window->update(deltaTime);
	m_gameEngine->update(deltaTime);
}

void GameLevelState::render()
{
	m_map->draw(m_window);
	m_gameEngine->draw(m_window);
}

void GameLevelState::handlePlayerInput(sf::Event& event)
{
	m_gameEngine->handlePlayerInput(event);
}

void GameLevelState::onDeactivate()
{
}
