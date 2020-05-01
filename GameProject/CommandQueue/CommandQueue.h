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

class EntityCommandDispatcher
{
public:
    EntityCommandDispatcher(std::shared_ptr<EventDispatcher> dispatcher);

    void update(sf::Time deltaTime);

    void clearQueues();

    template <typename T, typename... Args>
    void enqueue(EntityId id, Args... args)
    {
        if (m_entityQueues.count(id) > 0)
        {
            m_entityQueues[id]->enqueue<T>(id, args...);
        }
        else
        {
            m_entityQueues[id] = std::make_shared<CommandQueue>(m_dispatcher);
            m_entityQueues[id]->enqueue<T>(id, args...);
        }
    }

private:
    std::shared_ptr<EventDispatcher> m_dispatcher;
    std::unordered_map<EntityId, std::shared_ptr<CommandQueue>> m_entityQueues;
};
