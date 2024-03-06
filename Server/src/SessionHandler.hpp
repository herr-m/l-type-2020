#ifndef _SESSIONHANDLER_H_
#define _SESSIONHANDLER_H_
#include <memory>
#include <list> 

class ServerSession;

class SessionHandler
{
    std::list<std::shared_ptr<ServerSession>> _sessions;
    public:
    void connect(ServerSession* to_add);
    void disconnect(int pid);
    void eraseSession(int);
    size_t size() const{ return _sessions.size();}
    void print();
   
    bool checkUser(const std::string& user);
};



#endif