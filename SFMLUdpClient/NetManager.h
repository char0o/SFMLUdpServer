#pragma once
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include  "GameState.h"
#include "Packets.hpp"
#include <iostream>
#include "Globals.h"

using namespace sf;
struct ServerInfo
{
	sf::IpAddress address = "localhost";
	int port = 0;
};


class NetManager
{
public:
	NetManager();
	~NetManager();

	int GetLocalPlayer() const;

	bool Connect(IpAddress address, int port);
	void SendDisconnectPacket();
	const int CONNECTION_DELAY = 5;
	void SendCommands(Event& event, int ticks, EntityList& entityList);
	void Listen(GameState*& currentState, GameState*& nextState);
	void InterPolateEntities(GameState* current, GameState* next, float dt);
private:
	UdpSocket* socket;
	ServerInfo* serverInfo;
	int localPlayer = 0;
};





