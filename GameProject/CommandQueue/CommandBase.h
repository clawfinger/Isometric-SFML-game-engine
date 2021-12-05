#pragma once
#include "../Events/Observer.h"
#include "SFML/System/Time.hpp"
#include <memory>

class EventDispatcher;

class CommandBase : public Observer
{
public:
    CommandBase(std::shared_ptr<EventDispatcher> dispatcher)
    {
        m_dispatcher = dispatcher;
        m_isCompleted = false;
    }
    virtual ~CommandBase(){}
    virtual void execute() = 0;
    virtual bool isCompleted() = 0;
    virtual void update(sf::Time deltaTime) = 0;

protected:
    std::shared_ptr<EventDispatcher> m_dispatcher;
    bool m_isCompleted;
};
