#include "EntityList.h"

EntityList::EntityList()
{
	
}
EntityList::~EntityList()
{
	for (int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
	entities.clear();
}

void EntityList::AddEntity(BaseEntity* entity)
{
	entities.push_back(entity);
}

void EntityList::RemoveEntity(BaseEntity* entity)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i] == entity)
		{
			BaseEntity* temp = entities[i];
			entities.erase(entities.begin() + i);
			delete temp;
			break;
		}
	}
}
int EntityList::GetSize() const
{
	return entities.size();
}
BaseEntity* EntityList::GetEntity(int index) const
{
	if (index > entities.size() - 1)
	{
		return nullptr;
	}
	return entities[index];
}
BaseEntity* EntityList::GetEntityById(int id) const
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->GetId() == id)
		{
			return entities[i];
		}
	}
	return nullptr;
}
void EntityList::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Draw(window);
	}
}

void EntityList::Update(sf::Time dt)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(dt);
	}
}
