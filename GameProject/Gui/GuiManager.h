#pragma once

#include <memory>
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "../GameState.h"
#include "../Utils/Meta.h"
#include "Layout.h"

class EventDispatcher;
class Window;

class GuiManager
{
public:
	GuiManager(std::shared_ptr<EventDispatcher> dispatcher, std::shared_ptr<Window> window);
	void update(sf::Time deltaTime);
	void render();
    bool handlePlayerInput(sf::Event& event);

private:
    Vector2D<int> m_lastMousePos;
    GameStateId m_currentState;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<Window> m_window;
    std::unordered_map<GameStateId, std::vector<Widget*>> m_screenContainer;
};
REGISTER_TYPENAME(GuiManager)
