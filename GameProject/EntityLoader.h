#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ECS/Entity.h"
#include "Utils/Meta.h"
#include "ECS/EntityContainer.h"
#include "TextureManager.h"


class EntityLoader
{
public:
	EntityLoader(std::shared_ptr<EntityContainer> manager, std::shared_ptr<TextureManager> textureManager);
	~EntityLoader();
	EntityId load(std::string filename);
private:
	std::shared_ptr<EntityContainer> m_EntityManager;
	std::shared_ptr<TextureManager> m_TextureManager;
};
REGISTER_TYPENAME(EntityLoader)
