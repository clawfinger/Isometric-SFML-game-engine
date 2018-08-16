#pragma once
#include <memory>
#include "SystemBase.h"
#include "../../Events/Observer.h"

class EntityContainer;
class EventDispatcher;
class DiContainer;
class Window;

namespace NotificationTypes
{
	const std::string global = "GLOBAL";
	const std::string character = "CHAR";
}

class NotificationBase
{
public:
	void draw(std::shared_ptr<Window> window);
	std::string& type() { return m_type; }

protected:
	sf::Time m_duration;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	std::string m_type;
};

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

