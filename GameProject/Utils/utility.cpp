#include "stdafx.h"
#include "utility.h"
#include <algorithm>

StringList::StringList()
{
}

bool StringList::contains(const std::string & string)
{
	return (std::find_if(m_strings.begin(), m_strings.end(),
		[&](const std::string& original){return string == original;}) != m_strings.end());
}

StringList & StringList::operator<<(const std::string & string)
{
	m_strings.push_back(string);
	return *this;
}
