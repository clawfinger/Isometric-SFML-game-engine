#pragma once

#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "../Utils/Meta.h"

class EventDispatcher;
class Window;

class GuiManager
{
public:
	GuiManager(std::shared_ptr<EventDispatcher> dispatcher, std::shared_ptr<Window> window);
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Event&);

private:
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<Window> m_window;
};
REGISTER_TYPENAME(GuiManager)