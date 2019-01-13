#include "AnimationComponent.h"
#include "../../Utils/Logger.h"


AnimationComponent::AnimationComponent(): ComponentBase(typeName<AnimationComponent>())
{
}


AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::readData(std::stringstream & stream)
{
	int animNum;
	stream >> animNum;
	for (int i = 0; i < animNum; ++i)
	{
		std::string state;
		stream >> state;
		ClassMetaInfo<Animation>::deserialize(m_animations[state], stream);
	}
}

AnimationComponent::Animation& AnimationComponent::getStateAnimation(const std::string & state)
{
	auto it = m_animations.find(state);
	if (it != m_animations.end())
	{
		return it->second;
	}
	else
	{
		LOG("Animation component: Animation not found for state " + state);
		return m_animations[state];
	}
}
