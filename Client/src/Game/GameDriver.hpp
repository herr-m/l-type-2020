#ifndef _GAMEDRIVER_H_
#define _GAMEDRIVER_H_

#include <memory>
#include <SFML/System.hpp>
#include "Game.hpp"

class GameDriver final {
    std::unique_ptr<Game> _game = nullptr;
    sf::Clock _dt{};
  public:
    void createGame(bool fFire, unsigned nbrP, float dCoef, unsigned pUpChance, World world)
        {_game.reset(new Game(fFire, nbrP, dCoef, pUpChance, world));}
    void runGame() {
        if(!_game) return;
        while(!_game->isGameOver() && !_game->isLevelOver()){
            _dt.restart().asSeconds();
      }
    }
};

#endif
