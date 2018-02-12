#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <iostream>
#include <memory>

enum TextureId
{
	floor0,
	floor1,
	floor2,
	floor3,
	floor4,
	player
};

class TextureManager
{
public:
	TextureManager() {};
	void load(TextureId id, const std::string& filename);
	sf::Texture& get(TextureId id);
	sf::Texture& get(TextureId id) const;
private:
	std::map<TextureId, std::unique_ptr<sf::Texture>> m_textureCache;
};