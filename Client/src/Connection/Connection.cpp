#include "Connection.hpp"
#include "Session.hpp"

void Connection::connect()
{
    int clientserver ,serverclient,connected = 0;
    char pid[10];
    sprintf(pid,"%d",getpid());
    char buffer[128] = "connect\n";
    strcat(buffer,pid);
    std::cout << buffer << std::endl;
    clientserver = open(_client_to_server,O_WRONLY);
    if(clientserver < 0){perror("Problem in opening pipe \n");exit(1);};
    serverclient = open(_server_to_client,O_RDONLY);
    if(serverclient<0){perror("Problem in opening pipe \n");exit(1);} 
    while ( !connected)
    {   
    write(clientserver,buffer,sizeof(buffer));
    read(serverclient,buffer,sizeof(buffer));
    if(strcmp(buffer,"received")==0){
        std::cout << "connecté"<< std::endl;connected = 1;
        _session.reset(new ClientSession());
        std::thread thread(&ClientSession::listen, _session);
        thread.detach();
        }
    }
    close(clientserver);
    close(serverclient);
}

void Connection::disconnect()
{
    int clientserver ,serverclient,disconnected = 0;
    char pid[10];
    sprintf(pid,"%d",getpid());
    char buffer[128] = "disconnect\n";
    strcat(buffer,pid);
    std::cout << buffer << std::endl;
    clientserver = open(_client_to_server,O_WRONLY);
    if(clientserver < 0){perror("Problem in opening pipe \n");exit(1);};
    serverclient = open(_server_to_client,O_RDONLY);
    if(serverclient<0){perror("Problem in opening pipe \n");exit(1);} 
    while ( !disconnected)
    {   
        write(clientserver,buffer,sizeof(buffer));
        _session->send(std::shared_ptr<PacketAbstract>(new DummyPacket()));
        read(serverclient,buffer,sizeof(buffer));
        if(strcmp(buffer,"received")==0){
            std::cout << "deconnecté"<< std::endl;disconnected = 1;
            _session->end();
            }
    }
    close(clientserver);
    close(serverclient);
}

void Connection::send(std::shared_ptr<PacketAbstract> packet) {
    _session->send(packet);
}