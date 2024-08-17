#pragma once
#include <iostream>
#include <queue>
void SendEntities(sf::UdpSocket& socket, const EntityList& entities, const ClientList& clients, int ticks)
{
	clients.SendEntities(socket, entities, ticks);
}
void Listen(sf::UdpSocket& socket, EntityList& entityList, ClientList& clientList, std::queue<NetCommand>& commands)
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
				Entity* entity = new Entity(client);
				entityList.AddEntity(entity);
				clientList.AddClient(client);
				socket.send(*ConnectPacket(id).GetPacket(), sender, port);
			}
			break;
		case PacketType::Disconnect:
			clientList.RemoveClient(clientList.GetClientByIp(sender, port));
			std::cout << sender << " disconnected." << std::endl;
			break;
		case PacketType::Command:
			std::string command;
			int tick;
			packet >> tick;
			packet >> command;
			commands.push(NetCommand(command, tick, sender, port));
			break;
		}

	}
}
void HandleCommands(std::queue<NetCommand>& commandQueue, EntityList& entityList, int ticks)
{

	while (!commandQueue.empty() && commandQueue.front().GetTick() <= ticks)
	{
		std::cout << "Handling command: " << commandQueue.front().GetCommand() << std::endl;
		NetCommand command = commandQueue.front();
		commandQueue.pop();
		Entity* entity = entityList.GetEntityByIp(command.GetIp(), command.GetPort());
		if (entity == nullptr)
		{
			std::cout << "Entity not found." << std::endl;
			return;
		}
		if (command.GetCommand() == "+moveup")
		{
			entity->moveUp = true;
		}
		else if (command.GetCommand() == "-moveup")
		{
			entity->moveUp = false;
		}
		else if (command.GetCommand() == "+movedown")
		{
			entity->moveDown = true;
		}
		else if (command.GetCommand() == "-movedown")
		{
			entity->moveDown = false;
		}
		else if (command.GetCommand() == "+moveleft")
		{
			entity->moveLeft = true;
		}
		else if (command.GetCommand() == "-moveleft")
		{
			entity->moveLeft = false;
		}
		else if (command.GetCommand() == "+moveright")
		{
			entity->moveRight = true;
		}
		else if (command.GetCommand() == "-moveright")
		{
			entity->moveRight = false;
		}		
	}

}
