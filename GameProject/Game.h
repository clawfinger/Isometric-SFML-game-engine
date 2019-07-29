#pragma once
#include <vector>
#include <list>
#include <memory>
#include "TextureManager.h"
#include "Events/EventDispatcher.h"
#include "window.h"
#include "Map.h"
#include "State/GameStateManager.h"
#include "DiContainer/DiContainer.h"

class GuiManager;

class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void registerClassFactories();
private:
	//MEMBER ORDER MATTERS!
	std::shared_ptr<GameStateManager> m_stateManager;
	std::shared_ptr<TextureManager> m_textureManager;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<GuiManager> m_guiManager;
	std::shared_ptr<Window> m_window;
	std::shared_ptr<sf::View> view;
	std::shared_ptr<Map> m_map;

	DiContainer m_container;

	bool isRunning;
	sf::Time m_timePerFrame;
};
