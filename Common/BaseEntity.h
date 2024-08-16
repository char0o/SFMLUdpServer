#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;
class BaseEntity
{
public:
	BaseEntity();
	~BaseEntity();
	int GetId() const;
	void SetId(int id);
	virtual void SetPosition(Vector2f& pos);
	virtual Vector2f GetPosition() const;
	virtual void Draw(RenderWindow& window) = 0;
	void SetDirection(Vector2f& dir);
	virtual void Update(Time dt) = 0;
	virtual void Update(Time dt, const RenderWindow& window) = 0;
	virtual void SetColor(const Color& color);
	Color GetColor() const;
protected:
	int id;
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	Vector2f direction;
	Color color;
	float maxSpeed;
};

