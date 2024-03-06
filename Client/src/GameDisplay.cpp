#include "GameDisplay.hpp"
#include "Controller.hpp"
#include "Game/Game.hpp"
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <random>

GameDisplay::GameDisplay(WindowAbstract* window) : InterfaceAbstract(window, new InputHandler(std::vector<sf::Keyboard::Key>({
    sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::V,
    sf::Keyboard::I, sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L, sf::Keyboard::N, sf::Keyboard::Escape
}))), forceQuit(false), multiplayer(false), score(0) {
    InterfaceAbstract::connection.setGameDisplayPtr(this);
    
    Game::initRandomSeed();
}

void GameDisplay::handleInput() {
    inputHandler->update();
    if(inputHandler->keyJustPressed(sf::Keyboard::Escape)) forceQuit = true;

    for(sf::Keyboard::Key key : inputHandler->getPressedKeys()){
        game->handleInput(key, dt);
    }
}

void GameDisplay::update() {
    handleInput();

    // Update BG
    updateStars();

    // Update HUD
    score = game->getGameScore();
    playersInfo = game->getFriendsInfo();

    // Update game
    game->updateScreenState(dt);
}

void GameDisplay::render() {
    window->clear();

    // BG
    drawStars();

    // HUD
    for(const auto& e : playersInfo){
        if (e.playerID == 0) {
            window->drawText("Player 1", 5.f, 90.f);
            window->drawText("Health: " + std::to_string(e.hp), 7.f, 93.f);
            window->drawText("Lives: ", 5.f, 96.f);
            for(int i=0; i<e.numLives; ++i) window->drawSprite(9, 10.f + 5*i, 96.f);
        }

        else {
            window->drawText("Player 2", 80.f, 90.f);
            window->drawText("Health: " + std::to_string(e.hp), 80.f, 93.f);
            window->drawText("Lives: ", 80.f, 96.f);
            for(int i=0; i<e.numLives; ++i) window->drawSprite(9, 85.f + 5*i, 96.f);
        }
    }

    window->drawText(std::to_string(score), 50.f, 96.f);
    
    // Game
    for(const ScreenObjSerialDS& go : game->getScreenSerialized()) {
        window->drawSprite(go.spriteID, go.x, go.y);
    }

    window->update();
}

void GameDisplay::resetGame(std::string player1, std::string player2, std::string levelName, bool fFire, unsigned nbrP, float dCoef, unsigned pUpChance, World world) {
    _player1 = player1; _player2 = player2; _levelName = levelName; forceQuit = false;
    if(nbrP > 1) multiplayer = true;
    game.reset(new Game(fFire, nbrP, dCoef, pUpChance, world));
}

void GameDisplay::displayGameOver(bool levelComplete) {
    window->clear();
    levelComplete ? window->drawText("LEVEL OVER", 50.f, 45.f) : window->drawText("GAME OVER", 50.f, 45.f);
    window->drawText(std::to_string(score), 50.f, 55.f);
    window->update();
    sleep(4);
}

void GameDisplay::start() {
    clock.restart().asSeconds();
    while(!game->isGameOver() && !game->isLevelOver() && !forceQuit) {
        dt = clock.restart().asSeconds();
        
        update();
        render();
    }
    score = game->getGameScore();
    displayGameOver(game->isLevelOver());

    if(game->isLevelOver()) {
        connection.send(std::shared_ptr<PacketAbstract>(new ScorePacket(_player1, _levelName, score)));
        sleep(1);
        if(multiplayer) connection.send(std::shared_ptr<PacketAbstract>(new ScorePacket(_player2, _levelName, score)));
    }
        
    Controller::state = MAIN_MENU;
}
