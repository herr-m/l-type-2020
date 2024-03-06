#include <vector>
#include <cstddef> // std::size_t

#include "Game.hpp"
#include "Ennemies/Ships/AllEnnemyShips.hpp"
#include "Ennemies/Boss/AllEnnemyBoss.hpp"

// Private
void Game::updateScreenObjPos(const float elapsedTime) {
    for(const auto& obj : _screenState.ennemies) obj->updatePos(elapsedTime);
    for(const auto& obj : _screenState.ennemyProj) obj->updatePos(elapsedTime);
    for(const auto& obj : _screenState.friendProj) obj->updatePos(elapsedTime);
    for(const auto& obj : _screenState.powerUp) obj->updatePos(elapsedTime);
}

void Game::ennemiesShoot()
    {for(const auto& eObj : _screenState.ennemies) eObj->shootOnContainer(_screenState.ennemyProj);}

void Game::removeDeadEnnemy(){
    for(auto it = _screenState.ennemies.begin();
        it != _screenState.ennemies.end(); ++it){
            if((*it)->isDead()){
                if(shouldSpawnPowerUp()) spawnRandomPowerUpToPos((*it)->getPos());
                incScore(**it); _screenState.ennemies.erase(it--);
            }
    }
}

void Game::removeDeadFriend(){
    auto itIn = _inputHandlerCont.begin();
    for(auto it = _screenState.friends.begin(); it != _screenState.friends.end(); ++it)
        {if((*it)->isDead()){_screenState.friends.erase(it--); _inputHandlerCont.erase(itIn);}++itIn;}
}

void Game::updateFriendsPowerUP(const float elapsedTime) {
    for(const auto& ship : _screenState.friends){
        if(ship->hasPowerUp()){
            if(ship->hasInactivePowerUP()) ship->removeUsedPowerUP();
            else ship->increasePowerUPTimer(elapsedTime);
        }
    }
}

void Game::removeUsedPowerUp(){
    for(auto it = _screenState.powerUp.begin(); it != _screenState.powerUp.end(); ++it)
        if(!*it) _screenState.powerUp.erase(it--);
}

void Game::handleAllColisions(){
   ennemiesToFriendProjCollisions();
   friendsToEnnemiesCollisions();
   friendsToEnnemiesProjCollisions();
   if(_friendlyFire) friendsToFriendsProjCollisions();
}

void Game::friendsGetPowerUp() {
    for(const auto& ship : _screenState.friends){
        for(auto& pUp : _screenState.powerUp)
            if(pUp && ship->collideWith(*pUp)) ship->usePowerUP(pUp);
        }
}

void Game::incShootingDelay(const float elapsedTime){
   for(const auto& e : _screenState.ennemies) e->incShootingTimer(elapsedTime);
   for(const auto& f : _screenState.friends) f->incShootingTimer(elapsedTime);
}

EnnemyBaseAbstract* Game::translateAndSpawnEnnemy(const DataBaseSpawnDS& dSp){
    switch(dSp.ennemyID) {
        case 0: return ShipZigZacCorrect::makeToPos({dSp.xOffSet, _LIMY});
        case 1: return ShipZic::makeToPos({dSp.xOffSet, _LIMY});
        case 2: return ShipSinProjSin::makeToPos({dSp.xOffSet, _LIMY});
        case 3: return ShipZicProjSinShootingTripleShot::makeToPos({dSp.xOffSet, _LIMY});
        case 4: return BossBasic::makeToPos({dSp.xOffSet, _LIMY});
        case 5: return BossStaticSun::makeToPos({dSp.xOffSet, _LIMY});
        case 6: return BossOP::makeToPos({dSp.xOffSet, _LIMY});
    };
}  // warning OK should always return

//Public
Game::Game(bool fFire, unsigned nbrP, float dCoef, unsigned pUpChance, World world) noexcept :
    _friendlyFire(fFire), _nbrPlayer(nbrP), _powerUpChance(pUpChance), _dammageCoef(dCoef), _activeWorld(world){
    initInputHandlerCont(nbrP);
    SpawnFriendShips();
    //_activeWorld.addElement({4, 50, 50});
}

void Game::handleInput(const int input, const double elapsedTime){
    std::size_t i = 0;
    for(const auto& ship : _screenState.friends) (this->*_inputHandlerCont[i++])(input, *ship, elapsedTime);
}

void Game::updateScreenState(const float elapsedTime){
    if(_activeWorld.timeHasCome())
       _screenState.ennemies.emplace_back(translateAndSpawnEnnemy(_activeWorld.popAndReturnNext()));
    _activeWorld.worldMoveOn(elapsedTime);
    friendsGetPowerUp();
    removeUsedPowerUp();
    updateFriendsPowerUP(elapsedTime);
    incShootingDelay(elapsedTime);
    ennemiesShoot();
    updateScreenObjPos(elapsedTime);
    removeAllOffScreen();
    // check for live variation with  the player (this overhead allows to have a commun collision deteciton funciton)
    {std::vector<int> vectHp;
    for(const auto& e : _screenState.friends) vectHp.push_back(e->getNumberLives());
    handleAllColisions();
    std::size_t i=0;
    for(const auto& f : _screenState.friends)
        if(f->getNumberLives() < vectHp[i++]) {f->respawn(); dealDammageToAllEnnemiesOnLiveLost(*f);}}
    removeDeadEnnemy();
    removeDeadFriend();
}

std::list<ScreenObjSerialDS> Game::getScreenSerialized() const {
    std::list<ScreenObjSerialDS> res;
    for(const auto& obj : _screenState.ennemies) res.push_back(obj->getSerialize());
    for(const auto& obj : _screenState.ennemyProj) res.push_back(obj->getSerialize());
    for(const auto& obj : _screenState.friendProj) res.push_back(obj->getSerialize());
    for(const auto& obj : _screenState.powerUp) res.push_back(obj->getSerialize());
    for(const auto& obj : _screenState.friends) res.push_back(obj->getSerialize());
    return res;
}

const PointInSpaceDS Game::_friendsSpawnPos[MAX_NUM_PLAYER]{SPAWNP1, SPAWNP2};

PowerUpAbstract*(*const Game::_vectPowerUpSpawner[SARR])(const PointInSpaceDS&) // add all powerUp here and adjuste the size
{TripleShotPUP::makeToPos, TripleShotProjSinPUP::makeToPos, SunShotPUP::makeToPos,
        SunShotProjSinPUP::makeToPos, SpeedShipPUP::makeToPos, ProjSinPUP::makeToPos};
