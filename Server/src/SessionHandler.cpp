#include "SessionHandler.hpp"
#include "Session.hpp"
#include <thread>

void SessionHandler::connect(ServerSession* to_add)
{_sessions.push_back(std::shared_ptr<ServerSession>(to_add));}

void SessionHandler::print()
 {std::list<std::shared_ptr<ServerSession>>::iterator it = _sessions.begin();
    while(it != _sessions.end())
    {
        (*it) -> print();
        ++it;
    }    
}

void SessionHandler::disconnect(int pid)
{
    bool deleted = false;
    std::list<std::shared_ptr<ServerSession>>::iterator it = _sessions.begin();
    while(it!=_sessions.end() && !deleted)
    {
        if ((*it)->operator==(pid)){
            (*it)->stop();
            deleted=true;
        }
        else ++it;
    }
}

bool SessionHandler::checkUser(const std::string& user) {
    bool connected = false;
    std::list<std::shared_ptr<ServerSession>>::iterator it = _sessions.begin();
    while(it!=_sessions.end() && !connected) {
        if((*it) ->isUserConnected()) 
            connected = (*it) -> compUser(user);

        ++it;
    }

    return connected;
}

void SessionHandler::eraseSession(int pid) {
    bool deleted = false;
    std::list<std::shared_ptr<ServerSession>>::iterator it = _sessions.begin();
    while(it!=_sessions.end() && !deleted)
    {
        if ((*it)->operator==(pid)){
            (*it).reset();
            _sessions.erase(it);
            deleted=true;
        }
        else ++it;
    }
}