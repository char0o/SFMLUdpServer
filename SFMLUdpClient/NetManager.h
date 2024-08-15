#pragma once
#include "SFML/Network.hpp"
#include "Packets.hpp"
#include <iostream>
void SendConnectPacket(sf::UdpSocket& socket);
void SendDisconnectPacket(sf::UdpSocket& socket);
sf::Vector2f& GetServerPosition(sf::UdpSocket& socket);

void SendConnectPacket(sf::UdpSocket& socket)
{
	ConnectPacket connectPacket;
	socket.send(*connectPacket.GetPacket(), sf::IpAddress::LocalHost, 2000);
}

void SendDisconnectPacket(sf::UdpSocket& socket)
{
	DisconnectPacket disconnectPacket;
	socket.send(*disconnectPacket.GetPacket(), sf::IpAddress::LocalHost, 2000);
}

sf::Vector2f& GetServerPosition(sf::UdpSocket& socket)
{

	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;
	sf::Vector2f position;
	if (socket.receive(packet, sender, port) != sf::Socket::Done)
	{
		std::cout << "Error while receiving the message" << std::endl;
		return position;
	}

	int packetType = 0;
	if (!(packet >> packetType))
	{
		std::cout << "No packet type" << std::endl;
	}
	switch (packetType)
	{
	case PacketType::Position:
	{
		int id;
		packet >> id >> position.x >> position.y;
		return position;
	}
	}
	return position;
}
