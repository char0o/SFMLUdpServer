#pragma once
#include <vector>
#include "BaseEntity.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
class EntityList
{
public:
	EntityList();
	~EntityList();
	void AddEntity(BaseEntity* entity);
	void RemoveEntity(BaseEntity* entity);
	int GetSize() const;
	BaseEntity* GetEntity(int index) const;
	BaseEntity* GetEntityById(int id) const;
	void Draw(sf::RenderWindow& window);
	void Update(sf::Time dt);
	void Color(const sf::Color& color);
private:
	std::vector<BaseEntity*> entities;
};

