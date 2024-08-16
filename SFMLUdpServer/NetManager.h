#pragma once
#include <iostream>
void SendEntities(sf::UdpSocket& socket, const EntityList& entities, const ClientList& clients)
{
	clients.SendEntities(socket, entities);
}
void Listen(sf::UdpSocket& socket, EntityList& entityList, ClientList& clientList)
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
				int id = clientList.GetAvailableId();
				Client* client = new Client(id, sender, port);
				clientList.AddClient(client);
				socket.send(*ConnectPacket(id).GetPacket(), sender, port);
			}
			break;
		case PacketType::Disconnect:
			clientList.RemoveClient(clientList.GetClientByIp(sender, port));
			std::cout << sender << " disconnected." << std::endl;
			break;
		}
	}
}