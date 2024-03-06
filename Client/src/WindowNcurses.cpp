#include "WindowNcurses.hpp"
#include <curses.h>

void WindowNcurses::loadSprites() {
    // sprites
    sprites.push_back(new SpriteNcurses(4, 8, "................................", 5)); // 0 | ally ship
    sprites.push_back(new SpriteNcurses(4, 8, "................................", 2)); // 1 | ally ship
    sprites.push_back(new SpriteNcurses(6, 32, " _        _____                 | |      |_   __   _ _ __   ___ | |   _____| || | | | '_ \\ / _ \\| |__|_____| || |_| | |_) |  __/|_____|    |_| \\__, | .__/ \\___|               |___/|_| gg wp    ", 2)); // 2 | logo
    sprites.push_back(new SpriteNcurses(2, 2, "oooo")); // 3 | ally proj
    sprites.push_back(new SpriteNcurses(3, 3, "xxxxxxxxx")); // 4 | enemy
    sprites.push_back(new SpriteNcurses(3, 3, "xxxx xxxx")); // 5 | enemy
    sprites.push_back(new SpriteNcurses(3, 3, " x xxx x ")); // 6 | enemy
    sprites.push_back(new SpriteNcurses(3, 3, "x x x x x")); // 7 | enemy
    sprites.push_back(new SpriteNcurses(1, 1, "@", 4)); // 8 | TripleShotPUP
    sprites.push_back(new SpriteNcurses(1, 1, "@", 1)); // 9 | Hearth

    sprites.push_back(new SpriteNcurses(1, 1, ".")); // 10 | Star white
    sprites.push_back(new SpriteNcurses(1, 1, ".", 3)); // 11  | Star blue
    sprites.push_back(new SpriteNcurses(1, 1, ".", 4)); // 12 | Star yellow

    sprites.push_back(new SpriteNcurses(5, 34, " __  __    _    ____    _    ___  |  \\/  |  / \\  / ___|  / \\  / _ \\ | |\\/| | / _ \\ \\___ \\ / _ \\| | | || |  | |/ ___ \\ ___) / ___ | |_| ||_|  |_/_/   \\_|____/_/   \\_\\___/ ", 1)); // 13 | Boss 1
    sprites.push_back(new SpriteNcurses(5, 44, " ____  _____ ____ _____ _   _   _ _   _____ / ___|| ____/ ___|  ___/ \\ | | | | | |_   _|\\___ \\|  _|| |  _| |_ / _ \\| | | | |   | |   ___) | |__| |_| |  _/ ___ | |_| | |___| | |____/|_____\\____|_|/_/   \\_\\___/|_____|_|", 4)); // 14 | Boss 2
    sprites.push_back(new SpriteNcurses(5, 19, "|  _ \\ / \\  |___ \\ | |_) / _ \\   __) ||  __/ ___ \\ / __/ |_| /_/   \\_|_____|    Core Dumped    ", 0)); // 15 | Boss 3
}

void WindowNcurses::drawChar(char c, int x, int y){
    mvwprintw(stdscr, y, x, "%c", c);
}

WindowNcurses::WindowNcurses() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    noecho();
    start_color();
    getmaxyx(stdscr, rows, cols);

    loadSprites();

    // Init colours
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
}

void WindowNcurses::drawSprite(unsigned spriteID, float x, float y){
    attron(COLOR_PAIR(sprites[spriteID]->colour));
    for(int i=0; i < sprites[spriteID]->sizeY; ++i){
        for(int j=0; j < sprites[spriteID]->sizeX; ++j){
            if(sprites[spriteID]->sprite[sprites[spriteID]->sizeX*i + j] != ' ')
                mvwprintw(stdscr, (y*0.01*getRows()+i) - sprites[spriteID]->sizeY*0.5, (x*0.01*getCols()+j) - sprites[spriteID]->sizeX*0.5, "%c", sprites[spriteID]->sprite[sprites[spriteID]->sizeX*i + j]);
        }
    }
    attroff(COLOR_PAIR(sprites[spriteID]->colour));
}

void WindowNcurses::drawText(std::string text, float x, float y, bool highlight){
    if(highlight) attron(A_BOLD);

    for(int i=0; i < text.length(); ++i)
        mvwprintw(stdscr, y*0.01*getRows(), (x*0.01*getCols()+i) - text.length()*0.5, "%c", text[i]);
    attrset(A_NORMAL);
}

void WindowNcurses::clear(){
    erase();
}

void WindowNcurses::update(){
    refresh();
}

void WindowNcurses::close(){
    endwin();
}