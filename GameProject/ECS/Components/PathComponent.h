#pragma once
#include "ComponentBase.h"
#include "../../Utils/Meta.h"
#include "SFML/System/Vector2.hpp"
#include <stack>

//TODO: Implement own path stack to get rid of pathEnd parameter
class PathComponent : public ComponentBase
{
public:
	PathComponent();
	~PathComponent();
	void setPath(const std::stack<sf::Vector2f>& path, const sf::Vector2f& pathEnd);
	std::stack<sf::Vector2f>& getPath();

	sf::Vector2f& getPathEnd();
	bool isPathSet();
	void readData(std::stringstream& stream);
private:
	std::stack<sf::Vector2f> m_path;
	sf::Vector2f m_pathEnd;
};
REGISTER_TYPENAME(PathComponent)
