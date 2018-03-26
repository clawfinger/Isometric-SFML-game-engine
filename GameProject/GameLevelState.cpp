#include "stdafx.h"
#include "GameLevelState.h"
#include "Commands.h"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>


GameLevelState::GameLevelState(StateSharedContext& context): m_sharedContext(context)
{
	m_sharedContext.player->create(m_sharedContext.textureManager->get(CharacterId::swordsman()));
	m_sharedContext.player->setPosition(m_sharedContext.map->getPlayerSpawnCoordinate());
}


GameLevelState::~GameLevelState()
{
}

void GameLevelState::update(sf::Time deltaTime)
{
	m_sharedContext.window->update(deltaTime);
	m_sharedContext.player->update(deltaTime);
}

void GameLevelState::render()
{
	m_sharedContext.window->beginDraw();

	int mapHeight = m_sharedContext.map->mapHeight();
	int mapWidth = m_sharedContext.map->mapWidth();

	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			// TODO: remove sprite size hard code
			sf::Vector2f position(float(x * 64), float(y * 64));
			m_sharedContext.map->getMapTile(x, y).setPosition(position);
			m_sharedContext.window->draw(m_sharedContext.map->getMapTile(x, y).sprite());
		}
	}
	m_sharedContext.window->draw(m_sharedContext.player->getSprite());
	m_sharedContext.window->endDraw();
}

void GameLevelState::handlePlayerInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		handleKeyboardInput(event.key.code);
		if (event.key.code == sf::Keyboard::F12)
			m_sharedContext.window->toggleFullScreen();
		break;
	case sf::Event::KeyReleased:
		handleKeyboardInput(event.key.code);
		break;
	case sf::Event::MouseButtonPressed:
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mouse = m_sharedContext.window->getRenderWindow().mapPixelToCoords(
				sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			int mapIndex = m_sharedContext.map->mapFromWindow(mouse.x, mouse.y);
			if (m_sharedContext.map->isWalkable(m_sharedContext.map->XYfromLinear(mapIndex)))
			{
				SetPathCommand command(m_sharedContext.player, mapIndex);
				m_sharedContext.commandDispatcher->execute(&command);
			}
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
	m_sharedContext.commandDispatcher->execute(&moveCommand);
}
