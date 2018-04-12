#pragma once
#include <unordered_map>
#include <memory>
#include "GameStateBase.h"
#include "SFML/Graphics.hpp"
#include "../Utils/Meta.h"
#include "../DiContainer/DiContainer.h"
#include "../Window.h"

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
	void handleKeyboardInput(sf::Keyboard::Key key);
	void handleMouseInput(sf::Vector2i mouseCoords);
private:
	DiContainer* m_container;
	std::shared_ptr<Window> m_window;
};
REGISTER_TYPENAME(GameLevelState)
