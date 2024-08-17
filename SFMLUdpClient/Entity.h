#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "BaseEntity.h"
using namespace sf;
class Entity : public BaseEntity
{
	public:
	Entity();
	~Entity();
	void Update(Time dt) override {};
	void Update(Time dt, const RenderWindow& window) override;
	void Draw(RenderWindow& window) override;
	void SetPosition(Vector2f& pos);
	void SetColor(const Color& color) override;
	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;
private:
	RectangleShape* shape;
};

