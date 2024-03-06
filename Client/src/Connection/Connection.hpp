#ifndef _CONNECTION_H_
#define _CONNECTION_H_
#include <memory>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include "Packet.hpp"
#include "Session.hpp"

class Connection final 
{
    constexpr static const char* _client_to_server = "/tmp/client_to_server";
    constexpr static const char* _server_to_client = "/tmp/server_to_client";
    std::shared_ptr<ClientSession> _session;
    public:
    constexpr Connection() noexcept = default;

    void connect();
    void disconnect();
    void send(std::shared_ptr<PacketAbstract>);

    void setInterfacePtr(Interface* inter) { _session->setInterfacePtr(inter); }
    void setLevelMakerPtr(LevelMaker* levelmaker) {_session->setLevelMakerPtr(levelmaker); }
    void setGameDisplayPtr(GameDisplay* gameDisplay) {_session->setGameDisplayPtr(gameDisplay); }
};

#endif