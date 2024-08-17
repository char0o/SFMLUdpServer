#pragma once
#include "Entity.h"
class EntityList
{
public:
	EntityList();
	~EntityList();
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	int GetSize() const;
	Entity* GetEntity(int index) const;
	Entity* GetEntityById(int id) const;
	Entity* GetEntityByIp(sf::IpAddress ip, unsigned short port) const;
	void Update(sf::Time dt);
private:
	std::vector<Entity*> entities;
};


