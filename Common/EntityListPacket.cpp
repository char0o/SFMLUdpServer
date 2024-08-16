#include "EntityListPacket.h"

EntityListPacket::EntityListPacket()
{
	packet = new sf::Packet();
	*packet << static_cast<int>(PacketType::Entities);
}
EntityListPacket::EntityListPacket(const EntityList& entityList)
{
	packet = new sf::Packet();
	*packet << static_cast<int>(PacketType::Entities);
	*packet << entityList.GetSize();
	for (int i = 0; i < entityList.GetSize(); i++)
	{
		BaseEntity* entity = entityList.GetEntity(i);
		if (entity == nullptr)
		{
			*packet << -1;
			continue;
		}
		*packet << entity->GetId() << entity->GetPosition().x << entity->GetPosition().y;
	}
}
EntityListPacket::~EntityListPacket()
{
	delete packet;
}
sf::Packet* EntityListPacket::GetPacket()
{
	return packet;
}
