#pragma once
#include <memory>

class EventDispatcher;

class GuiEventController
{
public:
    GuiEventController(std::shared_ptr<EventDispatcher> dispatcher);
    void elementPressed(const std::string& name) const;

private:
    std::shared_ptr<EventDispatcher> m_eventDispatcher;
};
