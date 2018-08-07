#pragma once
#include <unordered_map>
#include <memory>
#include "GameStateBase.h"
#include "SFML/Graphics.hpp"
#include "../Utils/Meta.h"
#include "../DiContainer/DiContainer.h"
#include "../Window.h"
#include "../Map.h"
#include "../Events/EventDispatcher.h"
#include "../GameEngine.h"

class GameLevelState : public GameStateBase
{
public:
	GameLevelState(DiContainer* container);
	~GameLevelState();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Event& event);
	void onDeactivate();

private:
	DiContainer* m_container;
	std::shared_ptr<Window> m_window;
	std::shared_ptr<Map> m_map;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<GameEngine> m_gameEngine;
};
REGISTER_TYPENAME(GameLevelState)
