#include "stdafx.h"
#include "../Window.h"
#include "../Map.h"
#include "GameLevelState.h"
#include "../Command/CommandDispatcher.h"
#include "../Command/Commands.h"
#include "../ActorManager.h"
#include "../GameEngine.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>


GameLevelState::GameLevelState(StateSharedContext* context): m_sharedContext(context), m_gameEngine(context)
{	
}


GameLevelState::~GameLevelState()
{
}

void GameLevelState::update(sf::Time deltaTime)
{
	m_sharedContext->window->update(deltaTime);
	m_gameEngine.update(deltaTime);
}

void GameLevelState::render()
{
	m_sharedContext->window->beginDraw();

	m_sharedContext->map->draw(m_sharedContext->window->getRenderWindow());
	m_gameEngine.draw(m_sharedContext->window->getRenderWindow());

	m_sharedContext->window->endDraw();
}

void GameLevelState::handlePlayerInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		handleKeyboardInput(event.key.code);
		if (event.key.code == sf::Keyboard::F12)
			m_sharedContext->window->toggleFullScreen();
		break;
	case sf::Event::KeyReleased:
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

void GameLevelState::handleKeyboardInput(sf::Keyboard::Key key)
{
	ViewMoveCommand moveCommand;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		moveCommand.y_direction = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		moveCommand.y_direction = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveCommand.x_direction = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveCommand.x_direction = 1;

	moveCommand.m_speed = 300.f;
	m_sharedContext->commandDispatcher->execute(&moveCommand);
}

void GameLevelState::handleMouseInput(sf::Vector2i mouseCoords)
{
	sf::Vector2f mouse = m_sharedContext->window->getRenderWindow().mapPixelToCoords(mouseCoords);
	int mapIndex = m_sharedContext->map->mapFromWindow(mouse.x, mouse.y);
	if (m_sharedContext->map->isWalkable(m_sharedContext->map->XYfromLinear(mapIndex)))
	{
		SetPathCommand command(m_gameEngine.activeCharacter(), mapIndex);
		m_sharedContext->commandDispatcher->execute(&command);
	}
}
