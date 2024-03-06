#ifndef _PACKET_H_
#define _PACKET_H_
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/stack.hpp>
#include <string>
#include <stack>
#include "../../Client/src/Game/DataBaseSpawnDS.hpp"

class PacketHandler;

class PacketAbstract
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    virtual void execute(const PacketHandler&) const =0;
    virtual ~PacketAbstract ()  = default;
};
BOOST_CLASS_EXPORT_KEY(PacketAbstract)

class DummyPacket: public PacketAbstract
{
    int test = 0;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    DummyPacket()  = default;
    void execute(const PacketHandler&) const override{}
};
BOOST_CLASS_EXPORT_KEY(DummyPacket)

// Login
class LoginPacket: public PacketAbstract
{
    std::string _username;
    std::string _password;
    bool _isGuest;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit LoginPacket(std::string user,std::string pwd, bool isGuest):_username(user),_password(pwd), _isGuest(isGuest) {};
    LoginPacket()  = default;
    void execute(const PacketHandler&) const override;
};
BOOST_CLASS_EXPORT_KEY(LoginPacket)

class LoginPacketAnswer:public PacketAbstract
{
    bool _boolean;
    std::string _username{};
    std::string _error{};
    bool _isGuest;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit LoginPacketAnswer(bool bill,std::string user, std::string error, bool isGuest):_boolean(bill),_username(user), _error(error), _isGuest(isGuest) {}
    LoginPacketAnswer()  = default;
    void execute(const PacketHandler&) const override{}
};
BOOST_CLASS_EXPORT_KEY(LoginPacketAnswer)


// Signup
class SignupPacket: public PacketAbstract
{
    std::string _username;
    std::string _password;
    bool _isGuest;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit SignupPacket(std::string user,std::string pwd, bool isGuest):_username(user),_password(pwd), _isGuest(isGuest){};
    SignupPacket()  = default;
    void execute(const PacketHandler&) const override;
};
BOOST_CLASS_EXPORT_KEY(SignupPacket)

class SignupPacketAnswer:public PacketAbstract
{
    bool _boolean;
    std::string _username{};
    bool _isGuest;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit SignupPacketAnswer(bool bill,std::string user, bool isGuest):_boolean(bill),_username(user), _isGuest(isGuest){}
    SignupPacketAnswer()  = default;
    void execute(const PacketHandler&) const override{}
};
BOOST_CLASS_EXPORT_KEY(SignupPacketAnswer)

// FriendList
class FriendListPacket: public PacketAbstract {
    std::string _username;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit FriendListPacket(std::string user):_username(user){};
    FriendListPacket()  = default;
    void execute(const PacketHandler&) const override;

};
BOOST_CLASS_EXPORT_KEY(FriendListPacket)

class FriendListPacketAnswer:public PacketAbstract
{
    std::vector<std::string> _friends;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit FriendListPacketAnswer(std::vector<std::string> friends) : _friends(friends) {}
    FriendListPacketAnswer()  = default;
    void execute(const PacketHandler&) const override{}
};
BOOST_CLASS_EXPORT_KEY(FriendListPacketAnswer)

class AddFriendPacket: public PacketAbstract {
    std::string _username;
    std::string _userToAdd;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit AddFriendPacket(std::string user, std::string userToAdd):_username(user), _userToAdd(userToAdd){};
    AddFriendPacket()  = default;
    void execute(const PacketHandler&) const override;

};
BOOST_CLASS_EXPORT_KEY(AddFriendPacket)

class AddFriendErrPacket: public PacketAbstract {
    std::string _message;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit AddFriendErrPacket(std::string message): _message(message) {};
    AddFriendErrPacket()  = default;
    void execute(const PacketHandler&) const override {};

};
BOOST_CLASS_EXPORT_KEY(AddFriendErrPacket)

class RemoveFriendPacket: public PacketAbstract {
    std::string _username;
    std::string _userToRemove;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit RemoveFriendPacket(std::string user, std::string userToRemove):_username(user), _userToRemove(userToRemove){};
    RemoveFriendPacket()  = default;
    void execute(const PacketHandler&) const override;

};
BOOST_CLASS_EXPORT_KEY(RemoveFriendPacket)

class RemoveFriendErrPacket: public PacketAbstract {
    std::string _message;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit RemoveFriendErrPacket(std::string message): _message(message) {};
    RemoveFriendErrPacket()  = default;
    void execute(const PacketHandler&) const override {};

};
BOOST_CLASS_EXPORT_KEY(RemoveFriendErrPacket)

