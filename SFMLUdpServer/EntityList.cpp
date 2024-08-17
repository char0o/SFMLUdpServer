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
	if (index > entities.size() - 1)
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

void EntityList::Update(sf::Time dt)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(dt);
	}
}

Entity* EntityList::GetEntityByIp(sf::IpAddress ip, unsigned short port) const
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->GetClient() != nullptr)
		{
			if (entities[i]->GetClient()->GetIp() == ip && entities[i]->GetClient()->GetPort() == port)
			{
				return entities[i];
			}
		 }
	}
	return nullptr;
}