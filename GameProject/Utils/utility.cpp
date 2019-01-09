#include "utility.h"
#include <algorithm>

StringList::StringList()
{
}

bool StringList::contains(const std::string & string) const
{
	return (std::find_if(m_strings.begin(), m_strings.end(),
		[&](const std::string& original){return string == original;}) != m_strings.end());
}

StringList & StringList::operator<<(const std::string & string)
{
	m_strings.push_back(string);
	return *this;
}

std::vector<std::string>::iterator StringList::begin()
{
	return m_strings.begin();
}

std::vector<std::string>::iterator StringList::end()
{
	return m_strings.end();
}

std::vector<std::string>::const_iterator StringList::begin() const
{
	return m_strings.begin();
}

std::vector<std::string>::const_iterator StringList::end() const
{
	return m_strings.end();
}

bool Vector::isVectorsIntersects(Vector2f a, Vector2f b, Vector2f c, Vector2f d)
{
	auto isProjectionsIntersects = [](float a, float b, float c, float d)->bool
	{
		if (a > b)
			std::swap(a, b);
		if (c > d)
			std::swap(c, d);
		return std::max(a, c) <= std::min(b, d);
	};
	auto orientedArea = [](Vector2f a, Vector2f b, Vector2f c)->int
	{
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	};

	return isProjectionsIntersects(a.x, b.x, c.x, d.x) &&
		isProjectionsIntersects(a.y, b.y, c.y, d.y) &&
		orientedArea(a, b, c) * orientedArea(a, b, d) < 0 &&
		orientedArea(c, d, b) * orientedArea(c, d, a) < 0;

}