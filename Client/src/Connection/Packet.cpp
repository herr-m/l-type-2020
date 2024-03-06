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
BOOST_CLASS_EXPORT_IMPLEMENT(LoginPacket);

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

void LoginPacketAnswer::execute(const PacketHandler & handler) const
{
    handler.loginAns(_boolean, _username, _error, _isGuest);
}

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

void SignupPacketAnswer::execute(const PacketHandler & handler) const
{handler.signupAns(_boolean, _username, _isGuest);}

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

void FriendListPacketAnswer::execute(const PacketHandler & handler) const
{handler.friendListAns(_friends);}

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

template<class Archive>
void AddFriendErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void AddFriendErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void AddFriendErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(AddFriendErrPacket)

void AddFriendErrPacket::execute(const PacketHandler & handler) const
{handler.addFriendErr(_message);}

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

template<class Archive>
void RemoveFriendErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void RemoveFriendErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void RemoveFriendErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(RemoveFriendErrPacket)

void RemoveFriendErrPacket::execute(const PacketHandler & handler) const
{handler.removeFriendErr(_message);}

template<class Archive>
void DeleteFriendPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _username;
    ar & _userToDel;
}
template void DeleteFriendPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void DeleteFriendPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(DeleteFriendPacket)

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

template<class Archive>
void Top10QueryPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _username;
}
template void Top10QueryPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void Top10QueryPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(Top10QueryPacket)

template<class Archive>
void Top10QueryPacketAnswer::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _scoreboard;
}
template void Top10QueryPacketAnswer::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void Top10QueryPacketAnswer::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(Top10QueryPacketAnswer)

void Top10QueryPacketAnswer::execute(const PacketHandler & handler) const
{handler.top10Ans(_scoreboard);}

// Level
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

template<class Archive>
void AddCustomizedLevelErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void AddCustomizedLevelErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void AddCustomizedLevelErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(AddCustomizedLevelErrPacket)

void AddCustomizedLevelErrPacket::execute(const PacketHandler & handler) const
{handler.addCustomizedLevelErr(_message);}

template<class Archive>
void CustomizedLevelPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _nameOfLevel;
}
template void CustomizedLevelPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void CustomizedLevelPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(CustomizedLevelPacket)

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

void CustomizedLevelPacketAnswer::execute(const PacketHandler & handler) const
{handler.playLevel(_ennemyStack, _levelName);}

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


template<class Archive>
void AddLikeToLevelErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void AddLikeToLevelErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void AddLikeToLevelErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(AddLikeToLevelErrPacket)

void AddLikeToLevelErrPacket::execute(const PacketHandler & handler) const
{handler.addLikeToLevelErr(_message);}

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

template<class Archive>
void RemoveLikeFromLevelErrPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _message;
}
template void RemoveLikeFromLevelErrPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void RemoveLikeFromLevelErrPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(RemoveLikeFromLevelErrPacket)

void RemoveLikeFromLevelErrPacket::execute(const PacketHandler & handler) const
{handler.removeLikeFromLevelErr(_message);}

template<class Archive>
void NumberOfLikesQueryPacket::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _nameOfLevel;
}
template void NumberOfLikesQueryPacket::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void NumberOfLikesQueryPacket::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(NumberOfLikesQueryPacket)

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

template<class Archive>
void FetchLevelsPacketAnswer::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _levels;
}
template void FetchLevelsPacketAnswer::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void FetchLevelsPacketAnswer::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(FetchLevelsPacketAnswer)

void FetchLevelsPacketAnswer::execute(const PacketHandler & handler) const
{handler.displayLevels(_levels);}

template<class Archive>
void FetchPlayableLevels::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
}
template void FetchPlayableLevels::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void FetchPlayableLevels::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(FetchPlayableLevels)

template<class Archive>
void FetchPlayableLevelsAns::serialize(Archive & ar, const unsigned int version) 
{
    ar & boost::serialization::base_object<PacketAbstract>(*this);
    ar & _levels;
}
template void FetchPlayableLevelsAns::serialize(boost::archive::text_oarchive & ar, const unsigned int version);
template void FetchPlayableLevelsAns::serialize(boost::archive::text_iarchive & ar, const unsigned int version);
BOOST_CLASS_EXPORT_IMPLEMENT(FetchPlayableLevelsAns)

void FetchPlayableLevelsAns::execute(const PacketHandler & handler) const
{handler.displayLevelChoice(_levels);}