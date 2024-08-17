#include "GameState.h"
#include <iostream>
GameState::GameState()
{
	this->entityList = nullptr;
	this->ticks = 0;
}

GameState::GameState(EntityList* entityList)
{
	this->entityList = entityList;
	this->ticks = ticks;
}

GameState::GameState(EntityList* entityList, sf::Packet& packet, int ticks)
{
	this->entityList = entityList;
	int id;
	int size;
	this->ticks = ticks;
	packet >> size;
	for (int i = 0; i < size; i++)
	{
		packet >> id;
		if (id == -1)
			continue;
		Vector2f position;
		if (entityList->GetEntityById(id) == nullptr)
		{
			Entity* entity = new Entity();
			entity->SetId(id);
			packet >> position.x >> position.y;
			std::cout << "Position: " << position.x << " " << position.y << std::endl;
			entity->SetPosition(position);
			entityList->AddEntity(entity);
		}
		else
		{
			packet >> position.x >> position.y;
			entityList->GetEntityById(id)->SetPosition(position);
		}
	}
}

GameState::~GameState()
{
}
void GameState::Color(const sf::Color& color)
{
	if (entityList == nullptr)
		return;
	entityList->Color(color);
}

void GameState::Update(float dt)
{
}

void GameState::Draw(sf::RenderWindow& window)
{
	if (entityList == nullptr)
		return;
	entityList->Draw(window);
}
