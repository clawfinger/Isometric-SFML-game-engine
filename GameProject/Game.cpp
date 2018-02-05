#include "stdafx.h"
#include "game.h"
#include <iostream>
#include <assert.h>
#include <fstream>


Game::Game() : isRunning(true), m_map(10, 10)
{
	m_window.setup("SFML", sf::Vector2u(1280, 720));
	m_timePerFrame = sf::seconds(1.0f / 60.0f);
	m_viewSpeed = 500.f;
	//m_window.resizeView(sf::Vector2f(1280, 720));

	m_textureManager.load(floor0, "images/1.png");
	m_textureManager.load(floor1, "images/3.png");
	m_textureManager.load(floor2, "images/2.png");

	m_map.loadMap("map.txt", 10, 10, m_textureManager);
	m_mapHeight = m_map.mapHeight();
	m_mapWidth = m_map.mapWidth();
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
			timeSinceLastUpdate -= m_timePerFrame;
			processEvents();
			update(m_timePerFrame);

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
		}


	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (m_isMovingUp)
		movement.y -= m_viewSpeed;
	if (m_isMovingDown)
		movement.y += m_viewSpeed;
	if (m_isMovingLeft)
		movement.x -= m_viewSpeed;
	if (m_isMovingRight)
		movement.x += m_viewSpeed;
	m_window.moveView(movement * deltaTime.asSeconds());
}

void Game::render()
{
	m_window.beginDraw();

	for (int y = 0; y < m_mapHeight; y++)
	{
		for (int x = 0; x < m_mapWidth; x++)
		{
			// TODO: remove sprite size hardcode
			sf::Vector2f position(x * 64, y * 64);
			m_map.getMapTile(x, y).setPosition(position);
			m_window.draw(m_map.getMapTile(x, y).sprite());
		}
	}

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



