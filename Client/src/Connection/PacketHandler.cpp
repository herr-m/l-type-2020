#include "PacketHandler.hpp"
#include "Packet.hpp"
#include "Session.hpp"
#include <string>
#include <thread>
#include <chrono>
#include <exception>   
#include "../Interface.hpp"
#include "../levelmaker/LevelMaker.hpp"
#include "../GameDisplay.hpp"
#include "../Controller.hpp"

void PacketHandler::launch()
{
    while(_launched)
    {
    if (_queue.empty()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    else
    {_queue.front()-> execute(*this);
      _queue.pop();}
    }
}
void PacketHandler::stop() {
  _launched = false;
}

void PacketHandler::add(std::shared_ptr<PacketAbstract> to_add) 
{_queue.push(to_add);}

void PacketHandler::setInterfacePtr(Interface* inter) { _inter.reset(inter); }
void PacketHandler::setLevelMakerPtr(LevelMaker* levelmaker) { _levelmaker.reset(levelmaker); }
void PacketHandler::setGameDisplayPtr(GameDisplay* gameDisplay) { _gameDisplay.reset(gameDisplay); }

void PacketHandler::loginAns(const bool success, const std::string username, const std::string errMessage, bool isGuest) const {
  if(success) {
    if(isGuest) {
      _inter->setGuestUser(username); 
      InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new FetchPlayableLevels()));
    }
    else {
      _inter->setLoggedUser(username);
      _inter->setActiveMenu("MAIN");
    }
  }
  else {
    _inter->resetMenu(isGuest ? "GUEST_LOGIN" : "LOGIN");
    _inter->setPopUp(isGuest ? "GUEST_LOGIN" : "LOGIN", errMessage);
  }
}
void PacketHandler::signupAns(const bool success, const std::string username, bool isGuest) const {
  if(success) {
    if(isGuest) {
      _inter->setGuestUser(username);
      InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new FetchPlayableLevels()));
    }
    else {
      _inter->setLoggedUser(username);
      _inter->setActiveMenu("MAIN");
    }
  }
}

void PacketHandler::friendListAns(std::vector<std::string> friends) const {
  _inter->resetMenu("FRIENDLIST");
  _inter->setActiveMenu("FRIENDLIST");
  for(int i=0; i<friends.size(); ++i) {
    _inter->addMenuOption("FRIENDLIST", new DummyOption((35+i*5) % 100, 50, ((35+i*5)%100)+i*5, friends[i]));
  }
}

void PacketHandler::addFriendErr(std::string message) const {
  _inter->setPopUp("ADD_FRIEND", message);
}

void PacketHandler::removeFriendErr(std::string message) const {
  _inter->setPopUp("REMOVE_FRIEND", message);
}

void PacketHandler::top10Ans(std::vector<ScorePacket> scoreboard) const {
  _inter->resetMenu("SCOREBOARD");
  _inter->setActiveMenu("SCOREBOARD");
  for(int i=0; i<scoreboard.size(); ++i) {
    _inter->addMenuOption("SCOREBOARD", new DummyOption(std::floor((35+i*5)/100), 50, (35 + (i%13)*5), scoreboard[i].getUser()+" | Score: "+std::to_string(scoreboard[i].getScore())+" Level: "+scoreboard[i].getNameOfLevel()));
  }
}

void PacketHandler::addCustomizedLevelErr(std::string message) const {
}

void PacketHandler::addLikeToLevelErr(const std::string& message) const {
  _inter->setPopUp("LEVEL_BROWSER", message);
}

void PacketHandler::removeLikeFromLevelErr(std::string message) const {
}

void PacketHandler::displayLevels(std::vector<LevelPacket> levels) const {
  _inter->resetMenu("LEVEL_BROWSER");
  _inter->setActiveMenu("LEVEL_BROWSER");
  for(int i=0; i<levels.size(); ++i){
    _inter->addMenuOption("LEVEL_BROWSER", new LikeLevelOption(std::floor((35+i*5)/100), 50, (35 + (i%13)*5), levels[i].getName() + " by " + levels[i].getAuthor() + " | " + std::to_string(levels[i].getLikes()) + " likes", levels[i].getName(), false));
    }
}

void PacketHandler::displayLevelChoice(std::vector<LevelPacket> levels) const {
  _inter->resetMenu("LEVEL_CHOICE");
  _inter->setActiveMenu("LEVEL_CHOICE");
  for(int i=0; i<levels.size(); ++i)
    _inter->addMenuOption("LEVEL_CHOICE", new PlayLevel(std::floor((35+i*5)/100), 50, (35 + (i%13)*5), levels[i].getName() + " by " + levels[i].getAuthor() + " | " + std::to_string(levels[i].getLikes()) + " likes", levels[i].getName()));
}


void PacketHandler::playLevel(std::stack<EnnemyPacket> level, std::string levelName) const {
  // Algo rapide
  std::stack<DataBaseSpawnDS> temp;
  while(!level.empty()) {
    temp.push(DataBaseSpawnDS(level.top().getEnnemyId(), level.top().getTriggerPos(), level.top().getXOffSet()));
    level.pop();
  }

  std::stack<DataBaseSpawnDS> temp1;
  while(!temp.empty()) {
    temp1.push(temp.top());
    temp.pop();
  }

  std::map<std::string, std::string> gameSettings = _inter->getMenuData("SETTINGS");
  _gameDisplay->resetGame(_inter->getLoggedUser(), gameSettings["Multiplayer"] == "1"?_inter->getGuestUser():"", levelName, gameSettings["Friendly-fire"] == "1", gameSettings["Multiplayer"] == "1" ? 2 : 1, std::stof(gameSettings["Damage"]), std::stoi(gameSettings["Power-up chance"]), World(new std::stack<DataBaseSpawnDS>(temp1)));
  Controller::state = GAME;
  _inter->stop();
}