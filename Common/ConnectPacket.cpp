#include "ConnectPacket.h"

ConnectPacket::ConnectPacket()
{
	packet = new sf::Packet();
	*packet << static_cast<int>(PacketType::Connect);
}
ConnectPacket::~ConnectPacket()
{
	delete packet;
}
sf::Packet* ConnectPacket::GetPacket()
{
	return packet;
}
