#ifndef L_TYPE_DRAFT_WINDOWSFML_HPP
#define L_TYPE_DRAFT_WINDOWSFML_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "WindowAbstract.hpp"
#include <memory>
#include <map>

class WindowSFML : public WindowAbstract {
    sf::RenderWindow window;
    sf::Font font;
    std::vector<std::pair<std::unique_ptr<sf::RectangleShape>, sf::Texture*>> sprites;
public:
    WindowSFML();
    virtual ~WindowSFML() noexcept = default  ; 
    void drawSprite(unsigned, float, float) override;
    void drawText(std::string, float, float, bool = false) override;
    void clear() override;
    void update() override;
    void close() override;
};

#endif
