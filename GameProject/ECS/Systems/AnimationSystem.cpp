#include "AnimationSystem.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../../ECS/EntityContainer.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/EntityStateComponent.h"
#include "../Components/SpriteOrientationComponent.h"


AnimationSystem::AnimationSystem(DiContainer* container): SystemBase(typeName<AnimationSystem>())
{
	m_requirements << typeName<SpriteComponent>();
	m_requirements << typeName<AnimationComponent>();

	m_entityContainer = container->get<EntityContainer>();
	m_eventDispatcher = container->get<EventDispatcher>();
	m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
	registerCallBack(typeName<EntityCreatedEvent>(), std::bind(&AnimationSystem::handleEntitySpawnEvent, this, std::placeholders::_1));
}


AnimationSystem::~AnimationSystem()
{
}

void AnimationSystem::update(sf::Time deltaTime)
{
	for (auto entity : m_entities)
	{
		EntityStateComponent* stateComp = m_entityContainer->getComponent<EntityStateComponent>(entity, typeName<EntityStateComponent>());
		std::string state;
		if (stateComp == nullptr)
			state = EntityState::idle;
		else
			state = stateComp->getState();
		
		AnimationComponent* animComp = m_entityContainer->getComponent<AnimationComponent>(entity, typeName<AnimationComponent>());
		if (animComp != nullptr)
		{
			AnimationComponent::Animation& currentAnim = animComp->getStateAnimation(state);
			if (currentAnim.playing)
			{
				currentAnim.elapsedTime += deltaTime.asSeconds();
				if (currentAnim.elapsedTime > currentAnim.frameTime)
				{
					currentAnim.currentFrame++;
					if (currentAnim.currentFrame >= currentAnim.frameCount)
						currentAnim.currentFrame = 0;
					SpriteComponent* spriteComp = m_entityContainer->getComponent<SpriteComponent>(entity, typeName<SpriteComponent>());
					Vector2f& size = spriteComp->getSize();

					SpriteOrientationComponent* orientComp = m_entityContainer->getComponent<SpriteOrientationComponent>(entity, typeName<SpriteOrientationComponent>());

					int row = currentAnim.row;
					if (orientComp->orientation() == SpriteOrientation::right)
						row++;

					sf::IntRect frame(currentAnim.currentFrame * size.x, row * size.y, size.x, size.y);
					spriteComp->getSprite().setTextureRect(frame);
					currentAnim.elapsedTime = 0;
				}
			}
		}
	}
}

void AnimationSystem::handleEntitySpawnEvent(IEvent * event)
{
	EntityCreatedEvent *currentEvent = dynamic_cast<EntityCreatedEvent *>(event);
	if (nullptr != currentEvent)
	{
		if (fitsRequirements(currentEvent->components))
			addEntity(currentEvent->id);
	}
}
