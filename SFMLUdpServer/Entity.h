#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "BaseEntity.h"
#include "Client.h"
using namespace sf;
class Entity : public BaseEntity
{
public:
	Entity();
	Entity(Client* client);
	~Entity();
	void Update(Time dt) override;
	void Update(Time dt, const RenderWindow& window) override {};
	Vector2f GetPosition() const;
	void Draw(RenderWindow& window) override {};
	//void SetColor(const Color& color) override {};
	Client* GetClient() const;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
private:
	Client* client;
};

