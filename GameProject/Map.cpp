#include "stdafx.h"
#include "Map.h"
#include "Window.h"
#include <fstream>
#include <queue>
#include <sstream>
#include "Events/Events.h"
#include "Utils/Logger.h"

MapTile::MapTile(): m_walkable(true)
{
}


Map::Map(TextureManager* textures, EventDispatcher* dispatcher) :
	m_mapHeight(0), m_mapWidth(0),
	m_tileHeight(0), m_tileWidth(0),
	m_textureManager(textures),
	m_EventDispatcher(dispatcher)
{
	m_EventDispatcher->subscribe(typeName<TestEvent>(), this);
}

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

void Map::loadLevel(LevelNames name)
{
	std::ifstream mapFile;
	std::string levelFileName;
	switch (name)
	{
	case LevelNames::dungeon:
		levelFileName = "map.txt";
		break;
	}
	mapFile.open(levelFileName);
	if (!mapFile.is_open())
	{
		Logger::instance().log("ERROR: Level file " + levelFileName + " failed to load!");
		return;
	}
	std::stringstream s_stream;

	s_stream << mapFile.rdbuf();

	std::string tag;
	s_stream >> tag;
	if (tag == "mapSize")
	{
		s_stream >> m_mapWidth >> m_mapHeight;
	}
	else
	{
		Logger::instance().log("ERROR: missing tag mapSize in level map file. Level size is set to Zero");
	}
	s_stream >> tag;
	if (tag == "tileSize")
	{
		s_stream >> m_tileWidth >> m_tileHeight;
	}
	else
	{
		Logger::instance().log("ERROR: missing tag tileSize in level map file. Tile size is set to Zero");
	}
	s_stream >> tag;
	if (tag == "mapTiles")
	{
		int tileId;
		MapTile tile;
		for (int i = 0; i < m_mapWidth * m_mapHeight; i++)
		{
			s_stream >> tileId;
			switch (tileId)
			{
			case 0:
				tile.sprite().setTexture(m_textureManager->get(TextureId::wall()));
				tile.setWalkability(false);
				m_mapTiles.push_back(tile);
				break;
			case 1:
				tile.sprite().setTexture(m_textureManager->get(TextureId::floor1()));
				tile.setWalkability(true);
				m_mapTiles.push_back(tile);
				break;
			case 2:
				tile.sprite().setTexture(m_textureManager->get(TextureId::floor2()));
				tile.setWalkability(true);
				m_mapTiles.push_back(tile);
				break;
			}
		}
	}
	else
	{
		Logger::instance().log("ERROR: missing tag mapTiles in level map file. Level not loaded");

	}
	s_stream >> tag;
	if (tag == "playerSpawnPosition")
	{
		s_stream >> m_playerSpawnPosition.x >> m_playerSpawnPosition.y;
	}
	s_stream >> tag;
	if (tag == "enemySpawnPosition")
	{
		s_stream >> m_enemySpawnPosition.x >> m_enemySpawnPosition.y;
	}
	mapFile.close();
}

bool Map::isWalkable(sf::Vector2f tile)
{
	if (isWithinMap(tile.x, tile.y))
		return m_mapTiles[tile.y * m_mapWidth + tile.x].isWalkable();
	else
		return false;
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

std::stack<sf::Vector2f> Map::calculatePath(int start, int end)
{
	auto heuristic = [&](int start, int end)
	{
		sf::Vector2f from = XYfromLinear(start);
		sf::Vector2f to = XYfromLinear(end);
		return sqrt(pow((from.x - to.x), 2) + pow((from.y - to.y), 2));
	};

	std::vector<int> cameFrom(m_mapWidth * m_mapHeight);
	std::map<int, int> costSoFar;

	auto compareGreater = [](const std::pair<int, int>& left, const std::pair<int, int>& right) -> bool {return left.first > right.first; };

	std::priority_queue < std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compareGreater)> front(compareGreater);

	front.emplace(0, start);
	cameFrom[start] = start;
	costSoFar[start] = 0;

	while (front.size() != 0)
	{
		std::pair<int, int> currentTile = front.top();
		front.pop();

		if (currentTile.second == end)
			break;

		for (auto next : neighbors(currentTile.second))
		{
			int newCost = costSoFar[currentTile.second] + costForTile(next);
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				costSoFar[next] = newCost;
				int priority = newCost + heuristic(next, end);
				front.emplace(priority, next);
				cameFrom[next] = currentTile.second;
			}
		}
	}
	std::stack<sf::Vector2f> result;
	result.push(windowFromMap(XYfromLinear(end)));
	int prev = cameFrom[end];
	while (cameFrom[prev] != prev)
	{
		result.push(windowFromMap(XYfromLinear(prev)));
		prev = cameFrom[prev];
	}
	result.push(windowFromMap(XYfromLinear(start)));
	return result;
}

int Map::mapFromWindow(float x, float y)
{
	return linearFromXY(x / m_tileWidth, y / m_tileHeight);
}

sf::Vector2f Map::windowFromMap(float x, float y)
{
	return sf::Vector2f(x * m_tileWidth, y * m_tileHeight);
}

sf::Vector2f Map::windowFromMap(sf::Vector2f map)
{
	return sf::Vector2f(map.x * m_tileWidth, map.y * m_tileHeight);
}

int Map::linearFromXY(int x, int y)
{
	return y * m_mapWidth + x;
}

sf::Vector2f Map::XYfromLinear(int linear)
{
	float y = linear / m_mapWidth;
	float x = linear % m_mapWidth;
	return sf::Vector2f(x, y);
}

sf::Vector2f Map::getPlayerSpawnCoordinate()
{
	return windowFromMap(m_playerSpawnPosition);
}

sf::Vector2f Map::getEnemySpawnCoordinate()
{
	return windowFromMap(m_enemySpawnPosition);

}

void Map::draw(Window* window)
{
	for (int y = 0; y < m_mapHeight; y++)
	{
		for (int x = 0; x < m_mapWidth; x++)
		{
			// TODO: remove sprite size hard code
			sf::Vector2f position(float(x * 64), float(y * 64));
			getMapTile(x, y).setPosition(position);
			window->draw(getMapTile(x, y).sprite());
		}
	}
}

void Map::notify(IEvent * event)
{
	Logger::instance().log("Map: " + event->name());
}

std::vector<int> Map::neighbors(int position)
{
	std::vector<int> result;
	sf::Vector2f pos = XYfromLinear(position);
	std::vector<sf::Vector2i> neighborPoints;

	neighborPoints.push_back(sf::Vector2i(pos.x + 1, pos.y));
	neighborPoints.push_back(sf::Vector2i(pos.x - 1, pos.y));
	neighborPoints.push_back(sf::Vector2i(pos.x, pos.y + 1));
	neighborPoints.push_back(sf::Vector2i(pos.x, pos.y - 1));

	for (auto point : neighborPoints)
	{
		if (isWithinMap(point.x, point.y) && isWalkable(point.x, point.y))
			result.push_back(linearFromXY(point.x, point.y));
	}
	return result;
}

bool Map::isWithinMap(int x, int y)
{
	if (x < 0 || x > m_mapWidth - 1 || y < 0 || y > m_mapHeight - 1)
		return false;
	else
		return true;
}

int Map::costForTile(int linearPos)
{
	return 1;
}
