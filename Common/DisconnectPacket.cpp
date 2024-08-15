#include "DisconnectPacket.h"

DisconnectPacket::DisconnectPacket()
{
	packet = new sf::Packet();
	*packet << static_cast<int>(PacketType::Disconnect);
}
DisconnectPacket::~DisconnectPacket()
{
	delete packet;
}
sf::Packet* DisconnectPacket::GetPacket()
{
	return packet;
}
