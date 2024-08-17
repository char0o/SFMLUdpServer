#pragma once
#include <string>
#include "SFML/Network.hpp"
class NetCommand
{
public:
	NetCommand();
	NetCommand(std::string command, int tick);
	NetCommand(std::string command, int tick, sf::IpAddress ip, unsigned short port);
	~NetCommand();

	std::string GetCommand() const;
	int GetTick() const;
	sf::IpAddress GetIp() const;
	unsigned short GetPort() const;
private:
	std::string command;
	int tick;
	sf::IpAddress ip;
	unsigned short port;
};

