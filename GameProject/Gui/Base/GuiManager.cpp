#include "SFML/Main.hpp"
#include "GuiManager.h"
#include "../../Events/EventDispatcher.h"
#include "../../Window.h"
#include "../ToggledButtonLayout.h"
#include "../GameLevelController.h"
#include "Button.h"

GuiManager::GuiManager(std::shared_ptr<EventDispatcher> dispatcher, std::shared_ptr<Window> window): m_eventDispatcher(dispatcher),
    m_window(window)
{
    m_controllerContainer[GameStateId::level] = new GameLevelController(m_eventDispatcher);
    m_eventDispatcher->subscribe(typeName<GameStateActivatedEvent>(), this);
    registerCallBack(typeName<GameStateActivatedEvent>(), std::bind(&GuiManager::handleGameStateChangeEvent, this, std::placeholders::_1));
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

void GuiManager::handleGameStateChangeEvent(IEvent *event)
{
    GameStateActivatedEvent* stateEvent = dynamic_cast<GameStateActivatedEvent*>(event);
    if (stateEvent == nullptr)
    {
        LOG("handleGameStateChangeEvent: wrong event type!");
        return;
    }
    m_currentState = stateEvent->state;
    m_controller = m_controllerContainer[m_currentState];
    if (m_screenContainer.count(m_currentState) == 0)
        createStateGui();
}

void GuiManager::createStateGui()
{
    LOG("Create GUI!");

    ToggledButtonLayout* layout = new ToggledButtonLayout("Layout", *m_controller);
    layout->setSize(Vector2D<int>(80, 150));
    layout->setPosition(Vector2D<int>(10, 10));

    Button* button = new Button("PartySlot_1", *m_controller, layout);
    button->setText("1");
    button->setSize(Vector2D<int>(60, 60));
    button->setPosition(Vector2D<int>(10, 10));
    layout->addButton(button);

    button = new Button("PartySlot_2", *m_controller, layout);
    button->setText("2");
    button->setSize(Vector2D<int>(60, 60));
    button->setPosition(Vector2D<int>(10, 80));
    layout->addButton(button);

    m_screenContainer[m_currentState].push_back(layout);
}
