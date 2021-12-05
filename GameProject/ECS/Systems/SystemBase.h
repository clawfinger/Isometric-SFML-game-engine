#pragma once
#include <vector>
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Utils/Utility.h"
#include "Utils/Meta.h"
#include "ECS/Entity.h"
#include "DiContainer/DiContainer.h"

class SystemBase
{
public:
	SystemBase(std::string name);
	virtual ~SystemBase();
	virtual void update(sf::Time deltaTime) = 0;
	bool fitsRequirements(const StringList& components);
	void addEntity(EntityId entity);
	bool haseEntity(EntityId entity);
	void removeEntity(EntityId entity);
	std::string& name();

protected:
	std::vector<EntityId>  m_entities;
	StringList m_requirements;

private:
	std::string m_name;

};

