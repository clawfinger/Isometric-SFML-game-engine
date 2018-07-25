#pragma once
#include <memory>
#include "SystemBase.h"
#include "../../Events/Observer.h"

class EntityContainer;
class EventDispatcher;
class DiContainer;
class Window;

class RenderSystem : public SystemBase, public Observer
{
public:
	RenderSystem(DiContainer* container, std::string name);
	~RenderSystem();

	void update(sf::Time deltaTime);
	void notify(IEvent* event);
	void draw(std::shared_ptr<Window> window);
private:
	void handleEntitySpawnEvent(IEvent* event);
private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
};
REGISTER_TYPENAME(RenderSystem)
