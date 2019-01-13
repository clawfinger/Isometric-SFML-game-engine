#pragma once
#include <unordered_map>
#include "ComponentBase.h"
#include "../../Utils/Meta.h"
#include "../../Utils/StructSerialization.h"
#include "../../ActorsIds.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

class AnimationComponent :public ComponentBase
{
public:
	AnimationComponent();
	~AnimationComponent();
	void readData(std::stringstream& stream);

private:
	struct Animation
	{
		Animation()
		{
			ClassMetaInfo<Animation>::registerMember<std::string>("name", &Animation::name);
			ClassMetaInfo<Animation>::registerMember<int>("frameCount", &Animation::frameCount);
			ClassMetaInfo<Animation>::registerMember<float>("frameTime", &Animation::frameTime);
			ClassMetaInfo<Animation>::registerMember<bool>("infinite", &Animation::infinite);
		}
		std::string name;
		int frameCount;
		float frameTime;
		bool infinite;

		float elapsedTime;
		int currentFrame;
		bool playing;

	};

	//state - animation
	std::unordered_map<std::string, Animation> m_animations;
};
REGISTER_TYPENAME(AnimationComponent)
