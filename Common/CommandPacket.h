#pragma once
#include <SFML/Network.hpp>
#include "PacketType.h"
#include <string>
#include "NetCommand.h"
class CommandPacket
{
public:
	CommandPacket();
	CommandPacket(NetCommand& command);
	CommandPacket(int tick, std::string command);
	~CommandPacket();
	sf::Packet* GetPacket();
private:
	sf::Packet* packet;
};

