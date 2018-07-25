#pragma once
#include <memory>
#include "SystemBase.h"
#include "../../Events/Observer.h"

class EntityContainer;
class EventDispatcher;
class DiContainer;
class SpriteComponent;
class SpriteOrientationComponent;

class SpriteOrientationSystem : public SystemBase, public Observer
{
public:
	SpriteOrientationSystem(DiContainer* container, std::string name);
	~SpriteOrientationSystem();
	void update(sf::Time deltaTime) {}
	void notify(IEvent* event);

private:
	void handleEntitySpawnEvent(IEvent* event);
	void handleOrientationChangeEvent(IEvent* event);
	void updateSpriteOrientation(SpriteComponent* spriteComponent, SpriteOrientationComponent* orientationComponent);
private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
};
REGISTER_TYPENAME(SpriteOrientationSystem)
