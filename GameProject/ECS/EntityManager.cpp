#include "stdafx.h"
#include "../Utils/Logger.h"
#include "../Utils/Utility.h"
#include "../TextureManager.h"
#include "EntityContainer.h"
#include "../Events/EventDispatcher.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Components/PositionComponent.h"
#include "Entity.h"
#include "EntityManager.h"
#include <sstream>
#include <fstream>

EntityManager::EntityManager(std::shared_ptr<EntityContainer> entityContainer,
	std::shared_ptr<EventDispatcher> eventDispatcher,
	std::shared_ptr<TextureManager> textureManager):
	m_entityContainer(entityContainer),
	m_eventDispatcher(eventDispatcher),
	m_textureManager(textureManager)
{
	loadEntityTypes();
}


EntityManager::~EntityManager()
{
}

void EntityManager::loadCharacters()
{
	std::ifstream charFile;
	std::string filename = "Characters.txt";

	charFile.open(filename);
	if (!charFile.is_open())
	{
		Logger::instance().log("ERROR: Characters file " + filename + " failed to load!");
		return;
	}

	std::string line;
	EntityId entity = m_entityContainer->createEntity(m_entityTypes[EntityType::player]);

	while (std::getline(charFile, line)) {
		std::stringstream s_stream(line);
		std::string type;
		s_stream >> type;
		if (type == "Name") {
			std::string name;
			s_stream >> name;
			Logger::instance().log("Loaded: " + name);
		}
		else if (type == "Component")
		{
			std::string comp;
			s_stream >> comp;
			if (comp == "SpriteComponent")
			{
				SpriteComponent* spriteComp = m_entityContainer->getComponent<SpriteComponent>(entity, comp);
				if (spriteComp)
				{
					s_stream >> comp;
					spriteComp->create(m_textureManager->get(comp));
				}
			}
			else
			{
				ComponentBase* component = m_entityContainer->getComponent<ComponentBase>(entity, comp);
				component->readData(s_stream);
			}

		}
	}
	charFile.close();
}

void EntityManager::loadEntityTypes()
{
	std::ifstream charFile;
	std::string filename = "EntityTypes.txt";

	charFile.open(filename);
	if (!charFile.is_open())
	{
		Logger::instance().log("ERROR: Level file " + filename + " failed to load!");
		return;
	}

	std::string line;
	StringList componentsList;

	while (std::getline(charFile, line))
	{
		std::stringstream s_stream(line);
		std::string type;
		s_stream >> type;
		std::string comp;
		while (s_stream >> comp)
			componentsList << comp;
		m_entityTypes.insert(std::make_pair(type, std::move(componentsList)));
	}
	charFile.close();
}
