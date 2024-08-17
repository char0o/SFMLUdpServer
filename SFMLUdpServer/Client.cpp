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

int Client::GetId()
{
	return id;
}

sf::IpAddress Client::GetIp()
{
	return ip;
}

unsigned short Client::GetPort()
{
	return port;
}

void Client::SetId(int id)
{
	this->id = id;
}

void Client::SetIp(sf::IpAddress ip)
{
	this->ip = ip;
}

void Client::SetPort(unsigned short port)
{
	this->port = port;
}
