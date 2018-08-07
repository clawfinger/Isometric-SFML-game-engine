#pragma once
#include <memory>
#include "SystemBase.h"
#include "../../Events/Observer.h"

class EntityContainer;
class EventDispatcher;
class DiContainer;
class Window;

class VisualNotificationSystem : public SystemBase, public Observer
{
public:
	VisualNotificationSystem(DiContainer* container);
	~VisualNotificationSystem();

	void update(sf::Time deltaTime);
	void notify(IEvent* event);
	void draw(std::shared_ptr<Window> window);
private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
};
REGISTER_TYPENAME(VisualNotificationSystem)

