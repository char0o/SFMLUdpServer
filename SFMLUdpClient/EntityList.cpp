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

void EntityList::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}
void EntityList::Color(const sf::Color& color)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->SetColor(color);
	}
}
void EntityList::RemoveEntity(Entity* entity)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i] == entity)
		{
			Entity* temp = entities[i];
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
Entity* EntityList::GetEntity(int index) const
{
	if (index > entities.size() - 1 || index < 0 || entities.size() == 0)
	{
		return nullptr;
	}
	return entities[index];
}
Entity* EntityList::GetEntityById(int id) const
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
void EntityList::Draw(sf::RenderWindow& window, int localPlayer)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->GetId() == localPlayer)		
			continue;

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

void EntityList::Update(sf::Time dt, sf::RenderWindow& window)
{
	for (int i = 0; i < entities.size(); i++)
	{

		entities[i]->Update(dt, window);
	}
}
