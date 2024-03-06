#ifndef _PACKETHANDLER_H_
#define _PACKETHANDLER_H_
#include <memory>
#include <queue>
#include <string>
#include "Database.hpp"
#include "Packet.hpp"
#include "SessionHandler.hpp"

class PacketAbstract;
class SessionAbstract;

class PacketHandler
{
    std::queue<std::shared_ptr<PacketAbstract>> _queue;
    SessionAbstract* _session;
    bool _launched =true;
    std::shared_ptr<Database> _db;
    std::shared_ptr<SessionHandler> _handler;
    public:
    explicit PacketHandler(SessionAbstract* session,std::shared_ptr<Database> db, std::shared_ptr<SessionHandler> handler):_session(session),_db(db), _handler(handler){};
    void launch();
    void stop();
    void add(std::shared_ptr<PacketAbstract>);
    void login (const std::string&,const std::string&, bool)const;
    void signup (const std::string&,const std::string&, bool)const;
    void getFriendList(const std::string&) const;
    void addFriend(const std::string&, const std::string&) const;
    void removeFriend(const std::string&, const std::string&) const;
    void getTop10() const;
    void writeScore(std::string, std::string, int) const;
    
    void addCustomizedLevel(const std::string&, const std::string&, const std::vector<EnnemyPacket>&) const;
    void getLevel(const std::string&) const;
    void addLikeToLevel(const std::string&, const std::string&) const;
    void removeLikeFromLevel(const std::string&, const std::string&) const;
    void getNumberOfLikesForLevel(const std::string&) const;
    void getAllLevels() const;
    void getAllPlayableLevels() const;
};




#endif