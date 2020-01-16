#include "RenderSystem.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../../ECS/EntityContainer.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/SpriteOrientationComponent.h"
#include "../../Window.h"

RenderSystem::RenderSystem(DiContainer* container): SystemBase(typeName<RenderSystem>())
{
	m_requirements << typeName<SpriteComponent>();

	m_entityContainer = container->get<EntityContainer>();
	m_eventDispatcher = container->get<EventDispatcher>();
	m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
	registerCallBack(typeName<EntityCreatedEvent>(), std::bind(&RenderSystem::handleEntitySpawnEvent, this, std::placeholders::_1));
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::update(sf::Time deltaTime)
{
	for (EntityId entity : m_entities)
	{
		PositionComponent* positionComponent =
            m_entityContainer->getComponent<PositionComponent>(entity);
		SpriteComponent* spriteComponent =
            m_entityContainer->getComponent<SpriteComponent>(entity);

		spriteComponent->setPosition(positionComponent->getPosition());
	}
}

//void RenderSystem::notify(IEvent * event)
//{
//	if (event->name() == typeName<EntityCreatedEvent>())
//		handleEntitySpawnEvent(event);
//}

void RenderSystem::draw(std::shared_ptr<Window> window)
{
	m_toDraw.clear();
    sf::Vector2f SFviewTopLeft = window->getView().getCenter() - (window->getView().getSize() / 2.0f);
    sf::FloatRect viewRect(SFviewTopLeft, window->getView().getSize());

	for (EntityId entity : m_entities)
	{
		SpriteComponent* spriteComponent =
            m_entityContainer->getComponent<SpriteComponent>(entity);

        sf::Rect<float> spriteBounds = spriteComponent->getSprite().getGlobalBounds();

		if (spriteBounds.intersects(viewRect))
		{
			m_toDraw.push_back(entity);
		}
	}

	std::sort(m_toDraw.begin(), m_toDraw.end(),
		[&](EntityId entity_l, EntityId entity_r)
		{
			PositionComponent* position_l =
                m_entityContainer->getComponent<PositionComponent>(entity_l);
			PositionComponent* position_r =
                m_entityContainer->getComponent<PositionComponent>(entity_r);
			return (position_l->getPosition().y < position_r->getPosition().y);
		}

	);

	for (EntityId entity : m_toDraw)
	{
		SpriteComponent* spriteComponent =
            m_entityContainer->getComponent<SpriteComponent>(entity);
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
