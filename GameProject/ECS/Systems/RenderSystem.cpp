#include "stdafx.h"
#include "RenderSystem.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../ECS/EntityManager.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../../Window.h"

RenderSystem::RenderSystem(DiContainer* container, std::string name): SystemBase(name)
{
	m_requirements << typeName<SpriteComponent>();

	m_entityManager = container->get<EntityManager>();
	m_eventDispatcher = container->get<EventDispatcher>();
	m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::update(sf::Time deltaTime)
{
	for (EntityId entity : m_entities)
	{
		PositionComponent* positionComponent =
			m_entityManager->getComponent<PositionComponent>(entity, typeName<PositionComponent>());
		SpriteComponent* spriteComponent =
			m_entityManager->getComponent<SpriteComponent>(entity, typeName<SpriteComponent>());

		spriteComponent->setPosition(positionComponent->getPosition());

	}
}

void RenderSystem::notify(IEvent * event)
{
	if (event->name() == typeName<EntityCreatedEvent>())
		handleEntitySpawnEvent(event);
}

void RenderSystem::draw(std::shared_ptr<Window> window)
{
	for (EntityId entity : m_entities)
	{
		SpriteComponent* spriteComponent =
			m_entityManager->getComponent<SpriteComponent>(entity, typeName<SpriteComponent>());

		window->draw(spriteComponent->getSprite());

	}
}

void RenderSystem::handleEntitySpawnEvent(IEvent * event)
{
	EntityCreatedEvent *currentEvent = dynamic_cast<EntityCreatedEvent *>(event);
	if (nullptr != currentEvent)
	{
		if (fitsRequirements(currentEvent->components))
			addEntity(currentEvent->id);
	}
}
