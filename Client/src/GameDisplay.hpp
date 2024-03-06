#ifndef L_TYPE_DRAFT_GAMEDISPLAY_HPP
#define L_TYPE_DRAFT_GAMEDISPLAY_HPP

#include "Game/FriendShipInfoSerial.hpp"
#include "InterfaceAbstract.hpp"
#include "Game/Game.hpp"
#include <memory>
#include <string>
#include <list>

class GameDisplay : public InterfaceAbstract {
    std::unique_ptr<Game> game;

    bool forceQuit;
    bool multiplayer;
    unsigned score;
    std::string _player1, _player2, _levelName;
    std::list<FriendShipInfoSerial> playersInfo;

    void displayGameOver(bool);
    
    void handleInput() override;
    void update() override;
    void render() override;
public:
    GameDisplay(WindowAbstract*);
    virtual ~GameDisplay() = default ;
    GameDisplay();

    void resetGame(std::string, std::string, std::string, bool, unsigned, float, unsigned, World);
    void start() override;
};

#endif //L_TYPE_DRAFT_GAMEDISPLAY_HPP
