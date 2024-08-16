#pragma once
#include "SFML/Network.hpp"
#include "Packets.hpp"
#include <iostream>
void SendConnectPacket(sf::UdpSocket& socket);
void SendDisconnectPacket(sf::UdpSocket& socket);
void Listen(sf::UdpSocket& socket, EntityList& entityList);

void SendConnectPacket(sf::UdpSocket& socket)
{
	ConnectPacket connectPacket;
	socket.send(*connectPacket.GetPacket(), "localhost", 2000);
}

void SendDisconnectPacket(sf::UdpSocket& socket)
{
	DisconnectPacket disconnectPacket;
	socket.send(*disconnectPacket.GetPacket(), "localhost", 2000);
}

void Listen(sf::UdpSocket& socket, EntityList& entityList)
{

	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;
	sf::Vector2f position;
	if (socket.receive(packet, sender, port) != sf::Socket::Done)
	{
		return;
	}

	int packetType = 0;
	if (!(packet >> packetType))
	{
		std::cout << "No packet type" << std::endl;
	}
	switch (packetType)
	{
		int id;
	case PacketType::Entities:
		int size;
		packet >> size;
		for (int i = 0; i < size; i++)
		{
			packet >> id;
			if (id == -1)
				continue;
			Vector2f position;
			if (entityList.GetEntityById(id) == nullptr)
			{
				Entity* entity = new Entity();
				entity->SetId(id);				
				packet >> position.x >> position.y;
				entity->SetPosition(position);
				entityList.AddEntity(entity);
			}
			else
			{
				packet >> position.x >> position.y;
				entityList.GetEntity(id)->SetPosition(position);
			}
		}
		break;
	case PacketType::Connect:
		packet >> id;
		std::cout << id;
		break;
	}
}
