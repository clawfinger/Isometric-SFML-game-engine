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
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            for (auto widget: m_screenContainer[GameStateId::level])
            {
                Vector2D<int> coords = Vector2D<int>(event.mouseButton.x, event.mouseButton.y);
                if (widget->isInside(coords))
                    widget->onMousePress(coords);
            }
        }
        break;
    }
    case sf::Event::MouseButtonReleased:
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            for (auto widget: m_screenContainer[GameStateId::level])
            {
                Vector2D<int> coords = Vector2D<int>(event.mouseButton.x, event.mouseButton.y);
                if (widget->isInside(coords))
                    widget->onMouseRelease(coords);
            }
        }
        break;
    }
    case sf::Event::MouseMoved:
    {
        for (auto widget: m_screenContainer[GameStateId::level])
        {
            Vector2D<int> coords = Vector2D<int>(event.mouseMove.x, event.mouseMove.y);
            if (widget->isInside(coords))
            {
                if (widget->getState() == WidgetState::IDLE)
                    widget->setState(WidgetState::HOVER);
            }
            else
            {
                if (widget->getState() == WidgetState::HOVER)
                    widget->setState(WidgetState::IDLE);
            }
        }
        break;
    }
    }
}
