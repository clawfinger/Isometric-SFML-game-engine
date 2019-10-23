#include "GuiManager.h"
#include "../Events/Events.h"
#include "../Window.h"

GuiManager::GuiManager(std::shared_ptr<EventDispatcher> dispatcher, std::shared_ptr<Window> window):
	m_eventDispatcher(dispatcher),
    m_window(window),
    m_widget(new Widget("Test"))
{
}

void GuiManager::update(sf::Time deltaTime)
{

}

void GuiManager::render()
{
    m_widget->draw(&m_window->getRenderWindow());
}

void GuiManager::handlePlayerInput(sf::Event& event)
{

}
