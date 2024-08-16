#pragma once

#include "SFML/Network.hpp"
#include "Packets.hpp"
#include "Entity.h"
#include "EntityList.h"
#include <iostream>

void Listen(sf::UdpSocket& socket);
void SendEntities(sf::UdpSocket& socket, const EntityList& entities);

void SendEntities(sf::UdpSocket& socket, const EntityList& entities)
{
	for (int i = 0; i < entities.GetSize(); i++)
	{
		Entity* entity = dynamic_cast<Entity*>(entities.GetEntity(i));
		EntityListPacket entityListPacket(entities);
		
		socket.send(*entityListPacket.GetPacket(), entity->GetIp(), 2001);
	}
}
void Listen(sf::UdpSocket& socket, EntityList& entityList)
{
	sf::IpAddress sender;
	unsigned short port;
	sf::Packet packet;
	if (socket.receive(packet, sender, port) != sf::Socket::Done)
	{
		return;
	}
	int packetType = 0;
	if (packet >> packetType)
	{
		switch (packetType)
		{
		case PacketType::Connect:
			std::cout << sender << " connected." << std::endl;
			{
				Entity* entity = new Entity();
				entity->SetId(0);
				entity->SetIp(sender);
				entityList.AddEntity(entity);
				socket.send(*ConnectPacket(0).GetPacket(), sender, 2001);
			}
			break;
		case PacketType::Disconnect:
			std::cout << sender << " disconnected." << std::endl;
			break;
		}
	}
}