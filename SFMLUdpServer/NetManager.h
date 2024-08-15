#pragma once

#include "SFML/Network.hpp"
#include "PacketType.h"
#include <iostream>

void Listen(sf::UdpSocket& socket);
void SendPlayerPos(sf::UdpSocket& socket, sf::Vector2f& pos);

void SendPlayerPos(sf::UdpSocket& socket, const sf::Vector2f& pos)
{
	PlayerPacket playerPacket(1, pos);;
	socket.send(*playerPacket.GetPacket(), sf::IpAddress::LocalHost, 2001);
}
void Listen(sf::UdpSocket& socket)
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
			break;
		case PacketType::Disconnect:
			std::cout << sender << " disconnected." << std::endl;
			break;
		}
	}
}