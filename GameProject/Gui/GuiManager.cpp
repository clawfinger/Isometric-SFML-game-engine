#include "SFML/Main.hpp"
#include "GuiManager.h"
#include "../Events/Events.h"
#include "../Window.h"
#include "Layout.h"
#include "Button.h"

GuiManager::GuiManager(std::shared_ptr<EventDispatcher> dispatcher, std::shared_ptr<Window> window):
	m_eventDispatcher(dispatcher),
    m_window(window)
{
    m_currentState = GameStateId::level;
    Layout* layout = new Layout("Layout");
    layout->setSize(Vector2D<int>(80, 120));
    layout->setPosition(Vector2D<int>(10, 10));
    Widget* button = new Button("Button", layout);
    button->setSize(Vector2D<int>(60, 30));
    button->setPosition(Vector2D<int>(10, 10));
    layout->addWidget(button);
    m_screenContainer[m_currentState].push_back(layout);
}

void GuiManager::update(sf::Time deltaTime)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    for (auto widget: m_screenContainer[m_currentState])
        widget->update(deltaTime, Vector2D<int>(mousePos.x, mousePos.y));
}

void GuiManager::render()
{
    for (auto widget: m_screenContainer[m_currentState])
        if (widget->isVisible())
            widget->draw(&m_window->getRenderWindow());
}

bool GuiManager::handlePlayerInput(sf::Event& event)
{
    bool result = false;
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            for (auto widget: m_screenContainer[m_currentState])
            {
                Vector2D<int> coords = Vector2D<int>(event.mouseButton.x, event.mouseButton.y);
                if (widget->isInside(coords))
                {
                    widget->onMousePress(coords);
                    result = true;
                }
            }
        }
        break;
    }
    case sf::Event::MouseButtonReleased:
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            for (auto widget: m_screenContainer[m_currentState])
            {
                Vector2D<int> coords = Vector2D<int>(event.mouseButton.x, event.mouseButton.y);
                if (widget->isInside(coords))
                {
                    widget->onMouseRelease(coords);
                    result = true;
                }
            }
        }
        break;
    }
    case sf::Event::MouseMoved:
    {
        for (auto widget: m_screenContainer[m_currentState])
        {
            Vector2D<int> coords = Vector2D<int>(event.mouseMove.x, event.mouseMove.y);
            if (widget->isInside(coords))
            {
                widget->onMouseHover(coords);
            }
            else
            {
                widget->onMouseLeave();
            }
        }
        break;
    }
    default:
        return false;
    }
    return result;
}
