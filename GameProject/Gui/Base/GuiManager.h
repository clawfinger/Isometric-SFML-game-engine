#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "SFML/System/Clock.hpp"
#include "SFML/Window/Event.hpp"
#include "../../GameState.h"
#include "../../Utils/Meta.h"
#include "../../Utils/Vector2D.h"
#include "GuiEventController.h"
#include "../../Events/Events.h"
#include "../../Events/Observer.h"

class EventDispatcher;
class Window;
class Widget;

class GuiManager : public Observer
{
public:
	GuiManager(std::shared_ptr<EventDispatcher> dispatcher, std::shared_ptr<Window> window);
	void update(sf::Time deltaTime);
	void render();
	bool handlePlayerInput(sf::Event& event);

private:
    void handleGameStateChangeEvent(IEvent * event);
    void createStateGui();

private:
    GuiEventController m_controller;
	Vector2D<int> m_lastMousePos;
	GameStateId m_currentState;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
	std::shared_ptr<Window> m_window;
	std::unordered_map<GameStateId, std::vector<Widget*>> m_screenContainer;
};
REGISTER_TYPENAME(GuiManager)
