#include "NetManager.h"

NetManager::NetManager()
{
	socket = new sf::UdpSocket();
	socket->setBlocking(false);
	serverInfo = new ServerInfo();
}

NetManager::~NetManager()
{
	delete socket;
	delete serverInfo;
}

int NetManager::GetLocalPlayer() const
{
	return localPlayer;
}

bool NetManager::Connect(sf::IpAddress address, int port)
{
	if (socket->bind(CLIENT_PORT) != sf::Socket::Done)
	{
		std::cout << "Failed to bind socket" << std::endl;
	}
	sf::Clock clock;
	sf::Time lastChecked = sf::Time::Zero;
	while (clock.getElapsedTime().asSeconds() < CONNECTION_DELAY)
	{
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() - lastChecked.asSeconds() >= 1)
		{
			std::cout << "Trying to connect..." << std::endl;;
			ConnectPacket connectPacket;
			socket->send(*connectPacket.GetPacket(), address, port);

			lastChecked = elapsed;

		}
		sf::Packet answer;
		sf::IpAddress sender;
		unsigned short senderPort;
		if (socket->receive(answer, sender, senderPort) == sf::Socket::Done)
		{
			int packetType;
			answer >> packetType;
			if (packetType == PacketType::Connect)
			{
				answer >> localPlayer;
				serverInfo->address = sender;
				serverInfo->port = senderPort;
				std::cout << "Connected to server" << std::endl;
				return true;
			}
		}
	}
	return false;
}

void NetManager::SendDisconnectPacket()
{
	DisconnectPacket disconnectPacket;
	socket->send(*disconnectPacket.GetPacket(), serverInfo->address, serverInfo->port);
}

void NetManager::SendCommands(sf::Event& event, int ticks, EntityList& entityList)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::W)
		{
			NetCommand command("+moveup", ticks);
			CommandPacket commandPacket(command);
			socket->send(*commandPacket.GetPacket(), serverInfo->address, serverInfo->port);
		}
		if (event.key.code == sf::Keyboard::S)
		{
			NetCommand command("+movedown", ticks);
			CommandPacket commandPacket(command);
			socket->send(*commandPacket.GetPacket(), serverInfo->address, serverInfo->port);
		}
		if (event.key.code == sf::Keyboard::A)
		{
			NetCommand command("+moveleft", ticks);
			CommandPacket commandPacket(command);
			socket->send(*commandPacket.GetPacket(), serverInfo->address, serverInfo->port);
		}
		if (event.key.code == sf::Keyboard::D)
		{
			NetCommand command("+moveright", ticks);
			CommandPacket commandPacket(command);
			socket->send(*commandPacket.GetPacket(), serverInfo->address, serverInfo->port);
		}
	}
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W)
		{
			NetCommand command("-moveup", ticks);
			CommandPacket commandPacket(command);
			socket->send(*commandPacket.GetPacket(), serverInfo->address, serverInfo->port);
		}
		if (event.key.code == sf::Keyboard::S)
		{
			NetCommand command("-movedown", ticks);
			CommandPacket commandPacket(command);
			socket->send(*commandPacket.GetPacket(), serverInfo->address, serverInfo->port);
		}
		if (event.key.code == sf::Keyboard::A)
		{
			NetCommand command("-moveleft", ticks);
			CommandPacket commandPacket(command);
			socket->send(*commandPacket.GetPacket(), serverInfo->address, serverInfo->port);
		}
		if (event.key.code == sf::Keyboard::D)
		{
			NetCommand command("-moveright", ticks);
			CommandPacket commandPacket(command);
			socket->send(*commandPacket.GetPacket(), serverInfo->address, serverInfo->port);
		}
	}
}

void NetManager::Listen(GameState*& currentState, GameState*& nextState)
{

	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;
	sf::Vector2f position;
	if (socket->receive(packet, sender, port) != sf::Socket::Done)
	{
		return;
	}

	int packetType = 0;
	if (!(packet >> packetType))
	{
		std::cout << "No packet type" << std::endl;
	}
	switch (packetType)
	{
		int id;
	case PacketType::Entities:
	{
		int ticks;
		packet >> ticks;
		if (currentState->GetTicks() >= ticks)
			return;

		GameState* tempCurrent = currentState;
		GameState* tempNext = nextState;
		currentState = tempNext;
		nextState = new GameState(tempCurrent->GetEntityList(), packet, ticks, localPlayer);
		delete tempCurrent;
	}
	break;
	case PacketType::Connect:
		packet >> id;
		std::cout << id;
		break;
	}
}


void NetManager::InterPolateEntities(GameState* current, GameState* next, float dt)
{
	if (current == nullptr || next == nullptr)
		return;
	EntityList* currentList = current->GetEntityList();
	EntityList* nextList = next->GetEntityList();
	if (currentList == nullptr || nextList == nullptr)
		return;
	for (int i = 0; i < currentList->GetSize(); i++)
	{
		BaseEntity* currentEntity = currentList->GetEntity(i);
		BaseEntity* nextEntity = nextList->GetEntityById(currentEntity->GetId());
		if (nextEntity == nullptr)
			continue;
		float alpha = dt / TICKRATIO;
		sf::Vector2f position = currentEntity->GetPosition() + (nextEntity->GetPosition() - currentEntity->GetPosition()) * alpha;
		currentEntity->SetPosition(position);
	}
}