#pragma once
#include "SFML/Network.hpp"
#include "PacketType.h"
class ConnectPacket
{
public:
	ConnectPacket();
	ConnectPacket(int id);
	~ConnectPacket();
	sf::Packet* GetPacket();
private:
	sf::Packet* packet;
};

