#pragma once
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "PacketType.h"

#ifdef PLAYER_PACKET_EXPORTS
#define PLAYER_PACKET_API __declspec(dllexport)
#else
#define PLAYER_PACKET_API __declspec(dllimport)
#endif

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

