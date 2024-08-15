#include "Entity.h"

Entity::Entity()
{
	position = Vector2f(0, 0);
	velocity = Vector2f(0, 0);
	acceleration = Vector2f(0, 0);
	direction = Vector2f(1, 1);
	maxSpeed = 250.0f;
}

Entity::~Entity()
{

}
Vector2f Entity::GetPosition() const
{
	return position;
}
void Entity::Update(Time dt)
{
	float deltaTime = dt.asSeconds();
	if (position.x > 800 - 50)
	{
		position.x = 800 - 50;
		direction.x = -1;
	}
	if (position.x < 0)
	{
		position.x = 0;
		direction.x = 1;
	}
	if (position.y > 600 - 50)
	{
		position.y = 600 - 50;
		direction.y = -1;
	}
	if (position.y < 0)
	{
		position.y = 0;
		direction.y = 1;
	}
	velocity += direction * 1000.0f * deltaTime;
	float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (speed > maxSpeed)
	{
		velocity *= maxSpeed / speed;
	}
	position += velocity * deltaTime;
}