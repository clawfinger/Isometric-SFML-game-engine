#pragma once
#include <memory>

class EventDispatcher;

class GuiEventController
{
public:
    GuiEventController(std::shared_ptr<EventDispatcher> dispatcher);
    virtual ~GuiEventController() = default;
    void virtual elementPressed(const std::string& name) const = 0;

protected:
    std::shared_ptr<EventDispatcher> m_eventDispatcher;
};
