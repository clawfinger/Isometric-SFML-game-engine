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
	struct Animation
	{
		Animation() : name("DEFAULT_ANIM_NAME"), frameCount(0), frameTime(0.0), infinite(false),
			elapsedTime(0), currentFrame(0), playing(true)
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

	AnimationComponent();
	~AnimationComponent();
	void readData(std::stringstream& stream);
	Animation& getStateAnimation(const std::string& state);
private:
	//state - animation
	std::unordered_map<std::string, Animation> m_animations;
};
REGISTER_TYPENAME(AnimationComponent)
