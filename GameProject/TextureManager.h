#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <iostream>
#include <memory>
#include "ActorsIds.h"
#include "Utils/Meta.h"

namespace TextureId
{
	const std::string wall = "wall";
	const std::string floor1 = "floor1";
	const std::string floor2 = "floor2";
	const std::string floor3 = "floor3";
	const std::string floor4 = "floor4";
}

class TextureManager
{
public:
	TextureManager() {};
	void load(std::string id, const std::string& filename);
	sf::Texture& get(std::string id);
	sf::Texture& get(std::string id) const;
private:
	std::map<std::string, std::unique_ptr<sf::Texture>> m_textureCache;
};
REGISTER_TYPENAME(TextureManager)