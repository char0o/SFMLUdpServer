#include "Client.h"

Client::Client()
{

}

Client::Client(int id, sf::IpAddress ip, unsigned short port)
{
	this->id = id;
	this->ip = ip;
	this->port = port;
}

Client::~Client()
{

}

int Client::getId()
{
	return id;
}

sf::IpAddress Client::getIp()
{
	return ip;
}

unsigned short Client::getPort()
{
	return port;
}

void Client::setId(int id)
{
	this->id = id;
}

void Client::setIp(sf::IpAddress ip)
{
	this->ip = ip;
}

void Client::setPort(unsigned short port)
{
	this->port = port;
}
