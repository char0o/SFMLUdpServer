#pragma once
#include "SFML/Network.hpp"
#include "PacketType.h"
class DisconnectPacket
{
public:
	DisconnectPacket();
	~DisconnectPacket();
	sf::Packet* GetPacket();
private:
	sf::Packet* packet;
};

