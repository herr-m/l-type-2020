#include "Session.hpp"
#include "SessionHandler.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>   
#include <thread>
#include "Packet.hpp"

ServerSession::ServerSession (int pid,std::shared_ptr<Database> db, std::shared_ptr<SessionHandler> handler): SessionAbstract (pid), _handler(PacketHandler(this,db, handler))
    {mkfifo(_client_to_server.c_str(),0666);mkfifo(_server_to_client.c_str(),0666); _thread = std::thread(&ServerSession::listen, this);}

void  ServerSession::print()
{std::cout<<_client_to_server<<std::endl;}

bool ServerSession::operator== (int pid)
{return _pid==pid;}

bool ServerSession::isUserConnected () {return !(_mainuser.empty());}

void ServerSession::listen()
{
    std::thread t1(&PacketHandler::launch, &_handler);
    while (_connected)
    {
        std::shared_ptr <PacketAbstract> ptr{};
        std::ifstream inputstream(_client_to_server);
        if(inputstream.peek() != std::ifstream::traits_type::eof()) { 
            boost::archive::text_iarchive inputarchive(inputstream);
            inputarchive >> ptr;
            _handler.add(ptr);
        }
    }
    t1.join();
    //std::terminate();
}
void ServerSession::stop() {
    _connected = false;
    _handler.stop();
    _thread.join();
    unlink(_server_to_client.c_str());
    unlink(_client_to_server.c_str());
}

void ServerSession::send(std::shared_ptr<PacketAbstract> packet)
{
    std::ofstream outputstream (_server_to_client);
    boost::archive::text_oarchive outputarchive(outputstream);
    outputarchive << packet;
    outputstream.flush();
    outputstream.close();
}
