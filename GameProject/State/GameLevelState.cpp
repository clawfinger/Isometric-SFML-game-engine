#include "stdafx.h"
#include "GameLevelState.h"
#include "../Events/Events.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

GameLevelState::GameLevelState(DiContainer* container): m_container(container)
{	
	m_gameEngine = std::make_shared<GameEngine>(container);
	m_window = m_container->get<Window>();
	m_map = m_container->get<Map>();
	m_eventDispatcher = m_container->get<EventDispatcher>();

	m_map->loadLevel(LevelNames::dungeon);
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
	switch (event.type)
	{
	case sf::Event::KeyReleased:
	case sf::Event::KeyPressed:
		handleKeyboardInput(event.key.code);
		break;
	case sf::Event::MouseButtonPressed:
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i coords = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
			handleMouseInput(coords);
			break;
		}
	}
	}
}

void GameLevelState::onDeactivate()
{
}

void GameLevelState::handleKeyboardInput(sf::Keyboard::Key key)
{
	sf::Vector2f viewMoveVector;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		viewMoveVector.y = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		viewMoveVector.y = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		viewMoveVector.x = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		viewMoveVector.x = 1;

	m_window->setViewMoveVector(viewMoveVector);
}

void GameLevelState::handleMouseInput(sf::Vector2i mouseCoords)
{
	sf::Vector2f mouse = m_window->getRenderWindow().mapPixelToCoords(mouseCoords);
	int mapIndex = m_map->mapFromWindow(mouse.x, mouse.y);
	if (m_map->isWalkable(m_map->XYfromLinear(mapIndex)))
	{
		IEvent* tileClicked = new FloorTileClickedEvent(mapIndex);
		m_eventDispatcher->dispatch(tileClicked);
	}
}
