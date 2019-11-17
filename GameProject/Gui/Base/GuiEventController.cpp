#include "GuiEventController.h"
#include "../../Events/EventDispatcher.h"

GuiEventController::GuiEventController(std::shared_ptr<EventDispatcher> dispatcher):
    m_eventDispatcher(dispatcher)
{

}
