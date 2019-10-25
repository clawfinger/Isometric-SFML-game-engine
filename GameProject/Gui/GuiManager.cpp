#include "GuiManager.h"
#include "../Events/Events.h"
#include "../Window.h"

GuiManager::GuiManager(std::shared_ptr<EventDispatcher> dispatcher, std::shared_ptr<Window> window):
	m_eventDispatcher(dispatcher),
    m_window(window)
{
    Widget* widget = new Layout("Layout");
    widget->setSize(Vector2D<int>(100, 50));
    widget->setPosition(Vector2D<int>(20, 20));
    m_screenContainer[GameStateId::level].push_back(widget);
}

void GuiManager::update(sf::Time deltaTime)
{

}

void GuiManager::render()
{
    for (auto widget: m_screenContainer[GameStateId::level])
        widget->draw(&m_window->getRenderWindow());
}

void GuiManager::handlePlayerInput(sf::Event& event)
{

}
