#pragma once
#include "TextureManager.h"
#include "Events/EventDispatcher.h"
#include "Utils/Meta.h"
#include "LevelInfo.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <memory>

class Window;

class MapTile
{
public:
	MapTile();
	MapTile(sf::Texture& texture);
	bool isWalkable();
	bool isEmpty();
	bool isTransparent();

	void setWalkability(bool walkable);
	void setEmpty(bool empty);
	void setTransparent(bool transparent);

	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);

	sf::Sprite& sprite();
private:
	sf::Sprite m_sprite;
	bool m_walkable;
	bool m_empty;
	bool m_transparent;
};

class Map
{
public:
	Map(std::shared_ptr<TextureManager> textures, std::shared_ptr<EventDispatcher> dispatcher);
	void loadLevel(LevelTypes name);
	bool isWalkable(const sf::Vector2f& tile);
	bool isWalkable(int x, int y);
	int mapWidth();
	int mapHeight();
	MapTile& getMapTile(int x, int y);
	std::stack<sf::Vector2f> calculatePath(const sf::Vector2f& from, const sf::Vector2f& to);

	sf::Vector2f windowFromMap(float x, float y);
	sf::Vector2f windowFromMap(const sf::Vector2f& map);

	sf::Vector2i XYfromWindow(sf::Vector2f& windowCoords);

	sf::Vector2i orthoXYfromIsometricCoords(sf::Vector2f& windowCoords);

	sf::Vector2f getPlayerSpawnCoordinate(); //to be removed
	sf::Vector2f getEnemySpawnCoordinate(); //to be removed

	int manhattanLength(int from, int to);

	void draw(std::shared_ptr<Window> window);

private:
	std::vector<int> neighbors(int position);
	inline bool isWithinMap(int x, int y);
	int costForTile(int linearPos); // now always return 1; can change this in future
	void initMatrix();
	inline int linearFromXY(int x, int y);
	inline sf::Vector2f XYfromLinear(int linear);

private:
	std::shared_ptr<TextureManager> m_textureManager;
	std::shared_ptr<EventDispatcher> m_EventDispatcher;

	std::vector<MapTile> m_mapTiles;

	int m_mapWidth;
	int m_mapHeight;
	int m_tileWidth;
	int m_tileHeight;
	sf::Vector2f m_playerSpawnPosition;
	sf::Vector2f m_enemySpawnPosition;
	sf::Transform m_matrix;
};
REGISTER_TYPENAME(Map)