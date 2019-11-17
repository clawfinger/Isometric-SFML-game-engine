#include "GuiEventController.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../../Utils/Logger.h"

GuiEventController::GuiEventController(std::shared_ptr<EventDispatcher> dispatcher):
    m_eventDispatcher(dispatcher)
{

}

void GuiEventController::elementPressed(const std::string &name) const
{
    if (name == "PartySlot_1")
        m_eventDispatcher->dispatch<PartySlotActiveEvent>(1);
    else if (name == "PartySlot_2")
        m_eventDispatcher->dispatch<PartySlotActiveEvent>(2);
}
