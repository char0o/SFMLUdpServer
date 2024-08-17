#include "Entity.h"

Entity::Entity() : BaseEntity()
{

}

Entity::Entity(Client* client) : BaseEntity()
{
	this->client = client;
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
	if (moveUp)
	{
		direction = Vector2f(0.0f, -1.0f);
	}
	if (moveDown)
	{
		direction = Vector2f(0.0f, 1.0f);
	}
	if (moveLeft)
	{
		direction = Vector2f(-1.0f, 0.0f);
	}
	if (moveRight)
	{
		direction = Vector2f(1.0f, 0.0f);
	}
	velocity += direction * 1000.0f * deltaTime;
	float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (speed > maxSpeed)
	{
		velocity *= maxSpeed / speed;
	}
	position += velocity * deltaTime;
}

Client* Entity::GetClient() const
{
	return client;
}
