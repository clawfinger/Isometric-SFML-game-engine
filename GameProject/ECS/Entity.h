#pragma once
#include "cstdint"
#include <string>

using EntityId = uint32_t;
const uint32_t INVALIDID = 4294967295;

namespace EntityType
{
	static std::string character = "Character";
	static std::string enemy = "Enemy";
}