#pragma once
#include "SFML/Network.hpp"
#include "EntityList.h"
#include "PacketType.h"

class EntityListPacket
{
public:
	EntityListPacket();
	EntityListPacket(const EntityList& entityList, int ticks);
	~EntityListPacket();
	sf::Packet* GetPacket();
private:
	sf::Packet* packet;
};
