#pragma once
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "PacketType.h"



class PlayerPacket
{
	public:
	PlayerPacket();
	PlayerPacket(int id, sf::Vector2f position);
	~PlayerPacket();
	sf::Packet* GetPacket();
	sf::Vector2f& GetPosition();
	void SetPosition(const sf::Vector2f& position);
private:
	sf::Packet* packet;
};

