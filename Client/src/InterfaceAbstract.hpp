#ifndef L_TYPE_DRAFT_INTERFACEABSTRACT_HPP
#define L_TYPE_DRAFT_INTERFACEABSTRACT_HPP

#include "Connection/Connection.hpp"
#include "WindowNcurses.hpp"
#include "InputHandler.hpp"
#include "Connection/Connection.hpp"
#include <memory>

struct BgStar {
    int spriteID;
    float x, y, vel;

    void updatePos(const float& dt) {
        y += vel * dt;
        if(y > 100) y = 0;
    }
};

class InterfaceAbstract {
protected:
    std::unique_ptr<WindowAbstract> window;
    std::unique_ptr<InputHandler> inputHandler;
    sf::Clock clock;
    float dt;
    bool ended;
    std::array<BgStar, 100> stars;

    void updateStars() {
        for(BgStar& star : stars)
            star.updatePos(dt);
    }
    void drawStars() {
        for(const BgStar& star : stars)
            window->drawSprite(star.spriteID, star.x, star.y);
    }

    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
public:
    static Connection connection;
    InterfaceAbstract(WindowAbstract* window, InputHandler* inputHandler) :
        ended(false), window(window), inputHandler(inputHandler), dt(0.f) {
            srand(time(0));
            for(auto& star : stars)
                star = {rand()%3+10, static_cast<float>((rand()) % 100), static_cast<float>(rand() % 100), static_cast<float>(rand()%5) };
        }
    virtual void start() = 0;
    virtual ~InterfaceAbstract() = default ;
};
#endif //L_TYPE_DRAFT_INTERFACEABSTRACT_HPP
