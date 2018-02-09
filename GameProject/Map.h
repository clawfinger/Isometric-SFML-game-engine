#pragma once
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MapTile
{
public:
	MapTile();
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
	bool isWalkable(sf::Vector2i tile);
	bool isWalkable(int x, int y);
	int mapWidth();
	int mapHeight();
	MapTile& getMapTile(int x, int y);
	void aStarTest(int start, int end);
	int mapFromMouse(int x, int y);
	inline int linearFromXY(int x, int y);
	inline sf::Vector2i XYfromLinear(int linear);

private:
	std::vector<int> neighbors(int position);
	inline bool isWithinMap(int x, int y);
	int costForTile(int linearPos); // now always return 1; can change this in future

private:
	std::vector<MapTile> m_mapTiles;
	int m_mapWidth;
	int m_mapHeight;
	int m_tileWidth;
	int m_tileHeight;
};
