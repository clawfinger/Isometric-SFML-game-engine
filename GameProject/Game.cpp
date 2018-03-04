#include "stdafx.h"
#include "game.h"
#include <iostream>
#include <assert.h>
#include <fstream>

Game::Game() : isRunning(true), m_map(64, 64)
{
	m_window.setup("SFML", sf::Vector2u(1280, 720));
	m_timePerFrame = sf::seconds(1.0f / 60.0f);
	m_viewSpeed = 500.f;
	//m_window.resizeView(sf::Vector2f(1280, 720));

	m_textureManager.load(floor0, "images/1.png");
	m_textureManager.load(floor1, "images/3.png");
	m_textureManager.load(floor2, "images/2.png");
	m_textureManager.load(player, "images/player.png");

	m_map.loadMap("map.txt", 10, 10, m_textureManager);
	m_mapHeight = m_map.mapHeight();
	m_mapWidth = m_map.mapWidth();
	m_player.create(m_textureManager.get(player));
	m_player.setPosition(sf::Vector2f(0 * 64, 2 * 64));

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (isRunning)
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > m_timePerFrame)
		{
			processEvents();
			update(m_timePerFrame);

			timeSinceLastUpdate -= m_timePerFrame;
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.getRenderWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			isRunning = false;
			break;
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			if (event.key.code == sf::Keyboard::F12)
				m_window.toggleFullScreen();
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mouse = m_window.getRenderWindow().mapPixelToCoords(
					sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				int mapIndex = m_map.mapFromWindow(mouse.x, mouse.y);
				if (m_map.isWalkable(m_map.XYfromLinear(mapIndex)))
				{
					if (m_player.getPathEnd() != mapIndex)
					{
						sf::Vector2f playerPosition = m_player.getPosition();
						int linearMapPlayerPosition = m_map.mapFromWindow(playerPosition.x, playerPosition.y);
						m_player.setPath(m_map.calculatePath(linearMapPlayerPosition, mapIndex), mapIndex);
					}


				}
				break;
			}
		}
		}


	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f viewMovement(0.0f, 0.0f);
	if (m_isMovingUp)
		viewMovement.y -= m_viewSpeed;
	if (m_isMovingDown)
		viewMovement.y += m_viewSpeed;
	if (m_isMovingLeft)
		viewMovement.x -= m_viewSpeed;
	if (m_isMovingRight)
		viewMovement.x += m_viewSpeed;
	m_window.moveView(viewMovement * deltaTime.asSeconds());

	m_player.update(deltaTime);
}

void Game::render()
{
	m_window.beginDraw();

	for (int y = 0; y < m_mapHeight; y++)
	{
		for (int x = 0; x < m_mapWidth; x++)
		{
			// TODO: remove sprite size hard code
			sf::Vector2f position(float(x * 64), float(y * 64));
			m_map.getMapTile(x, y).setPosition(position);
			m_window.draw(m_map.getMapTile(x, y).sprite());
		}
	}
	m_window.draw(m_player.getSprite());
	m_window.endDraw();
	
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
		m_isMovingUp = isPressed;
	if (key == sf::Keyboard::Down)
		m_isMovingDown = isPressed;
	if (key == sf::Keyboard::Left)
		m_isMovingLeft = isPressed;
	if (key == sf::Keyboard::Right)
		m_isMovingRight = isPressed;
}



