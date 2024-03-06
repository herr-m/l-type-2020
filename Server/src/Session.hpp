#ifndef _SESSION_H_
#define _SESSION_H_
#include "Packet.hpp"
#include "Database.hpp"
#include "PacketHandler.hpp"
#include <atomic>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <thread>
#include <memory>

class SessionHandler;
class SessionAbstract
{
    protected:
    std::atomic<bool> _connected;
    std::string _mainuser{};
    std::string _guest{};
    int _pid;
    std::string  _client_to_server = "/tmp/client_to_server_";
    std::string  _server_to_client = "/tmp/server_to_client_";
    explicit SessionAbstract(int pid):
    _pid(pid), _connected(true) {_client_to_server +=std::to_string(_pid);_server_to_client+=std::to_string(_pid);};
    public:
    virtual void setMainUser(const std::string& user)=0;
    virtual void setGuestUser(const std::string& user)=0;
    virtual void send(std::shared_ptr<PacketAbstract> packet)=0;
    virtual void listen()=0;
    virtual void stop()=0;
    virtual ~SessionAbstract() noexcept = default;

};

class ServerSession: public SessionAbstract
{
   
    bool _userconnected = false;
    PacketHandler _handler;
    std::thread _thread;
public:
    explicit ServerSession (int pid,std::shared_ptr<Database> db, std::shared_ptr<SessionHandler>);
    void print();
    ServerSession() noexcept = default;
    bool operator== (int);
    void send (std::shared_ptr<PacketAbstract> packet) override;
    void listen() override;
    void stop() override;
    bool isUserConnected () ;
    void setMainUser(const std::string& user) override { _mainuser = user; }
    void setGuestUser(const std::string& user) override { _guest = user; }

    bool compUser(const std::string& user) { return _mainuser == user; }
};

#endif