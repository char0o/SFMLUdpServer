#include "BaseEntity.h"

BaseEntity::BaseEntity() : id(0)
{
	position = Vector2f(0, 0);
	velocity = Vector2f(0, 0);
	acceleration = Vector2f(0, 0);
	direction = Vector2f(1, 1);
	maxSpeed = 250.0f;
}
BaseEntity::~BaseEntity()
{

}
void BaseEntity::SetDirection(Vector2f& dir)
{
	direction = dir;
}
void BaseEntity::SetId(int id)
{
	this->id = id;
}
int BaseEntity::GetId() const
{
	return id;
}
void BaseEntity::SetPosition(Vector2f& pos)
{
	position = pos;
}
Vector2f BaseEntity::GetPosition() const
{
	return position;
}
void BaseEntity::SetColor(const Color& color)
{
	this->color = color;
}
Color BaseEntity::GetColor() const
{
	return color;
}