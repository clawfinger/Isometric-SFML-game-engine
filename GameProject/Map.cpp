#include "stdafx.h"
#include "Map.h"
#include <fstream>

MapTile::MapTile(sf::Texture& texture): m_walkable(true)
{
	m_sprite.setTexture(texture);
}

bool MapTile::isWalkable()
{
	return m_walkable;
}

void MapTile::setWalkability(bool walkable)
{
	m_walkable = walkable;
}

void MapTile::setPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

void MapTile::setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

sf::Sprite& MapTile::sprite()
{
	return m_sprite;
}

Map::Map(): m_mapHeight(10), m_mapWidth(10), m_tileHeight(64), m_tileWidth(64)
{
}

Map::Map(int tileWidth, int tileHeight): m_mapHeight(10), m_mapWidth(10),
			m_tileHeight(tileHeight), m_tileWidth(tileWidth)
{

}

void Map::loadMap(std::string fileName, int mapWidth, int mapHeight, const TextureManager& textures)
{
	m_mapWidth = mapWidth;
	m_mapHeight = mapHeight;

	std::ifstream input(fileName);

	if (!input.is_open())
	{
		std::cout << "File open failure" << std::endl;
		return;
	}
	char character;
	input.get(character);
	while (true)
	{
		while (character != '\n')
		{
			int tileId = std::stoi(&character);
			switch (tileId)
			{
			case 0:
				m_mapTiles.push_back(MapTile(textures.get(TextureId::floor0)));
				break;
			case 1:
				m_mapTiles.push_back(MapTile(textures.get(TextureId::floor1)));
				break;
			case 2:
				m_mapTiles.push_back(MapTile(textures.get(TextureId::floor2)));
				break;
			}
			input.get(character);
		}
		input.get(character);
		if (input.peek() == EOF)
			break;

	}
	input.close();

}

sf::Vector2i Map::mapFromScreen(float x, float y)
{
	return sf::Vector2i(x / m_mapWidth, y / m_mapHeight);
}

bool Map::isWalkable(sf::Vector2i tile)
{
	return m_mapTiles[tile.x * m_mapWidth + tile.y].isWalkable();
}

bool Map::isWalkable(int x, int y)
{
	return m_mapTiles[y * m_mapWidth + x].isWalkable();
}

int Map::mapWidth()
{
	return m_mapWidth;
}

int Map::mapHeight()
{
	return m_mapHeight;
}

MapTile& Map::getMapTile(int x, int y)
{
	return m_mapTiles[y * m_mapWidth + x];
}
