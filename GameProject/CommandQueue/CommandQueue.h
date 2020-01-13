#pragma once
#include "SFML\System\Time.hpp"
#include "CommandBase.h"
#include <queue>

class EventDispatcher;

class CommandQueue
{
public:
    CommandQueue(std::shared_ptr<EventDispatcher> dispatcher);

    template <typename T, typename... Args>
    void enqueue(Args... args)
    {
        T command(args...);
        command.setEventDispatcher(m_dispatcher);
        command.execute();
        m_commandQueue.push(command);
    }

    void update(sf::Time deltaTime);

private:
    std::shared_ptr<EventDispatcher> m_dispatcher;
    std::queue<CommandBase> m_commandQueue;
};
