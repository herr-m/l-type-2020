#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include <stdlib.h> // rand
#include <time.h> // to randomize srand
#include <list>
#include <cstddef> // std::size_t

#include "GameObjContainerDS.hpp"
#include "Ennemies/EnnemyBaseAbstract.hpp"
#include "PowerUp/PowerUpAbstract.hpp"
#include "ScreenObjSerialDS.hpp"
#include "PointInSpaceDS.hpp"
#include "World.hpp"
#include "GameObjAbstract/DammageObjAbstract.hpp"
#include "FriendShips/BaseShip.hpp"
#include "GameObjAbstract/HealthObjAbstract.hpp"
#include "DataBaseSpawnDS.hpp"
#include "PowerUp/AllPowerUps.hpp"
#include "FriendShipInfoSerial.hpp"

constexpr const std::size_t SARR = 6; // size of powerUp array
constexpr const std::size_t MAX_NUM_PLAYER=2;
constexpr const double _SCREENW=100, _SCREENH=100, _LIMX=5, _LIMY=0;
constexpr const PointInSpaceDS SPAWNP1{_SCREENW/3, 2*_SCREENH/3}, SPAWNP2{2*_SCREENW/3, 2*_SCREENH/3};

class Game final{
    static const PointInSpaceDS _friendsSpawnPos[MAX_NUM_PLAYER];
    static PowerUpAbstract*(*const _vectPowerUpSpawner[SARR])(const PointInSpaceDS&); // add all powerUp here and adjuste the size

    const bool _friendlyFire;
    unsigned _score{};
    const unsigned _nbrPlayer, _powerUpChance;
    const float _dammageCoef;
    std::vector<void(Game::*)(int, FriendShipAbstract&, double)> _inputHandlerCont;
    World _activeWorld;
    GameObjContainerDS _screenState{};

    void incScore(const ScoreObjAbstract& obj) {_score += obj.getScore();}
    void updateScreenObjPos(const float);
    inline void ennemiesShoot();
    static EnnemyBaseAbstract* translateAndSpawnEnnemy(const DataBaseSpawnDS&);

    void initInputHandlerCont(const unsigned nbrP){
        _inputHandlerCont.emplace_back(&Game::handleInputPlayer<22, 18, 0, 3, 21>);
        if(nbrP==2) _inputHandlerCont.emplace_back(&Game::handleInputPlayer<8, 10, 9, 11, 13>);
    }

    template<typename T, typename U>// !!T should be a HealthObjAbstract and U a DammageObjAbstract (add concept if enough time)!!
    inline void healthCollideWithDammage
    (std::list<std::unique_ptr<T>>& healthList, std::list<std::unique_ptr<U>>& dammageList, const bool remove, const float coeff=1.f);

    void friendsToEnnemiesCollisions()
        {healthCollideWithDammage(_screenState.friends, _screenState.ennemies, false);}
    void ennemiesToFriendProjCollisions()
        {healthCollideWithDammage(_screenState.ennemies, _screenState.friendProj, true, _dammageCoef);}
    void friendsToEnnemiesProjCollisions()
        {healthCollideWithDammage(_screenState.friends, _screenState.ennemyProj, true);}
    void friendsToFriendsProjCollisions()
        {healthCollideWithDammage(_screenState.friends, _screenState.friendProj, true);}
    inline void friendsGetPowerUp();
    inline void handleAllColisions();

    inline void removeUsedPowerUp();
    inline void removeDeadEnnemy();
    inline void removeDeadFriend();

    inline void updateFriendsPowerUP(const float elapsedTime);

    static bool isOffScreen(const ScreenObjAbstract& obj)
       {const PointInSpaceDS p = obj.getPos(); return p.x < -_LIMX || p.x > _SCREENW+_LIMX || p.y < -_LIMY || p.y > _SCREENH+_LIMY;};

    template<typename T> // !! T should be a screen obj !!
    inline void removeOffScreen(std::list<std::unique_ptr<T>>& screenList);
    void removeAllOffScreen(){
        removeOffScreen(_screenState.ennemies);
        removeOffScreen(_screenState.ennemyProj);
        removeOffScreen(_screenState.friendProj);
        removeOffScreen(_screenState.powerUp);
    }

    bool shouldSpawnPowerUp() const {return rand()%100 < _powerUpChance;}
    void spawnRandomPowerUpToPos(const PointInSpaceDS& p)
       {_screenState.powerUp.emplace_back(_vectPowerUpSpawner[rand()%(SARR)](p));}

    void dealDammageToAllEnnemiesOnLiveLost(FriendShipAbstract& fShip)
        {for(const auto& e : _screenState.ennemies) e->takeDammageFrom(fShip, _dammageCoef);}

    template<int kUP, int kDown, int kLeft, int kRight, int kShoot>
    inline void handleInputPlayer(const int input, FriendShipAbstract& ship, const double);
    inline void incShootingDelay(const float elapsedTime);

    void SpawnFriendShips()
    {for(int i=0 ; i<_nbrPlayer; ++i)
            _screenState.friends.emplace_back(BaseShip::makeToPos(_friendsSpawnPos[i], i));} // change 1 with the appropriate sprite value, idealy the ships sprites would be 0 and 1
  public:
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;
    ~Game() = default;
    Game(bool, unsigned, float, unsigned, World) noexcept;
    Game() noexcept; // ctor for testing should be removed

    void updateScreenState(const float);
    void handleInput(const int, const double);
    std::list<ScreenObjSerialDS> getScreenSerialized() const;
    bool isGameOver() const {return _screenState.friends.size() == 0;}
    auto getGameScore() const {return _score;}
    bool isLevelOver() const
        {return _activeWorld.allSpawned() && _screenState.ennemies.size()==0;}
    std::list<FriendShipInfoSerial> getFriendsInfo() const {
        std::list<FriendShipInfoSerial> res;
        for(const auto& ship : _screenState.friends) res.emplace_front(ship->getShipInfo());
        return res;
    }

    static void initRandomSeed() {srand(static_cast<unsigned>(time(NULL)));}
};

template<int kUP, int kDown, int kLeft, int kRight, int kShoot>
void Game::handleInputPlayer(const int input, FriendShipAbstract& ship, const double elapsedTime){
    switch(input){
        case kUP: ship.moveUP(0, elapsedTime); return;
        case kDown: ship.moveDown(_SCREENH, elapsedTime); return;
        case kLeft: ship.moveLeft(0, elapsedTime); return;
        case kRight: ship.moveRight(_SCREENW, elapsedTime); return;
        case kShoot: ship.shootOnContainer(_screenState.friendProj); return;
    }
}

template<typename T, typename U>
void Game::healthCollideWithDammage
(std::list<std::unique_ptr<T>>& healthList, std::list<std::unique_ptr<U>>& dammageList, const bool remove, const float coeff){
    for(const auto& hpObj : healthList)
        for(auto it = dammageList.begin(); it != dammageList.end(); ++it){
            if(hpObj->collideWith(**it)){
                hpObj->takeDammageFrom(**it, coeff);
                if(remove) dammageList.erase(it--);
            }
        }
}

template<typename T>
void Game::removeOffScreen(std::list<std::unique_ptr<T>>& screenList){
    for(auto it = screenList.begin(); it != screenList.end(); ++it)
        if(isOffScreen(**it)) screenList.erase(it--);
}
#endif
