#include "Entity.h"

Entity::Entity() : BaseEntity()
{

}

Entity::Entity(Client* client) : BaseEntity()
{
	this->client = client;
	this->id = client->GetId();
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
		direction.y = -1.0f;
	}
	if (moveDown)
	{
		direction.y = 1.0f;
	}
	if (!moveUp && !moveDown)
	{
		direction.y = 0.0f;
	}
	if (moveLeft)
	{
		direction.x = -1.0f;
	}
	if (moveRight)
	{
		direction.x = 1.0f;
	}
	if (!moveLeft && !moveRight)
	{
		direction.x = 0.0f;
	}
	velocity += direction * 2500.0f * deltaTime;
	float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (speed > maxSpeed)
	{
		velocity *= maxSpeed / speed;
	}

	velocity *= 0.95f;

	position += velocity * deltaTime;

	velocity *= 1.0f / (1.0f + 10.0f * deltaTime);
}

Client* Entity::GetClient() const
{
	return client;
}
