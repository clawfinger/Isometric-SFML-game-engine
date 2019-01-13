#include "AnimationComponent.h"



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