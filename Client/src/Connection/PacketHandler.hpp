#ifndef _PACKETHANDLER_H_
#define _PACKETHANDLER_H_
#include "Packet.hpp"
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include "../Game/DataBaseSpawnDS.hpp"

class Interface;
class LevelMaker;
class GameDisplay;
class PacketAbstract;
class ClientSession;

class PacketHandler
{
    std::queue<std::shared_ptr<PacketAbstract>> _queue;
    ClientSession* _session;
    bool _launched =true;

    std::shared_ptr<Interface> _inter{};
    std::shared_ptr<LevelMaker> _levelmaker{};
    std::shared_ptr<GameDisplay> _gameDisplay{};
public:
    explicit PacketHandler(ClientSession* session):_session(session) {};
    void launch();
    void stop();
    void add(std::shared_ptr<PacketAbstract>);
    void loginAns(const bool, const std::string, const std::string, bool) const;
    void signupAns(const bool, const std::string, bool) const;
    void friendListAns(std::vector<std::string> ) const;
    void addFriendErr(std::string) const;
    void removeFriendErr(std::string) const;
    void top10Ans(std::vector<ScorePacket>) const;
    void addCustomizedLevelErr(std::string) const;
    void addLikeToLevelErr(const std::string&) const;
    void removeLikeFromLevelErr(std::string) const;
    void displayLevels(std::vector<LevelPacket>) const;
    void displayLevelChoice(std::vector<LevelPacket>) const;
    void playLevel(std::stack<EnnemyPacket>, std::string) const;

    void setInterfacePtr(Interface*);
    void setLevelMakerPtr(LevelMaker*);
    void setGameDisplayPtr(GameDisplay*);
};

#endif