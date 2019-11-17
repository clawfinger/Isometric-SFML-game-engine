#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "Utils/StructSerialization.h"

namespace EnemyId
{
    static const std::string Rat = "ratman";
};

namespace CharacterId
{
	static const std::string Toughguy = "Toughguy";
	static const std::string frog = "frog";
}

namespace EntityState
{
	static const std::string idle = "idle";
	static const std::string moving = "moving";
};

struct EnemyData
{
	EnemyData()
	{
		ClassMetaInfo<EnemyData>::registerMember<std::string>("name", &EnemyData::name);
		ClassMetaInfo<EnemyData>::registerMember<Vector2f>("spriteOrigin", &EnemyData::spriteOrigin);
		ClassMetaInfo<EnemyData>::registerMember<Vector2f>("spriteSize", &EnemyData::spriteSize);
		ClassMetaInfo<EnemyData>::registerMember<std::string>("textureId", &EnemyData::textureId);
		ClassMetaInfo<EnemyData>::registerMember<float>("movementSpeed", &EnemyData::movementSpeed);
		ClassMetaInfo<EnemyData>::registerMember<int>("vision", &EnemyData::vision);

	}
	std::string name;
	sf::IntRect defaultTextureRect;
	Vector2f spriteOrigin;
	Vector2f spriteSize;
	std::string textureId;
	float movementSpeed;
	int vision;
};

struct CharacterData
{
	CharacterData()
	{
		ClassMetaInfo<CharacterData>::registerMember<std::string>("name", &CharacterData::name);
		ClassMetaInfo<CharacterData>::registerMember<Vector2f>("spriteOrigin", &CharacterData::spriteOrigin);
		ClassMetaInfo<CharacterData>::registerMember<Vector2f>("spriteSize", &CharacterData::spriteSize);
		ClassMetaInfo<CharacterData>::registerMember<std::string>("textureId", &CharacterData::textureId);
		ClassMetaInfo<CharacterData>::registerMember<float>("movementSpeed", &CharacterData::movementSpeed);
		ClassMetaInfo<CharacterData>::registerMember<int>("vision", &CharacterData::vision);

	}
	std::string name;
	sf::IntRect defaultTextureRect;
	Vector2f spriteOrigin;
	Vector2f spriteSize;
	std::string textureId;
	float movementSpeed;
	int vision;
};
