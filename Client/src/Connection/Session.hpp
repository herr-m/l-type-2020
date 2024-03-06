#ifndef _SESSION_H_
#define _SESSION_H_
#include "Packet.hpp"
#include "PacketHandler.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <thread>
#include <memory>


class LevelMaker;
class SessionAbstract
{
    protected:
    bool _connected = true;
    std::string _mainuser{};
    std::string _guest{};
    int _pid;
    std::string  _client_to_server = "/tmp/client_to_server_";
    std::string  _server_to_client = "/tmp/server_to_client_";
    explicit SessionAbstract(int pid):
    _pid(pid){_client_to_server +=std::to_string(_pid);_server_to_client+=std::to_string(_pid);};
    public:
    virtual void send(std::shared_ptr<PacketAbstract> packet)=0;
    virtual void listen()=0;
    virtual ~SessionAbstract() noexcept = default;

};

class ClientSession: public SessionAbstract
{
    PacketHandler _handler;
public:
    explicit ClientSession(): SessionAbstract(getpid()), _handler(this){}
    virtual ~ClientSession() noexcept = default ;
    void listen() override;
    void end();
    void send (std::shared_ptr<PacketAbstract>) override;

    void setInterfacePtr(Interface* inter) { _handler.setInterfacePtr(inter); }
    void setLevelMakerPtr(LevelMaker* levelmaker) {_handler.setLevelMakerPtr(levelmaker); }
    void setGameDisplayPtr(GameDisplay* gameDisplay) {_handler.setGameDisplayPtr(gameDisplay); }
};
#endif