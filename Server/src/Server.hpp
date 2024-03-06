#ifndef _SERVER_H_
#define _SERVER_H_
#include <memory>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "SessionHandler.hpp"
#include "Database.hpp"
class Server
{
    constexpr static const char* _client_to_server = "/tmp/client_to_server";
    constexpr static const char* _server_to_client = "/tmp/server_to_client";
    std::shared_ptr<SessionHandler> _handler;
    std::shared_ptr<Database> _db ;
public:
    explicit Server();
    void launch();
};



#endif