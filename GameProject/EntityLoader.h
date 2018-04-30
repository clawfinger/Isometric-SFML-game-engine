#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ECS/Entity.h"
#include "Utils/Meta.h"

class TextureManager;
class EventDispatcher;
class EntityContainer;

class EntityLoader
{
public:
	EntityLoader(std::shared_ptr<EntityContainer> manager,
		std::shared_ptr<TextureManager> textureManager,
		std::shared_ptr<EventDispatcher> eventDispatcher);
	~EntityLoader();
	EntityId load(std::string filename);
private:
	std::shared_ptr<EntityContainer> m_entityContainer;
	std::shared_ptr<TextureManager> m_TextureManager;
	std::shared_ptr<EventDispatcher> m_eventDispatcher;
};
REGISTER_TYPENAME(EntityLoader)
