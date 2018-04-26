#pragma once
#include <memory>
#include "SystemBase.h"
#include "../../Events/Observer.h"

class EntityManager;
class EventDispatcher;
class DiContainer;
class Window;

class RenderSystem : public SystemBase, Observer
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
	std::shared_ptr<EntityManager> m_entityManager;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
};
REGISTER_TYPENAME(RenderSystem)
