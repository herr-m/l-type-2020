#include "WindowSFML.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

WindowSFML::WindowSFML() : window(sf::VideoMode(800, 600), "L-Type", sf::Style::Titlebar) {
    window.setVerticalSyncEnabled(false);
    cols = 800; rows = 600;
    font.loadFromFile("assets/font.ttf");

    // 0 | Player 1 Ship
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/p1_ship.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(35.f,35.f));

    // 1 | Player 2 Ship
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/p2_ship.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(35.f,35.f));

    // 2 | Logo
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/logo.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(256.f,48.f));

    // 3 | ally proj
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/enemy_prawn.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(8.f, 8.f));

    // 4 | enemy squid
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/enemy_squid.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(24.f, 24.f));

    // 5 | enemy prawn
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/enemy_prawn.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(24.f, 24.f));

    // 6 | enemy crab
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/enemy_crab.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(24.f, 24.f));

    // 7 | enemy green
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/enemy_green.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(24.f, 24.f));

    // 8 | TripleShotPUP
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/powerup.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(12.f, 12.f));

    // 9 | Hearth
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/powerup.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(8.f, 8.f));

    // 10 | bg star yellow
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/powerup.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(4.f, 4.f));

    // 11 | bg star blue
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/powerup_blue.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(4.f, 4.f));

    // 12 | bg star white
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/powerup_white.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(4.f, 4.f));

    // 13 | boss 1
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/Boss1.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(64.f, 64.f));

    // 14 | boss 2
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/Boss2.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(64.f, 64.f));

    // 15 | boss 3
    sprites.push_back(std::make_pair(std::make_unique<sf::RectangleShape>(), new sf::Texture()));
    sprites.back().second->loadFromFile("assets/Boss3.png");
    sprites.back().first->setTexture(sprites.back().second);
    sprites.back().first->setSize(sf::Vector2f(64.f, 64.f));
};

void WindowSFML::drawSprite(unsigned spriteID, float x, float y) {
    sf::FloatRect rect = sprites[spriteID].first->getLocalBounds();
    sprites[spriteID].first->setOrigin(rect.left + rect.width/2.0f,
               rect.top  + rect.height/2.0f);
    sprites[spriteID].first->setPosition(sf::Vector2f(x*0.01*getCols(), y*0.01*getRows()));
    window.draw(*sprites[spriteID].first);
}

void WindowSFML::drawText(std::string text, float x, float y, bool highlight) {
    sf::Text textObj(text, font);
    textObj.setCharacterSize(16);
    textObj.setFillColor(sf::Color::White);
    sf::FloatRect rect = textObj.getLocalBounds();
    textObj.setOrigin(rect.left + rect.width/2.0f,
               rect.top  + rect.height/2.0f);
    textObj.setPosition(sf::Vector2f(x*0.01*getCols(), y*0.01*getRows()));
    if(highlight) textObj.setStyle(sf::Text::Underlined);

    window.draw(textObj);
}

void WindowSFML::clear() {
    window.clear();
}

void WindowSFML::update() {
    sf::Event event;
    while (window.pollEvent(event)) {}
    window.display();
}

void WindowSFML::close() {
    window.close();
}
