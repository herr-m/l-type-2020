#include "PacketHandler.hpp"
#include "DataBaseSpawnDS.hpp"
#include "Database.hpp"
#include "Packet.hpp"
#include "Session.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <chrono>
#include <exception>   
#include <algorithm> 

void PacketHandler::launch()
{
    while(_launched)
    {
    if (_queue.empty()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    else
    {
        _queue.front()-> execute(*this);
        _queue.pop();}
    }
}

void PacketHandler::stop() {
    _launched = false;
}

void PacketHandler::add(std::shared_ptr<PacketAbstract> to_add) 
{
    _queue.push(to_add);
}

void PacketHandler::login(const std::string& username,const std::string& pwd, bool isGuest) const
{
    std::cout << "LOGIN " << username << std::endl;

    bool answer = false;
    std::string errMessage;
    if(username.empty())
        errMessage = "Empty username!";
    else if(_handler->checkUser(username)) {
       errMessage = "User already connected!";
    }
    else {
        if( _db->isPasswordMatching(username, pwd)) {
            answer = true;
            isGuest ? _session->setGuestUser(username) : _session->setMainUser(username);
        }
        else {
            errMessage = "Wrong username or password!";
        }
    }
    
    
    std::cout << (answer ? "SUCCESS" : "FAILED") << std::endl;

    _session -> send (std::shared_ptr<PacketAbstract>(new LoginPacketAnswer(answer,username, errMessage, isGuest)));
}

void PacketHandler::signup(const std::string& username,const std::string& pwd, bool isGuest) const
{
    std::cout << "SIGNUP" << std::endl;

    bool answer = false;
    if(!username.empty())
        answer = _db->newAccount(username, pwd);

    _session -> send (std::shared_ptr<PacketAbstract>(new SignupPacketAnswer(answer,username,isGuest)));
}

void PacketHandler::getFriendList(const std::string& username) const {
    std::cout << "FRIENDLIST" << std::endl;
    std::vector<std::string> friendsList = _db->getFriendsListOf(username);

    _session->send(std::shared_ptr<PacketAbstract>(new FriendListPacketAnswer(friendsList)));
}

void PacketHandler::addFriend(const std::string& username, const std::string& userToAdd) const {
    std::cout << "ADDFRIEND" << std::endl;

    bool answer = false;
    std::string errMessage;
    if(userToAdd.empty())
        errMessage = "Empty name!";
    else if(!_db->isUsernameInDatabase(userToAdd))
        errMessage = "User you are trying to add does not exist!";
    else
        if(_db->friendshipExists(username, userToAdd))
            errMessage = "You are already friends!";
        else {
            answer = true;
            _db->newFriendship(username, userToAdd);
        }
    
    if(answer)
        getFriendList(username);
    else
        _session->send(std::shared_ptr<PacketAbstract>(new AddFriendErrPacket(errMessage)));
}

void PacketHandler::removeFriend(const std::string& username, const std::string& userToDel) const {
    std::cout << "REMOVEFRIEND" << std::endl;
    _db->deleteFriendship(username, userToDel);

    getFriendList(username);
}

void PacketHandler::getTop10() const {
    std::cout << "FRIENDLIST" << std::endl;
    std::vector<ScorePacket> scoreboard;
    for(auto i : _db->getGlobalTopTen()) {
        scoreboard.push_back(ScorePacket(i.username, i.nameOfLevel, i.score));
    }

    _session->send(std::shared_ptr<PacketAbstract>(new Top10QueryPacketAnswer(scoreboard)));
}

void PacketHandler::writeScore(std::string player, std::string level, int score) const {
    _db->newScore(player, level,  score);
}


void PacketHandler::addCustomizedLevel(const std::string& usernameOfCreator, const std::string& nameOfLevel, const std::vector<EnnemyPacket>& vectorOfLevel) const {
    std::cout << "ADDCUSTOMIZEDLEVEL" << std::endl;

    if(nameOfLevel.empty()) {
        _session->send(std::shared_ptr<PacketAbstract>(new AddCustomizedLevelErrPacket("Empty level name!"))); return;
    }
    
    std::vector<DataBaseSpawnDS> temp;
    for(EnnemyPacket i : vectorOfLevel) temp.push_back(DataBaseSpawnDS(i.getEnnemyId(), i.getTriggerPos(), i.getXOffSet()));
    bool answer = _db->newCustomizedLevel(usernameOfCreator, nameOfLevel, temp);
    std::string errMessage;
    
    if(!answer)
        errMessage = "A level already has this name, please use another one.";
        _session->send(std::shared_ptr<PacketAbstract>(new AddCustomizedLevelErrPacket(errMessage)));
}

void PacketHandler::getLevel(const std::string& nameOfLevel) const {
    std::cout << "GETLEVEL" << std::endl;

    std::stack<DataBaseSpawnDS> ennemyStack = _db->getLevel(nameOfLevel);
    // Algo rapide
    std::stack<EnnemyPacket> temp;
    while(!ennemyStack.empty()) {
        temp.push(EnnemyPacket(ennemyStack.top().ennemyID, ennemyStack.top().triggerPos, ennemyStack.top().xOffSet));
        ennemyStack.pop();
    }

    std::stack<EnnemyPacket> temp1;
    while(!temp.empty()) {
        temp1.push(temp.top());
        temp.pop();
    }
    _session->send(std::shared_ptr<PacketAbstract>(new CustomizedLevelPacketAnswer(temp1, nameOfLevel)));
}

void PacketHandler::addLikeToLevel(const std::string& nameOfLevel, const std::string& username) const {
    std::cout << "ADDLIKE" << std::endl;

    std::string errMessage = "Level liked!";
    bool answer = _db->addLikeToLevel(nameOfLevel, username);
    
    if(!answer)
        errMessage = "You already liked this level !";

    _session->send(std::shared_ptr<PacketAbstract>(new AddLikeToLevelErrPacket(errMessage)));
}

void PacketHandler::removeLikeFromLevel(const std::string& nameOfLevel, const std::string& username) const {
    std::cout << "REMOVELIKE" << std::endl;

    std::string errMessage;
    bool answer = _db->removeLikeFromLevel(nameOfLevel, username);

    if (!answer)
        errMessage = "User did not like this level !";
        _session->send(std::shared_ptr<PacketAbstract>(new RemoveLikeFromLevelErrPacket(errMessage)));
}

void PacketHandler::getNumberOfLikesForLevel(const std::string& nameOfLevel) const {
    std::cout << "GETNUMBEROFLIKES" << std::endl;

    int nbrOfLikes = _db->getNumberOfLikesForLevel(nameOfLevel);
    _session->send(std::shared_ptr<PacketAbstract>(new NumberOfLikesQueryPacketAnswer(nbrOfLikes)));
};

void PacketHandler::getAllLevels() const {
    std::cout << "FETCHLEVELLIST" << std::endl;

    std::vector<LevelPacket> res;
    std::vector<LevelInfo> temp = _db->getAllLevels();
    for(LevelInfo i : temp) {
        res.push_back(LevelPacket(i.author, i.name, i.likes));
    }

    _session->send(std::shared_ptr<PacketAbstract>(new FetchLevelsPacketAnswer(res)));
}

void PacketHandler::getAllPlayableLevels() const {
    std::cout << "FETCHLEVELLIST" << std::endl;

    std::vector<LevelPacket> res;
    std::vector<LevelInfo> temp = _db->getAllLevels();
    for(LevelInfo i : temp) {
        res.push_back(LevelPacket(i.author, i.name, i.likes));
    }

    _session->send(std::shared_ptr<PacketAbstract>(new FetchPlayableLevelsAns(res)));
}