class DeleteFriendPacket: public PacketAbstract {
    std::string _username;
    std::string _userToDel;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit DeleteFriendPacket(std::string user, std::string userToDel):_username(user), _userToDel(userToDel){};
    DeleteFriendPacket()  = default;
    void execute(const PacketHandler&) const override;

};
BOOST_CLASS_EXPORT_KEY(DeleteFriendPacket)

// Scores
class ScorePacket : public PacketAbstract 
{
    std::string _username;
    std::string _nameOfLevel;
    int _score;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit ScorePacket (std::string user, std::string nameOfLevel, int score):_username(user), _nameOfLevel(nameOfLevel), _score(score){}
    ScorePacket()  = default;
    void execute(const PacketHandler&) const override;
    
    std::string getUser() { return _username; }
    int getScore() { return _score; }
    std::string getNameOfLevel() { return _nameOfLevel; }
};
BOOST_CLASS_EXPORT_KEY(ScorePacket)

class Top10QueryPacket : public PacketAbstract
{
    std::string _username;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit Top10QueryPacket (std::string user):_username(user){}
    Top10QueryPacket()  = default;
    void execute(const PacketHandler&) const override;
};
BOOST_CLASS_EXPORT_KEY(Top10QueryPacket)

class Top10QueryPacketAnswer : public PacketAbstract
{
    std::vector<ScorePacket> _scoreboard;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit Top10QueryPacketAnswer (std::vector<ScorePacket> scoreboard) : _scoreboard(scoreboard) {}
    Top10QueryPacketAnswer()  = default;
    void execute(const PacketHandler&) const override {};
};
BOOST_CLASS_EXPORT_KEY(Top10QueryPacketAnswer)

// Levels
// ?
class EnnemyPacket : public PacketAbstract 
{
    unsigned _ennemyId;
    double _triggerPos;
    double _xOffSet;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit EnnemyPacket (unsigned ennemyName, double timeOfSpawn, double xOffSet):_ennemyId(ennemyName), _triggerPos(timeOfSpawn), _xOffSet(xOffSet){}
    EnnemyPacket()  = default;
    void execute(const PacketHandler&) const override{};
    
    unsigned getEnnemyId() { return _ennemyId; }
    double getTriggerPos() { return _triggerPos; }
    double getXOffSet() { return _xOffSet; }
};
BOOST_CLASS_EXPORT_KEY(EnnemyPacket)

class AddCustomizedLevelPacket: public PacketAbstract {
    std::string _usernameOfCreator;
    std::string _nameOfLevel;
    std::vector<EnnemyPacket> _vectorOfLevel;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit AddCustomizedLevelPacket(std::string username, std::string nameOfLevel, std::vector<EnnemyPacket> vectorOfLevel):_usernameOfCreator(username), _nameOfLevel(nameOfLevel), _vectorOfLevel(vectorOfLevel){};
    AddCustomizedLevelPacket()  = default;
    void execute(const PacketHandler&) const override;
};
BOOST_CLASS_EXPORT_KEY(AddCustomizedLevelPacket)

class AddCustomizedLevelErrPacket: public PacketAbstract {
    std::string _message;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit AddCustomizedLevelErrPacket(std::string message): _message(message) {};
    AddCustomizedLevelErrPacket()  = default;
    void execute(const PacketHandler&) const override {};

};
BOOST_CLASS_EXPORT_KEY(AddCustomizedLevelErrPacket)


class CustomizedLevelPacket: public PacketAbstract {
    std::string _nameOfLevel;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit CustomizedLevelPacket(std::string nameOfLevel):_nameOfLevel(nameOfLevel){};
    CustomizedLevelPacket()  = default;
    void execute(const PacketHandler&) const override;

};
BOOST_CLASS_EXPORT_KEY(CustomizedLevelPacket)

class CustomizedLevelPacketAnswer:public PacketAbstract
{
    std::stack<EnnemyPacket> _ennemyStack;
    std::string _levelName;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit CustomizedLevelPacketAnswer(std::stack<EnnemyPacket> ennemyStack, std::string name) : _ennemyStack(ennemyStack), _levelName(name) {}
    CustomizedLevelPacketAnswer() = default;
    void execute(const PacketHandler&) const override{}
};
BOOST_CLASS_EXPORT_KEY(CustomizedLevelPacketAnswer)

