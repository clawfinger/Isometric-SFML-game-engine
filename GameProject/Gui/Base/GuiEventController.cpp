#include "GuiEventController.h"
#include "../../Events/Events.h"
#include "../../Utils/Logger.h"

GuiEventController::GuiEventController(std::shared_ptr<EventDispatcher> dispatcher):
    m_eventDispatcher(dispatcher)
{

}

void GuiEventController::elementPressed(const std::string &name) const
{
    LOG("GuiEventController: element " + name + " pressed!");
}
