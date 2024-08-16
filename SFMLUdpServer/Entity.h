#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "BaseEntity.h"
using namespace sf;
class Entity : public BaseEntity
{
public:
	Entity();
	~Entity();
	void Update(Time dt) override;
	void Update(Time dt, const RenderWindow& window) override {};
	Vector2f GetPosition() const;
	void Draw(RenderWindow& window) override {};
private:
};

