#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "Utils/StructSerialization.h"

namespace EnemyId
{
	static const std::string Rat = "Rat";
};

namespace CharacterId
{
	static const std::string Toughguy = "Toughguy";
	static const std::string Smartguy = "Smartguy";
}

struct EnemyData
{
	EnemyData()
	{
		ClassMetaInfo<EnemyData>::registerMember<std::string>("name", &EnemyData::name);
		ClassMetaInfo<EnemyData>::registerMember<sf::IntRect>("defaultTextureRect", &EnemyData::defaultTextureRect);
		ClassMetaInfo<EnemyData>::registerMember<sf::Vector2f>("spriteOrigin", &EnemyData::spriteOrigin);
		ClassMetaInfo<EnemyData>::registerMember<std::string>("textureId", &EnemyData::textureId);
		ClassMetaInfo<EnemyData>::registerMember<float>("movementSpeed", &EnemyData::movementSpeed);
	}
	std::string name;
	sf::IntRect defaultTextureRect;
	sf::Vector2f spriteOrigin;
	std::string textureId;
	float movementSpeed;
};