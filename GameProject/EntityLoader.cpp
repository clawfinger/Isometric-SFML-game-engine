#include "stdafx.h"
#include "EntityLoader.h"
#include "Utils/Logger.h"
#include "Utils/utility.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/PositionComponent.h"
#include <fstream>
#include <sstream>

EntityLoader::EntityLoader(std::shared_ptr<EntityContainer> manager,
	std::shared_ptr<TextureManager> textureManager): m_EntityManager(manager), m_TextureManager(textureManager)
{
}

EntityLoader::~EntityLoader()
{
}

EntityId EntityLoader::load(std::string filename)
{
	std::ifstream charFile;

	charFile.open(filename);
	if (!charFile.is_open())
	{
		Logger::instance().log("ERROR: Level file " + filename + " failed to load!");
		return - 1;
	}

	std::string line;
	StringList componentsList;
	EntityId entity = -1;

	while (std::getline(charFile, line)) {
		std::stringstream s_stream(line);
		std::string type;
		s_stream >> type;
		if (type == "Name") {
			std::string name;
			s_stream >> name;
			std::cout << "Name: " << name << std::endl;
		}
		else if (type == "ComponentList")
		{
			std::string comp;
			while (s_stream >> comp)
				componentsList << comp;
			entity = m_EntityManager->createEntity(componentsList);

		}
		else if (type == "Component")
		{
			std::string comp;
			s_stream >> comp;
			if (comp == "SpriteComponent")
			{
				SpriteComponent* spriteComp = m_EntityManager->getComponent<SpriteComponent>(entity, comp);
				if (spriteComp)
				{
					s_stream >> comp;
					spriteComp->create(m_TextureManager->get(comp));
				}
			}
			else
			{
				ComponentBase* component = m_EntityManager->getComponent<ComponentBase>(entity, comp);
				component->readData(s_stream);
			}
			
		}
	}
	charFile.close();
	return entity;
}
