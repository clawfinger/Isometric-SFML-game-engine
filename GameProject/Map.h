#pragma once
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MapTile
{
public:
	MapTile(sf::Texture& texture);
	bool isWalkable();
	void setWalkability(bool walkable);
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);
	sf::Sprite& sprite();
private:
	sf::Sprite m_sprite;
	bool m_walkable;
};

class Map
{
public:
	Map();
	Map(int tileWidth, int tileHeight);
	void loadMap(std::string fileName, int mapWidth, int mapHeight, const TextureManager& textures);
	//sf::Vector2i /*map size*/ loadMap(std::string fileName, const TextureManager& textures); //TODO
	sf::Vector2i mapFromScreen(float x, float y);
	bool isWalkable(sf::Vector2i tile);
	bool isWalkable(int x, int y);
	int mapWidth();
	int mapHeight();
	MapTile& getMapTile(int x, int y);

private:
	std::vector<MapTile> m_mapTiles;
	int m_mapWidth;
	int m_mapHeight;
	int m_tileWidth;
	int m_tileHeight;
};
