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
        m_commandQueue.push(std::make_shared<T>(m_dispatcher, args...));
    }

    void update(sf::Time deltaTime);

private:
    std::shared_ptr<EventDispatcher> m_dispatcher;
    std::queue<std::shared_ptr<CommandBase>> m_commandQueue;
    bool m_isQueueIdling;
};
