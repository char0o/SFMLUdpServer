#include "ConnectPacket.h"

ConnectPacket::ConnectPacket()
{
	packet = new sf::Packet();
	*packet << static_cast<int>(PacketType::Connect);
}
ConnectPacket::ConnectPacket(int id)
{
	packet = new sf::Packet();
	*packet << static_cast<int>(PacketType::Connect) << id;
}
ConnectPacket::~ConnectPacket()
{
	delete packet;
}
sf::Packet* ConnectPacket::GetPacket()
{
	return packet;
}
