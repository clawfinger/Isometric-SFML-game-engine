#include "stdafx.h"
#include "TextureManager.h"

void TextureManager::load(TextureId id, const std::string & filename)
{
	std::unique_ptr<sf::Texture> newTexture(new sf::Texture());
	if (!newTexture->loadFromFile(filename))
	{
		std::cout << "TextureManager::load - Failed to load texture by " << filename << std::endl;
		return;
	}
	m_textureCache.insert(std::make_pair(id, std::move(newTexture)));
}

sf::Texture& TextureManager::get(TextureId id)
{
	return static_cast<const TextureManager&>(*this).get(id);
}

sf::Texture& TextureManager::get(TextureId id) const
{
	auto found = m_textureCache.find(id);
	if (found != m_textureCache.end())
		return *found->second;
	else
	{
		std::cout << "Texture " << id << " not found. Aborting";
		abort();
	}
}