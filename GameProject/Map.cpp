#include "Map.h"
#include "Window.h"
#include <fstream>
#include <queue>
#include <sstream>
#include <memory>
#include "Events/Events.h"
#include "Utils/Logger.h"
#include "Utils/Utility.h"

MapTile::MapTile(): m_walkable(true), m_empty(false)
{
}

Map::Map(std::shared_ptr<TextureManager> textures, std::shared_ptr<EventDispatcher> dispatcher) :
	m_mapHeight(0), m_mapWidth(0),
	m_tileHeight(0), m_tileWidth(0),
	m_textureManager(textures),
	m_EventDispatcher(dispatcher)
{
	initMatrix();
}

MapTile::MapTile(sf::Texture& texture): m_walkable(true), m_empty(false), m_transparent(true)
{
	m_sprite.setTexture(texture);
}

bool MapTile::isWalkable()
{
	return m_walkable;
}

bool MapTile::isEmpty()
{
	return m_empty;
}

bool MapTile::isTransparent()
{
	return m_transparent;
}

void MapTile::setWalkability(bool walkable)
{
	m_walkable = walkable;
}

void MapTile::setEmpty(bool empty)
{
	m_empty = empty;
}

void MapTile::setTransparent(bool transparent)
{
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

void Map::loadLevel(LevelTypes name)
{
	std::ifstream mapFile;
	std::string levelFileName;
	switch (name)
	{
	case LevelTypes::dungeon:
		levelFileName = "map.txt";
		break;
	}
	mapFile.open(levelFileName);
	if (!mapFile.is_open())
	{
		LOG("ERROR: Level file " + levelFileName + " failed to load!");
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
		LOG("ERROR: missing tag mapSize in level map file. Level size is set to Zero");
	}
	s_stream >> tag;
	if (tag == "tileSize")
	{
		s_stream >> m_tileWidth >> m_tileHeight;
	}
	else
	{
		LOG("ERROR: missing tag tileSize in level map file. Tile size is set to Zero");
	}
	s_stream >> tag;
	if (tag == "mapTiles")
	{
		for (int i = 0; i < m_mapHeight; i++)
		{
			std::string mapLine;
			s_stream >> mapLine;
			std::string floorTileTags = "ABCDEF";
			if (mapLine.size() < size_t(m_mapWidth))
			{
				for (size_t i = 0; i < size_t(m_mapWidth - mapLine.size()); i++)
				{
					mapLine.push_back('0');
				}
			}
			for (int i = 0; i < m_mapWidth; i++)
			{
				MapTile tile;
				int index = 0;
				switch (mapLine[i])
				{
				case '0':
					tile.setWalkability(false);
					tile.setEmpty(true);
					tile.setTransparent(true);
					break;
				case 'A':
					tile.setWalkability(true);
					index = getRandomInRange<int>(0, floorTileTags.size() - 1);
					tile.sprite().setTexture(m_textureManager->get(std::string("A")));
					tile.setTransparent(true);
					break;
				default:
					tile.sprite().setTexture(m_textureManager->get(std::string(mapLine.begin() + i, mapLine.begin() + i + 1)));
					tile.setWalkability(false);
					tile.setTransparent(false);
					break;
				}
				m_mapTiles.push_back(tile);
			}
		}
	}
	else
	{
		LOG("ERROR: missing tag mapTiles in level map file. Level not loaded");

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
	m_EventDispatcher->dispatch(new MapCreatedEvent(name));
}

bool Map::isWalkable(const sf::Vector2f& tile)
{
	if (isWithinMap(int(tile.x), int(tile.y)))
		return m_mapTiles[int(tile.y) * m_mapWidth + int(tile.x)].isWalkable();
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

std::stack<sf::Vector2f> Map::calculatePath(const sf::Vector2f& from, const sf::Vector2f& to)
{
	int start = linearFromXY(from.x, from.y);
	int end = linearFromXY(to.x, to.y);

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

sf::Vector2f Map::windowFromMap(float x, float y)
{
	return sf::Vector2f(x * m_tileWidth, y * m_tileHeight);
}

sf::Vector2f Map::windowFromMap(const sf::Vector2f& map)
{
	return sf::Vector2f(map.x * m_tileWidth, map.y * m_tileHeight);
}

int Map::linearFromXY(int x, int y)
{
	return y * m_mapWidth + x;
}

sf::Vector2f Map::XYfromLinear(int linear)
{
	float y = float(linear / m_mapWidth);
	float x = float(linear % m_mapWidth);
	return sf::Vector2f(x, y);
}

sf::Vector2i Map::XYfromWindow(sf::Vector2f& windowCoords)
{
	return sf::Vector2i(int(windowCoords.x / m_tileWidth), int(windowCoords.y / m_tileHeight));
}

sf::Vector2f Map::getPlayerSpawnCoordinate()
{
	return windowFromMap(m_playerSpawnPosition);
}

sf::Vector2f Map::getEnemySpawnCoordinate()
{
	return windowFromMap(m_enemySpawnPosition);

}

int Map::manhattanLength(int from, int to)
{
	sf::Vector2f fromCoord = XYfromLinear(from);
	sf::Vector2f toCoord = XYfromLinear(to);
	return abs(fromCoord.x - toCoord.x) + abs(fromCoord.y - toCoord.y);
}

void Map::draw(std::shared_ptr<Window> window)
{
	//sf::Vector2f viewTopLeft = window->getView().getCenter() - (window->getView().getSize() / 2.0f);
	//sf::Vector2f viewDownRight = window->getView().getCenter() + (window->getView().getSize() / 2.0f);

	//int startX = int(viewTopLeft.x) / m_tileWidth - 1;
	//int endX = int(viewDownRight.x) / m_tileWidth + 2;

	//int startY = int(viewTopLeft.y) / m_tileHeight - 1;
	//int endY = int(viewDownRight.y) / m_tileHeight + 2;

	//if (startX < 0 || startX > m_mapWidth)
	//	startX = 0;
	//if (startY < 0 || startY > m_mapHeight)
	//	startY = 0;

	//if (endX > m_mapWidth)
	//	endX = m_mapWidth;
	//if (endY > m_mapHeight)
	//	endY = m_mapHeight;

	//for (int y = startY; y < endY; y++)
	//{
	//	for (int x = startX; x < endX; x++)
	//	{
	//		MapTile& current = getMapTile(x, y);
	//		sf::Vector2f position(float(x * m_tileWidth), float(y * m_tileHeight));
	//		current.setPosition(position);
	//		if(!current.isEmpty())
	//			window->draw(getMapTile(x, y).sprite());
	//	}
	//}

	for (int i = 0; i < m_mapWidth; i++)
	{
		for (int j = 0; j < m_mapHeight; j++)
		{
			MapTile& current = getMapTile(i, j);
			float screenX = (i - j) * 0.5 * m_tileWidth;
			float screenY = (i + j) * 0.5 * 0.57735 * m_tileHeight;
			sf::Vector2f position(screenX, screenY);
			current.setPosition(position);
			if(!current.isEmpty())
				window->draw(getMapTile(i, j).sprite());
		}
	}
}


std::vector<int> Map::neighbors(int position)
{
	std::vector<int> result;
	sf::Vector2f pos = XYfromLinear(position);
	std::vector<sf::Vector2i> neighborPoints;

	neighborPoints.push_back(sf::Vector2i(int(pos.x + 1), int(pos.y)));
	neighborPoints.push_back(sf::Vector2i(int(pos.x - 1), int(pos.y)));
	neighborPoints.push_back(sf::Vector2i(int(pos.x), int(pos.y + 1)));
	neighborPoints.push_back(sf::Vector2i(int(pos.x), int(pos.y - 1)));

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

void Map::initMatrix()
{
	m_matrix.translate(64, 0);
	m_matrix.scale(sqrt(2.0) / 2.0, sqrt(2.0) / (2 / 0.57735));
	m_matrix.rotate(45);
}

sf::Vector2i Map::orthoXYfromIsometricCoords(sf::Vector2f& windowCoords)
{
	sf::Vector2f orthCoord = m_matrix.getInverse().transformPoint(windowCoords.x, windowCoords.y);
	return sf::Vector2i(floor(orthCoord.x / m_tileWidth), floor(orthCoord.y / m_tileHeight));
}
