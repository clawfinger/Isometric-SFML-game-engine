#include "stdafx.h"
#include "RenderSystem.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../../ECS/EntityContainer.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../../Window.h"

RenderSystem::RenderSystem(DiContainer* container, std::string name): SystemBase(name)
{
	m_requirements << typeName<SpriteComponent>();

	m_entityContainer = container->get<EntityContainer>();
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
			m_entityContainer->getComponent<PositionComponent>(entity, typeName<PositionComponent>());
		SpriteComponent* spriteComponent =
			m_entityContainer->getComponent<SpriteComponent>(entity, typeName<SpriteComponent>());

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
		PositionComponent* positionComponent =
			m_entityContainer->getComponent<PositionComponent>(entity, typeName<PositionComponent>());

		sf::Vector2f viewTopLeft = window->getView().getCenter() - (window->getView().getSize() / 2.0f);
		sf::Vector2f viewDownRight = window->getView().getCenter() + (window->getView().getSize() / 2.0f);
		sf::Vector2f entityPosition = positionComponent->getPosition();

		entityPosition.x = std::round(entityPosition.x);
		entityPosition.y = std::round(entityPosition.y);

		positionComponent->setPosition(entityPosition);

		SpriteComponent* spriteComponent =
			m_entityContainer->getComponent<SpriteComponent>(entity, typeName<SpriteComponent>());

		sf::Rect<float> spriteBounds = spriteComponent->getSprite().getLocalBounds();

		if ((entityPosition.x + spriteBounds.width) > viewTopLeft.x &&
			(entityPosition.y + spriteBounds.height) > viewTopLeft.y &&
			entityPosition.x < viewDownRight.x && entityPosition.y < viewDownRight.y)
		{
			window->draw(spriteComponent->getSprite());
		}
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
