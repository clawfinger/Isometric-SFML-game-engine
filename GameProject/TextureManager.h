#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <iostream>
#include <memory>
#include "ActorsIds.h"
#include "Utils/Meta.h"

namespace TextureId
{
	static std::string wall() { return std::string("wall"); };
	static std::string floor1() { return std::string("floor1"); };
	static std::string floor2() { return std::string("floor2"); };
	static std::string floor3() { return std::string("floor3"); };
	static std::string floor4() { return std::string("floor4"); };
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