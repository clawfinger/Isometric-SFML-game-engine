#include "GameLevelController.h"
#include "../Events/EventDispatcher.h"

GameLevelController::GameLevelController(std::shared_ptr<EventDispatcher> dispatcher): GuiEventController(dispatcher)
{

}

void GameLevelController::elementPressed(const std::string &name) const
{
    if (name == "PartySlot_1")
        m_eventDispatcher->dispatch<PartySlotActiveEvent>(1);
    else if (name == "PartySlot_2")
        m_eventDispatcher->dispatch<PartySlotActiveEvent>(2);
}
