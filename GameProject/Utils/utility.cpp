#include "stdafx.h"
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