class AddLikeToLevelPacket: public PacketAbstract {
    std::string _nameOfLevel;
    std::string _username;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit AddLikeToLevelPacket(std::string nameOfLevel, std::string username):_nameOfLevel(nameOfLevel), _username(username){};
    AddLikeToLevelPacket()  = default;
    void execute(const PacketHandler&) const override;

};
BOOST_CLASS_EXPORT_KEY(AddLikeToLevelPacket)

class AddLikeToLevelErrPacket: public PacketAbstract {
    std::string _message;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit AddLikeToLevelErrPacket(std::string message): _message(message) {};
    AddLikeToLevelErrPacket()  = default;
    void execute(const PacketHandler&) const override {};

};
BOOST_CLASS_EXPORT_KEY(AddLikeToLevelErrPacket)


class RemoveLikeFromLevelPacket: public PacketAbstract {
    std::string _nameOfLevel;
    std::string _username;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit RemoveLikeFromLevelPacket(std::string nameOfLevel, std::string username):_nameOfLevel(nameOfLevel), _username(username){};
    RemoveLikeFromLevelPacket()  = default;
    void execute(const PacketHandler&) const override;

};
BOOST_CLASS_EXPORT_KEY(RemoveLikeFromLevelPacket)

class RemoveLikeFromLevelErrPacket: public PacketAbstract {
    std::string _message;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit RemoveLikeFromLevelErrPacket(std::string message): _message(message) {};
    RemoveLikeFromLevelErrPacket()  = default;
    void execute(const PacketHandler&) const override {};

};
BOOST_CLASS_EXPORT_KEY(RemoveLikeFromLevelErrPacket)

class NumberOfLikesQueryPacket : public PacketAbstract
{
    std::string _nameOfLevel;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit NumberOfLikesQueryPacket (std::string nameOfLevel):_nameOfLevel(nameOfLevel){}
    NumberOfLikesQueryPacket()  = default;
    void execute(const PacketHandler&) const override;
};
BOOST_CLASS_EXPORT_KEY(NumberOfLikesQueryPacket)

class NumberOfLikesQueryPacketAnswer : public PacketAbstract
{
    int _nbrOfLikes;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit NumberOfLikesQueryPacketAnswer (int numberOfLikes) : _nbrOfLikes(numberOfLikes) {}
    NumberOfLikesQueryPacketAnswer()  = default;
    void execute(const PacketHandler&) const override {};
};
BOOST_CLASS_EXPORT_KEY(NumberOfLikesQueryPacketAnswer)

class LevelPacket : public PacketAbstract 
{
    std::string _author;
    std::string _name;
    int _likes;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit LevelPacket (std::string author, std::string name, int likes):_author(author), _name(name), _likes(likes){}
    LevelPacket()  = default;
    void execute(const PacketHandler&) const override{};
    
    std::string getAuthor() { return _author; }
    std::string getName() { return _name; }
    int getLikes() { return _likes; }
};
BOOST_CLASS_EXPORT_KEY(LevelPacket)

class FetchLevelsPacket : public PacketAbstract
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    FetchLevelsPacket()  = default;
    void execute(const PacketHandler&) const override;
};
BOOST_CLASS_EXPORT_KEY(FetchLevelsPacket)

class FetchLevelsPacketAnswer : public PacketAbstract
{
    std::vector<LevelPacket> _levels;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit FetchLevelsPacketAnswer (std::vector<LevelPacket> levels) : _levels(levels) {}
    FetchLevelsPacketAnswer()  = default;
    void execute(const PacketHandler&) const override {};
};
BOOST_CLASS_EXPORT_KEY(FetchLevelsPacketAnswer)

class FetchPlayableLevels : public PacketAbstract
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    FetchPlayableLevels()  = default;
    void execute(const PacketHandler&) const override; 
};
BOOST_CLASS_EXPORT_KEY(FetchPlayableLevels)

class FetchPlayableLevelsAns : public PacketAbstract
{
    std::vector<LevelPacket> _levels;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);
    public:
    explicit FetchPlayableLevelsAns (std::vector<LevelPacket> levels) : _levels(levels) {}
    FetchPlayableLevelsAns()  = default;
    void execute(const PacketHandler&) const override {};
};
BOOST_CLASS_EXPORT_KEY(FetchPlayableLevelsAns)

#endif
