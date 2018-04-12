#include "stdafx.h"
#include "game.h"
#include "State/GameLevelState.h"
#include "ActorsIds.h"
#include "Utils/Logger.h"
#include <iostream>
#include <fstream>

Game::Game() : isRunning(true)
{
	registerClassFactories();
	m_window = m_container.get<Window>();
	m_map = m_container.get<Map>();
	m_eventDispatcher = m_container.get<EventDispatcher>();
	m_textureManager = m_container.get<TextureManager>();
	m_stateManager = m_container.get<GameStateManager>();

	m_window->setup("SFML", sf::Vector2u(1920, 1080));
	m_timePerFrame = sf::seconds(1.0f / 60.0f);

	m_stateManager->setContainer(&m_container);

	m_textureManager->load(TextureId::wall(), "images/3.png");
	m_textureManager->load(TextureId::floor1(), "images/1.png");
	m_textureManager->load(TextureId::floor2(), "images/2.png");
	m_textureManager->load(CharacterId::swordsman(), "images/player.png");
	m_textureManager->load(EnemyId::enemy(), "images/enemy.png");

	m_map->loadLevel(LevelNames::dungeon);
	m_stateManager->activateState(GameStateType::level);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (isRunning)
	{
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
	while (m_window->getRenderWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			isRunning = false;
			return;
		}
		else if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::F12)
				m_window->toggleFullScreen();

		m_stateManager->currentState()->handlePlayerInput(event);
	}
}

void Game::update(sf::Time deltaTime)
{
	m_stateManager->currentState()->update(deltaTime);
}

void Game::render()
{
	m_window->beginDraw();

	m_stateManager->currentState()->render();	

	m_window->endDraw();
}

void Game::registerClassFactories()
{
	m_container.registerClass<TextureManager>(constructingFunction);
	m_container.registerClass<EventDispatcher>(constructingFunction);

	m_container.registerClass<Map>(constructingFunction<TextureManager, EventDispatcher>);
	m_container.registerClass<Window>(constructingFunction);
}	



