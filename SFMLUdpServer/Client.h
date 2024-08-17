#pragma once
#include "SFML/Network.hpp"
class Client
{
public:
	Client();
	Client(int id, sf::IpAddress ip, unsigned short port);
	~Client();
	int GetId();
	sf::IpAddress GetIp();
	void SetIp(sf::IpAddress ip);
	void SetId(int id);
	unsigned short GetPort();
	void SetPort(unsigned short port);

private:
	int id;
	unsigned short port;
	sf::IpAddress ip;
};

