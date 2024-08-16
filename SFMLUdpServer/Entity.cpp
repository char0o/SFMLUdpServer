#include "Entity.h"

Entity::Entity() : BaseEntity()
{

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
		position.x = 800 - 51;
		direction.x = -1;
	}
	if (position.x < 0)
	{
		position.x = 1;
		direction.x = 1;
	}
	if (position.y > 600 - 50)
	{
		position.y = 600 - 51;
		direction.y = -1;
	}
	if (position.y < 0)
	{
		position.y = 1;
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
