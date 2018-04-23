#pragma once
#include <vector>
#include "SFML\System\Time.hpp"
#include "../../Utils/utility.h"
#include "../../Utils/Meta.h"
#include "../Entity.h"
class SystemBase
{
public:
	SystemBase(std::string name);
	virtual ~SystemBase();
	virtual void update(sf::Time deltaTime) = 0;
	bool checkRequirements(const StringList& requirements);
	void addEntity(EntityId entity);
	bool haseEntity(EntityId entity);
	void removeEntity(EntityId entity);
	std::string& name();

protected:
	std::vector<EntityId>  m_entities;

private:
	std::string m_name;
	StringList m_requirements;

};

