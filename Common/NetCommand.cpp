#include "NetCommand.h"

NetCommand::NetCommand()
{
	this->command = "";
	this->tick = 0;
	this->ip = sf::IpAddress::None;
	this->port = 0;
}

NetCommand::NetCommand(std::string command, int tick)
{
	this->command = command;
	this->tick = tick;
	this->ip = sf::IpAddress::None;
	this->port = 0;
}

NetCommand::NetCommand(std::string command, int tick, sf::IpAddress ip, unsigned short port)
{
	this->command = command;
	this->tick = tick;
	this->ip = ip;
	this->port = port;

}

NetCommand::~NetCommand()
{

}

std::string NetCommand::GetCommand() const
{
	return this->command;
}

int NetCommand::GetTick() const
{
	return this->tick;
}

sf::IpAddress NetCommand::GetIp() const
{
	return this->ip;
}

unsigned short NetCommand::GetPort() const
{
	return this->port;
}