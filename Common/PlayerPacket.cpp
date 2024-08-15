#include "PlayerPacket.h"
PlayerPacket::PlayerPacket()
{
	packet = new sf::Packet();
}
PlayerPacket::PlayerPacket(int id, sf::Vector2f position)
{
	packet = new sf::Packet();
	*packet << static_cast<int>(PacketType::Position) << id << position.x << position.y;
}
sf::Packet* PlayerPacket::GetPacket()
{
	return packet;
}
sf::Vector2f& PlayerPacket::GetPosition()
{
	sf::Vector2f position;
	if (packet->getDataSize() != 0)
	{
		*packet >> position.x >> position.y;
	}
	return position;
}
void PlayerPacket::SetPosition(const sf::Vector2f& position)
{
	*packet << position.x << position.y;
}
PlayerPacket::~PlayerPacket()
{
	delete packet;
}