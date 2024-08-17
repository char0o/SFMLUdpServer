#include "CommandPacket.h"

CommandPacket::CommandPacket() {
	this->packet = new sf::Packet();
}

CommandPacket::CommandPacket(NetCommand& command)
{
	this->packet = new sf::Packet();
	*packet << static_cast<int>(PacketType::Command);
	*packet << command.GetTick();
	*packet << command.GetCommand();
}
CommandPacket::CommandPacket(int tick, std::string command) {
	this->packet = new sf::Packet();
	*packet << static_cast<int>(PacketType::Command);
	*packet << tick;
	*packet << command;
}

CommandPacket::~CommandPacket() {
	delete this->packet;
}

sf::Packet* CommandPacket::GetPacket() {
	return this->packet;
}
