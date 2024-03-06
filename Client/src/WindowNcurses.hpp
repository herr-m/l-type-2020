#ifndef L_TYPE_DRAFT_WINDOWNCURSES_HPP
#define L_TYPE_DRAFT_WINDOWNCURSES_HPP

#include "WindowAbstract.hpp"
#include <ncurses.h>
#include <map>

struct SpriteNcurses {
    unsigned sizeY, sizeX, colour;
    std::string sprite;
    virtual ~SpriteNcurses() noexcept = default ;
    SpriteNcurses(unsigned sizeY, unsigned sizeX, std::string sprite, unsigned colour = 0) : sizeY(sizeY), sizeX(sizeX), sprite(sprite), colour(colour) {}
};

class WindowNcurses : public WindowAbstract {
    std::vector<SpriteNcurses*> sprites;
    void loadSprites();
public:
    WindowNcurses();
    virtual ~WindowNcurses() noexcept = default  ; 
    void drawChar(char, int, int);
    void drawSprite(unsigned, float, float) override;
    void drawText(std::string, float, float, bool = false) override;
    void clear() override;
    void update() override;
    void close() override;
};

#endif //L_TYPE_DRAFT_WINDOWNCURSES_HPP
