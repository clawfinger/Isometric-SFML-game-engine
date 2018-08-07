#include "stdafx.h"
#include "VisualNotificationSystem.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../../ECS/EntityContainer.h"
#include "../../Window.h"

VisualNotificationSystem::VisualNotificationSystem(DiContainer* container): SystemBase(typeName<VisualNotificationSystem>())
{
	m_entityContainer = container->get<EntityContainer>();
	m_eventDispatcher = container->get<EventDispatcher>();
	//m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
}


VisualNotificationSystem::~VisualNotificationSystem()
{
}

void VisualNotificationSystem::update(sf::Time deltaTime)
{
}

void VisualNotificationSystem::notify(IEvent * event)
{
}

void VisualNotificationSystem::draw(std::shared_ptr<Window> window)
{
}
