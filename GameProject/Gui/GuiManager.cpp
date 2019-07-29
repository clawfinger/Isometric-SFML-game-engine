#include "GuiManager.h"
#include "../Events/Events.h"

GuiManager::GuiManager(std::shared_ptr<EventDispatcher> dispatcher, std::shared_ptr<Window> window):
	m_eventDispatcher(dispatcher),
	m_window(window)
{
}

void GuiManager::update(sf::Time deltaTime)
{

}

void GuiManager::render()
{

}

void GuiManager::handlePlayerInput(sf::Event&)
{

}
