#include "ClientList.h"

ClientList::ClientList()
{

}

ClientList::~ClientList()
{
	for (int i = 0; i < clients.size(); i++)
	{
		delete clients[i];
	}
}

void ClientList::AddClient(Client* client)
{
	clients.push_back(client);
}

void ClientList::RemoveClient(Client* client)
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i] == client)
		{
			clients.erase(clients.begin() + i);
			delete client;
			break;
		}
	}
}

Client* ClientList::GetClient(int index)
{
	if (index < 0 || index >= clients.size())
		return nullptr;

	return clients[index];
}

Client* ClientList::GetClientById(int it)
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getId() == it)
			return clients[i];
	}
	return nullptr;
}

Client* ClientList::GetClientByIp(sf::IpAddress ip, unsigned short port)
{
	for (int i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getIp() == ip && clients[i]->getPort() == port)
			return clients[i];
	}
	return nullptr;
}
int ClientList::GetAvailableId()
{
	int id = 0;
	bool found = false;
	for (int i = 0; i < MAX_CLIENTS || !found; i++)
	{
		if (GetClientById(i) == nullptr)
		{
			id = i;
			found = true;
		}
	}
	return id;
}
void ClientList::SendEntities(sf::UdpSocket& socket, const EntityList& entities, int ticks) const
{
	for (int i = 0; i < clients.size(); i++)
	{
		EntityListPacket entityListPacket(entities, ticks);

		socket.send(*entityListPacket.GetPacket(), clients[i]->getIp(), clients[i]->getPort());
	}
}
int ClientList::GetSize() const
{
	return clients.size();
}