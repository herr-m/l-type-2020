#include <csignal>
#include "InterfaceAbstract.hpp"
#include "Connection/Connection.hpp"
#include "Controller.hpp"
#include "WindowNcurses.hpp"

#include <SFML/Audio.hpp>

void sighandler(int sig)
{
    //fclose(stdin);
}

Connection InterfaceAbstract::connection = Connection();
State Controller::state = State::MAIN_MENU;
int main(int argc, char *argv[]) {
    sf::Music music;
    music.openFromFile("assets/music.ogg");
    music.play();

    //signal(SIGINT, sighandler);
    //signal(SIGTSTP, sighandler);

    WindowAbstract* window;
    if(argc > 1 && strcmp(argv[1], "SFML") == 0)
        window = new WindowSFML();
    else
        window = new WindowNcurses();

    Controller controller = Controller(window);
    controller.start();
    
    return 0;
}
