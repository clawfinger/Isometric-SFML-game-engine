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
	void setPath(const std::stack<Vector2f>& path, const Vector2f& pathEnd);
	std::stack<Vector2f>& getPath();

	Vector2f& getPathEnd();
	bool isPathSet();
	void readData(std::stringstream& stream);
private:
	std::stack<Vector2f> m_path;
	Vector2f m_pathEnd;
};
REGISTER_TYPENAME(PathComponent)
