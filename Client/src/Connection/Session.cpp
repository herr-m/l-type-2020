#include "Session.hpp"
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>   
#include <thread>

void ClientSession::listen()
{
    std::thread t1(&PacketHandler::launch, &_handler);
    while (_connected)
    {
        std::shared_ptr <PacketAbstract> ptr{};
        std::ifstream inputstream(_server_to_client);
        if(inputstream.peek() != std::ifstream::traits_type::eof()) {
            boost::archive::text_iarchive inputarchive(inputstream);
            inputarchive >> ptr;
            _handler.add(ptr);
        }
    }
    t1.join();
    std::terminate();
}

void ClientSession::send(std::shared_ptr<PacketAbstract> packet)
{
    std::ofstream outputstream (_client_to_server);
    boost::archive::text_oarchive outputarchive(outputstream);
    outputarchive << packet;
    outputstream.flush();
    outputstream.close();
}

void ClientSession::end() {
    _connected = false;
    _handler.stop();
}
