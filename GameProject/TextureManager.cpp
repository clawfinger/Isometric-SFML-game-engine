#include "stdafx.h"
#include <fstream>
#include <sstream>
#include "Utils/Logger.h"
#include "TextureManager.h"

void TextureManager::preloadTextures()
{
	std::ifstream mapFile;
	std::string levelFileName;
	levelFileName = "textures.txt";
	mapFile.open(levelFileName);
	if (!mapFile.is_open())
	{
		Logger::instance().log("ERROR: Texture file " + levelFileName + " failed to load!");
		return;
	}
	std::stringstream s_stream;

	s_stream << mapFile.rdbuf();
	std::string tag;
	std::string spriteName;
	while (s_stream >> tag >> spriteName)
	{
		load(tag, "images/" + spriteName + ".png");
	}
	load(CharacterId::Toughguy, "images/toughguy.png");
	load(CharacterId::Smartguy, "images/smartguy.png");
	load(EnemyId::enemy, "images/rat.png");
}

void TextureManager::load(std::string id, const std::string & filename)
{
	std::unique_ptr<sf::Texture> newTexture(new sf::Texture());
	if (!newTexture->loadFromFile(filename))
	{
		Logger::instance().log("TextureManager::load - Failed to load texture by " + filename);
		return;
	}
	m_textureCache.insert(std::make_pair(id, std::move(newTexture)));
}

sf::Texture& TextureManager::get(std::string id)
{
	return static_cast<const TextureManager&>(*this).get(id);
}

sf::Texture& TextureManager::get(std::string id) const
{
	auto found = m_textureCache.find(id);
	if (found != m_textureCache.end())
		return *found->second;
	else
	{
		Logger::instance().log("Texture " + id + " not found. Aborting");
		abort();
	}
}