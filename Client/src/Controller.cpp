#include "Controller.hpp"
#include "Game/World.hpp"
#include <string>

void Controller::start() {
    InterfaceAbstract::connection.connect();

    Interface* interface = new Interface(window);
    SubmitOption::setInterfacePtr(interface);

    GameDisplay* game = new GameDisplay(window);
    while (state != QUIT) {
        switch (state) {
            case MAIN_MENU: {
                interface->start();
                break;
            }
            case LEVEL_EDITOR: {
                sf::RenderWindow levelmakerWindow(sf::VideoMode(800, 600), "Level editor");
                LevelMaker level(levelmakerWindow, interface->getLoggedUser());
                while (levelmakerWindow.isOpen()) {
                    level.handleInput();
                    level.draw();
                }
                break;
            }
            case GAME: {
                std::map<std::string, std::string> gameSettings = interface->getMenuData("SETTINGS");
                game->start();
                break;
            }
        }
    }
    
    InterfaceAbstract::connection.disconnect();
    window->close();
}