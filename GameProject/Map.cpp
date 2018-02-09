#include "stdafx.h"
#include "Map.h"
#include <fstream>
#include <queue>

MapTile::MapTile(): m_walkable(true)
{
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
		MapTile tile;
		while (character != '\n')
		{
			int tileId = std::stoi(&character);
			switch (tileId)
			{
			case 0:
				m_mapTiles.push_back(MapTile(textures.get(TextureId::floor0)));
				break;
			case 1:
				tile.sprite().setTexture(textures.get(TextureId::floor1));
				tile.setWalkability(false);
				m_mapTiles.push_back(tile);
				break;
			case 2:
				tile.sprite().setTexture(textures.get(TextureId::floor2));
				tile.setWalkability(false);
				m_mapTiles.push_back(tile);
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

bool Map::isWalkable(sf::Vector2i tile)
{
	return m_mapTiles[tile.y * m_mapWidth + tile.x].isWalkable();
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

void Map::aStarTest(int start, int end)
{
	auto heuristic = [&](int start, int end)
	{
		sf::Vector2i from = XYfromLinear(start);
		sf::Vector2i to = XYfromLinear(end);
		return sqrt(pow((from.x - to.x), 2) + pow((from.y - to.y), 2));
	};

	std::vector<int> cameFrom(m_mapWidth * m_mapHeight);
	//std::vector<int> costSoFar(m_mapWidth * m_mapHeight);
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
	std::vector<int> result;
	result.push_back(end);
	int prev = cameFrom[end];
	while (cameFrom[prev] != prev)
	{
		result.push_back(prev);
		prev = cameFrom[prev];
	}
	result.push_back(start);
	for (auto x : result)
	{
		std::cout << x << " ";
	}
	std::cout << "ok";
}

int Map::mapFromMouse(int x, int y)
{
	return linearFromXY(x / m_tileWidth, y / m_tileHeight);
}

int Map::linearFromXY(int x, int y)
{
	return y * m_mapWidth + x;
}

sf::Vector2i Map::XYfromLinear(int linear)
{
	int y = linear / m_mapWidth;
	int x = linear % m_mapWidth;
	return sf::Vector2i(x, y);
}

std::vector<int> Map::neighbors(int position)
{
	std::vector<int> result;
	sf::Vector2i pos = XYfromLinear(position);
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
