#pragma once
#include <vector>
#include "Client.h"
#include <SFML/Network.hpp>
#include "EntityListPacket.h"
#include "EntityList.h"
#include "Packets.hpp"
class ClientList
{
	public:
	ClientList();
	~ClientList();
	void AddClient(Client* client);
	void RemoveClient(Client* client);
	Client* GetClient(int index);
	Client* GetClientById(int id);
	Client* GetClientByIp(sf::IpAddress ip, unsigned short port);
	int GetSize() const;
	int GetAvailableId();
	void SendEntities(sf::UdpSocket& socket, const EntityList& entityList, int ticks) const;
	const int MAX_CLIENTS = 8;
private:
	int currentId;
	std::vector<Client*> clients;
};

