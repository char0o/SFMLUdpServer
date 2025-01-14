#pragma once
#include <vector>
#include "Entity.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
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
	void Draw(sf::RenderWindow& window, int localPlayer);
	void Update(sf::Time dt);
	void Update(sf::Time dt, sf::RenderWindow& window);
	void Color(const sf::Color& color);
private:
	std::vector<Entity*> entities;
};



