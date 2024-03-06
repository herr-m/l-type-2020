#ifndef LEVELMAKER_HPP_
#define LEVELMAKER_HPP_

#include <SFML/Graphics.hpp>
#include "../Game/Game.hpp"
#include "../Connection/Packet.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

struct SpawnDS final
{
    unsigned int id;
    float triggerPos;
    float xOffSet;
};

class LevelMaker
{
public:
    LevelMaker(sf::RenderWindow &window, std::string author, int mapLength = 6000, int mapWidth = 800, float scrollRatio = 0.85f, float scrollSpeed = 30.f, int pixelPerSec = 200, std::string fontPath = "assets/font.ttf");
    void draw();
    void handleInput();
    std::vector<EnnemyPacket> getSortedList() const;
    std::string getLevelName() const;
    void setInfoText(const std::string &text);

    bool isSaved() const;
    bool isClosed() const;

private:
    void initTextures();
    void initEnnemiDraws();
    void initViews();
    void initEnnemiButtons();
    void initSettingButtons();
    void initScroll();

    void drawScroll();

    void handleKey(const sf::Keyboard::Key &key);
    void handleTextEntered(const int &unicode);
    void handleScrollClick(const sf::Vector2f &viewPos);
    void handleOptionsClick(const sf::Vector2f &viewPos);

    void addEnnemi(const SpawnDS &e);

    bool collision(const SpawnDS &e1, const SpawnDS &e2) const;
    bool contains(const SpawnDS &ennemi, const float &x, const float &y) const;
    bool isInsideMapLimit(const SpawnDS &e) const;

    void drawScale();

    unsigned int _currentEnnemi;
    int _mapLength;
    int _mapWidth;
    float _scrollRatio;
    float _scrollSpeed;
    int _pixelPerSec;
    bool _save;
    bool _close;
    std::vector<SpawnDS> _ennemies;

    sf::RenderWindow &_window;

    sf::Font _font;

    sf::RectangleShape _ennemiDraws[7];
    sf::Texture _ennemiTexs[7];
    sf::RectangleShape _ennemiButtons[7];

    sf::Text _saveText;
    sf::Text _closeText;

    sf::Text _infoText;
    sf::Text _levelName;
    sf::Text _levelNameInput;
    std::string _levelNameString;

    sf::View _viewOptions;
    sf::View _viewScroll;

    sf::RenderTexture _scrollRTex;
    const sf::Texture &_scrollTex = _scrollRTex.getTexture();
    sf::Sprite _scrollSprite;

    std::string _author;
};

#endif