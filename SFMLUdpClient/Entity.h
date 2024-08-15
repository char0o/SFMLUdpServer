#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
using namespace sf;
class Entity
{
	public:
	Entity();
	~Entity();
	void Update(Time dt, const RenderWindow& window);
	void Draw(RenderWindow& window);
	void SetPosition(Vector2f& pos);
private:
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	Vector2f direction;
	float maxSpeed;
	RectangleShape* shape;
};

