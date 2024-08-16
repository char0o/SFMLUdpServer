#include "Entity.h"

Entity::Entity() : BaseEntity()
{
	shape = new RectangleShape(Vector2f(50, 50));
	shape->setPosition(position);
	shape->setFillColor(Color::Red);
}
Entity::~Entity()
{
	delete shape;
}
void Entity::SetColor(const Color& color)
{
	BaseEntity::SetColor(color);
	shape->setFillColor(color);
}
void Entity::Update(Time dt, const RenderWindow& window)
{
	float deltaTime = dt.asSeconds();
	std::cout << deltaTime << std::endl;
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
	shape->setPosition(position);
	//float deltaTime = dt.asSeconds();

	//Vector2f direction;
	//if (Keyboard::isKeyPressed(Keyboard::W))
	//{
	//	direction.y = -1;
	//}
	//if (Keyboard::isKeyPressed(Keyboard::S))
	//{
	//	direction.y = 1;
	//}
	//if (Keyboard::isKeyPressed(Keyboard::A))
	//{
	//	direction.x = -1;
	//}
	//if (Keyboard::isKeyPressed(Keyboard::D))
	//{
	//	direction.x = 1;
	//}

	//if (direction.x != 0 || direction.y != 0)
	//{
	//	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	//	direction.x /= length;
	//}

	//velocity += direction * 1000.0f * deltaTime;

	//float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	//if (speed > maxSpeed)
	//{
	//	velocity *= maxSpeed / speed;
	//}

	//position += velocity * deltaTime;

	//velocity *= 1.0f / (1.0f + 10.0f * deltaTime);
	//shape->setPosition(position);
}
void Entity::Draw(RenderWindow& window)
{
	window.draw(*shape);
}
void Entity::SetPosition(Vector2f& pos)
{
	position = pos;
	shape->setPosition(position);
}