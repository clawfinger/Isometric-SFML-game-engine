#include "stdafx.h"
#include "EntityLoader.h"
#include "Utils/Logger.h"
#include "Utils/utility.h"
#include "ECS/Components/SpriteComponent.h"
#include <fstream>
#include <sstream>

EntityLoader::EntityLoader(std::shared_ptr<EntityManager> manager,
	std::shared_ptr<TextureManager> textureManager): m_EntityManager(manager), m_TextureManager(textureManager)
{
}

EntityLoader::~EntityLoader()
{
}

std::vector<EntityId>& EntityLoader::getCharacters()
{
	return m_charsIds;
}

void EntityLoader::load(std::string filename)
{
	std::ifstream charFile;

	charFile.open(filename);
	if (!charFile.is_open())
	{
		Logger::instance().log("ERROR: Level file " + filename + " failed to load!");
		return;
	}
	std::stringstream s_stream;

	s_stream << charFile.rdbuf();
	std::string tag;
	s_stream >> tag;
	StringList componentsList;
	if (tag == "components")
	{
		s_stream >> tag;
		while (tag != "#components")
		{
			componentsList << tag;
			s_stream >> tag;
		}
	}
	else
	{
		Logger::instance().log("ERROR: missing tag components in character file");
		return;
	}
	EntityId entity = m_EntityManager->createEntity(componentsList);
	s_stream >> tag;
	ComponentBase* component = m_EntityManager->getComponent<ComponentBase>(entity, tag);
	if (component->name() == "SpriteComponent")
	{
		SpriteComponent* spriteComp = dynamic_cast<SpriteComponent*>(component);
		if (spriteComp)
		{
			s_stream >> tag;
			spriteComp->create(m_TextureManager->get(tag));
		}
	}
	m_charsIds.push_back(entity);
}
