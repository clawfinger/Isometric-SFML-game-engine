#pragma once
#include <unordered_map>
#include "GameStateBase.h"
#include "SFML/Graphics.hpp"
#include "../Utils/Meta.h"


class GameLevelState : public GameStateBase
{
public:
	GameLevelState();
	~GameLevelState();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Event& event);
	void onDeactivate();
private:
	void handleKeyboardInput(sf::Keyboard::Key key);
	void handleMouseInput(sf::Vector2i mouseCoords);
private:
};
REGISTER_TYPENAME(GameLevelState)
