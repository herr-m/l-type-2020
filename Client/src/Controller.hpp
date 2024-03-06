#include "WindowSFML.hpp"
#include "WindowNcurses.hpp"
#include "GameDisplay.hpp"
#include "Interface.hpp"
#include "levelmaker/LevelMaker.hpp"

enum State{MAIN_MENU, LEVEL_EDITOR, GAME, QUIT};
class Controller {
    WindowAbstract* window;

    public:
        Controller(WindowAbstract* window) : window(window) {}
        static State state;
        void start();
};
