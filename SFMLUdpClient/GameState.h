#pragma once
#include <SFML/Network.hpp>
#include "Entity.h"
#include "EntityList.h"
#include "Packets.hpp"
class GameState
{
public:
	GameState();
	GameState(EntityList* entityList);
	GameState(EntityList* entityList, sf::Packet& packet, int ticks, int localPlayer);
	~GameState();
	void Update(float dt, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void Color(const sf::Color& color);
	EntityList* GetEntityList() { return entityList; }
	int GetTicks() const { return ticks; }
private:
	EntityList* entityList;
	int ticks;
	int localPlayer;
};

