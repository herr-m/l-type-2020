#include "Packet.hpp"
#include "PacketHandler.hpp"
#include <unistd.h>
#include <iostream>
#include <string>

template<class Archive>
void PacketAbstract::serialize(Archive & ar, const unsigned int version){}
template void PacketAbstract::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void PacketAbstract::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(PacketAbstract);

template<class Archive>
void DummyPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & test;
}  
template void DummyPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void DummyPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(DummyPacket);

// Login
template<class Archive>
void LoginPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _username;
    ar & _password;
    ar & _isGuest;
}  
template void LoginPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void LoginPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(LoginPacket)

void LoginPacket::execute (const PacketHandler& handler) const
{handler.login(_username,_password,_isGuest);}

template<class Archive>
void LoginPacketAnswer::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _boolean;
    ar & _username;
    ar & _error;
    ar & _isGuest;
}  
template void LoginPacketAnswer::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void LoginPacketAnswer::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(LoginPacketAnswer);


// Signup
template<class Archive>
void SignupPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _username;
    ar & _password;
    ar & _isGuest;
}  
template void SignupPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void SignupPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(SignupPacket);

void SignupPacket::execute (const PacketHandler& handler) const
{handler.signup(_username,_password, _isGuest);}

template<class Archive>
void SignupPacketAnswer::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _boolean;
    ar & _username;
    ar & _isGuest;
}  
template void SignupPacketAnswer::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void SignupPacketAnswer::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(SignupPacketAnswer);

// Friendlist
template<class Archive>
void FriendListPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _username;
}
template void FriendListPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void FriendListPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(FriendListPacket)

template<class Archive>
void FriendListPacketAnswer::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _friends;
}
template void FriendListPacketAnswer::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void FriendListPacketAnswer::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(FriendListPacketAnswer)

void FriendListPacket::execute (const PacketHandler& handler) const
{handler.getFriendList(_username);}

template<class Archive>
void AddFriendPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _username;
    ar & _userToAdd;
}
template void AddFriendPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void AddFriendPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(AddFriendPacket)

void AddFriendPacket::execute (const PacketHandler& handler) const
{handler.addFriend(_username,_userToAdd);}

template<class Archive>
void AddFriendErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void AddFriendErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void AddFriendErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(AddFriendErrPacket)

template<class Archive>
void RemoveFriendPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _username;
    ar & _userToRemove;
}
template void RemoveFriendPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void RemoveFriendPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(RemoveFriendPacket)

void RemoveFriendPacket::execute (const PacketHandler& handler) const
{handler.removeFriend(_username,_userToRemove);}

template<class Archive>
void RemoveFriendErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void RemoveFriendErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void RemoveFriendErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(RemoveFriendErrPacket)

// Scores
template<class Archive>
void ScorePacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _username;
    ar & _nameOfLevel;
    ar & _score;
}
template void ScorePacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void ScorePacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(ScorePacket)

void ScorePacket::execute(const PacketHandler& handler) const {
    handler.writeScore(_username, _nameOfLevel, _score);
}

template<class Archive>
void Top10QueryPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _username;
}
template void Top10QueryPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void Top10QueryPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(Top10QueryPacket)

void Top10QueryPacket::execute(const PacketHandler& handler) const {
    handler.getTop10();
}

template<class Archive>
void Top10QueryPacketAnswer::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _scoreboard;
}
template void Top10QueryPacketAnswer::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void Top10QueryPacketAnswer::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(Top10QueryPacketAnswer)

// Levels
template<class Archive>
void EnnemyPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _ennemyId;
    ar & _triggerPos;
    ar & _xOffSet;
}
template void EnnemyPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void EnnemyPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(EnnemyPacket)

template<class Archive>
void AddCustomizedLevelPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _usernameOfCreator;
    ar & _nameOfLevel;
    ar & _vectorOfLevel;
}
template void AddCustomizedLevelPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void AddCustomizedLevelPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(AddCustomizedLevelPacket)

void AddCustomizedLevelPacket::execute (const PacketHandler& handler) const
{handler.addCustomizedLevel(_usernameOfCreator,_nameOfLevel, _vectorOfLevel);}

template<class Archive>
void AddCustomizedLevelErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void AddCustomizedLevelErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void AddCustomizedLevelErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(AddCustomizedLevelErrPacket)

template<class Archive>
void CustomizedLevelPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _nameOfLevel;
}
template void CustomizedLevelPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void CustomizedLevelPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(CustomizedLevelPacket)

void CustomizedLevelPacket::execute (const PacketHandler& handler) const
{handler.getLevel(_nameOfLevel);}

template<class Archive>
void CustomizedLevelPacketAnswer::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _ennemyStack;
    ar & _levelName;
}
template void CustomizedLevelPacketAnswer::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void CustomizedLevelPacketAnswer::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(CustomizedLevelPacketAnswer)

template<class Archive>
void AddLikeToLevelPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _nameOfLevel;
    ar & _username;
}
template void AddLikeToLevelPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void AddLikeToLevelPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(AddLikeToLevelPacket)

void AddLikeToLevelPacket::execute (const PacketHandler& handler) const
{handler.addLikeToLevel(_nameOfLevel, _username);}

template<class Archive>
void AddLikeToLevelErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void AddLikeToLevelErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void AddLikeToLevelErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(AddLikeToLevelErrPacket)

template<class Archive>
void RemoveLikeFromLevelPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _nameOfLevel;
    ar & _username;
}
template void RemoveLikeFromLevelPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void RemoveLikeFromLevelPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(RemoveLikeFromLevelPacket)

void RemoveLikeFromLevelPacket::execute (const PacketHandler& handler) const
{handler.removeLikeFromLevel(_nameOfLevel, _username);}

template<class Archive>
void RemoveLikeFromLevelErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void RemoveLikeFromLevelErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void RemoveLikeFromLevelErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(RemoveLikeFromLevelErrPacket)

template<class Archive>
void NumberOfLikesQueryPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _nameOfLevel;
}
template void NumberOfLikesQueryPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void NumberOfLikesQueryPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(NumberOfLikesQueryPacket)

void NumberOfLikesQueryPacket::execute(const PacketHandler& handler) const {
    handler.getNumberOfLikesForLevel(_nameOfLevel);
}

template<class Archive>
void NumberOfLikesQueryPacketAnswer::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _nbrOfLikes;
}
template void NumberOfLikesQueryPacketAnswer::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void NumberOfLikesQueryPacketAnswer::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(NumberOfLikesQueryPacketAnswer)

template<class Archive>
void LevelPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _author;
    ar & _name;
    ar & _likes;
}
template void LevelPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void LevelPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(LevelPacket)

template<class Archive>
void FetchLevelsPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
}
template void FetchLevelsPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void FetchLevelsPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(FetchLevelsPacket)

void FetchLevelsPacket::execute(const PacketHandler& handler) const {
    handler.getAllLevels();
}

template<class Archive>
void FetchLevelsPacketAnswer::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _levels;
}
template void FetchLevelsPacketAnswer::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void FetchLevelsPacketAnswer::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(FetchLevelsPacketAnswer)

template<class Archive>
void FetchPlayableLevels::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
}
template void FetchPlayableLevels::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void FetchPlayableLevels::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(FetchPlayableLevels)

void FetchPlayableLevels::execute(const PacketHandler& handler) const {
    handler.getAllPlayableLevels();
}

template<class Archive>
void FetchPlayableLevelsAns::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _levels;
}
template void FetchPlayableLevelsAns::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void FetchPlayableLevelsAns::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(FetchPlayableLevelsAns)