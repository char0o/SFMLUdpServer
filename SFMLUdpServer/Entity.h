#pragma once
#include "SFML/System.hpp"
using namespace sf;
class Entity
{
public:
	Entity();
	~Entity();
	void Update(Time dt);
	Vector2f GetPosition() const;
private:
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	Vector2f direction;
	float maxSpeed;
};

