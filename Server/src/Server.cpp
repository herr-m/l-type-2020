#include "Server.hpp"
#include "Session.hpp"
#include "PacketHandler.hpp"
#include <cstring>


Server::Server():_handler(new SessionHandler()),_db(new Database()) {}
void Server::launch()
{
    int clientserver ,serverclient;
    char buffer[256];
    char* token;
    mkfifo(_client_to_server,0666);
    mkfifo(_server_to_client,0666);
    while(1)
    {
        clientserver = open(_client_to_server,O_RDWR);
        if(clientserver < 0){perror("Problem in opening pipe \n");exit(1);};
        serverclient = open(_server_to_client,O_RDWR);
        if(serverclient<0){perror("Problem in opening pipe \n");exit(1);} 
        read(clientserver,buffer,sizeof(buffer));
        token = strtok(buffer,"\n");
        size_t size = _handler->size();
        if(strcmp(token,"connect")==0)  {
            token = strtok(NULL,"\n"); 
            _handler->connect(new ServerSession(atoi(token),_db, _handler));
            if(++size == _handler->size()){write(serverclient,"received",sizeof("received"));_handler->print();}
            else write(serverclient,"connection failed",sizeof("connection failed"));
        }
        else if(strcmp(token,"disconnect")==0) {
            token = strtok(NULL,"\n");
            _handler->disconnect(atoi(token));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            _handler->eraseSession(atoi(token));
            if(--size==_handler->size()) {write(serverclient,"received",sizeof("received"));_handler->print();}
            else { write(serverclient,"disconnection failed",sizeof("disconnection failed")); }
        }
        else write(serverclient,"not received",sizeof("not received"));
        memset(buffer,0,sizeof(buffer));
    }
    close(clientserver);
    close(serverclient);
}