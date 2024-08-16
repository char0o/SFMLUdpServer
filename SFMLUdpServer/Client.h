#pragma once
#include "SFML/Network.hpp"
class Client
{
public:
	Client();
	Client(int id, sf::IpAddress ip, unsigned short port);
	~Client();
	int getId();
	sf::IpAddress getIp();
	void setIp(sf::IpAddress ip);
	void setId(int id);
	unsigned short getPort();
	void setPort(unsigned short port);
private:
	int id;
	unsigned short port;
	sf::IpAddress ip;
};

