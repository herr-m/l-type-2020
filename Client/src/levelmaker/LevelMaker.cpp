#include "LevelMaker.hpp"
#include "../Controller.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

LevelMaker::LevelMaker(sf::RenderWindow &window, std::string author, int mapLength, int mapWidth, float scrollRatio, float scrollSpeed, int pixelPerSec, std::string fontPath)
    : _window(window), _currentEnnemi(1), _mapLength(mapLength), _mapWidth(mapWidth), _scrollRatio(scrollRatio), _scrollSpeed(scrollSpeed), _pixelPerSec(pixelPerSec), _save(false), _close(false), _levelNameString(""), _author(author)
{
    _font.loadFromFile(fontPath);
    initTextures();
    initEnnemiDraws();
    initViews();
    initEnnemiButtons();
    initSettingButtons();
    initScroll();
}

void LevelMaker::initTextures()
{
    _ennemiTexs[0].loadFromFile("assets/enemy_squid.png");
    _ennemiTexs[1].loadFromFile("assets/enemy_prawn.png");
    _ennemiTexs[2].loadFromFile("assets/enemy_crab.png");
    _ennemiTexs[3].loadFromFile("assets/enemy_green.png");
    _ennemiTexs[4].loadFromFile("assets/Boss1.png");
    _ennemiTexs[5].loadFromFile("assets/Boss2.png");
    _ennemiTexs[6].loadFromFile("assets/Boss3.png");
}

void LevelMaker::initEnnemiDraws()
{

    _ennemiDraws[0].setSize(sf::Vector2f(24, 24));
    _ennemiDraws[0].setTexture(&_ennemiTexs[0]);
    _ennemiDraws[0].setOrigin(12, 12);

    _ennemiDraws[1].setSize(sf::Vector2f(24, 24));
    _ennemiDraws[1].setTexture(&_ennemiTexs[1]);
    _ennemiDraws[1].setOrigin(12, 12);

    _ennemiDraws[2].setSize(sf::Vector2f(24, 24));
    _ennemiDraws[2].setTexture(&_ennemiTexs[2]);
    _ennemiDraws[2].setOrigin(12, 12);

    _ennemiDraws[3].setSize(sf::Vector2f(24, 24));
    _ennemiDraws[3].setTexture(&_ennemiTexs[3]);
    _ennemiDraws[3].setOrigin(12, 12);

    _ennemiDraws[4].setSize(sf::Vector2f(36, 36));
    _ennemiDraws[4].setTexture(&_ennemiTexs[4]);
    _ennemiDraws[4].setOrigin(18, 18);

    _ennemiDraws[5].setSize(sf::Vector2f(36, 36));
    _ennemiDraws[5].setTexture(&_ennemiTexs[5]);
    _ennemiDraws[5].setOrigin(18, 18);

    _ennemiDraws[6].setSize(sf::Vector2f(36, 36));
    _ennemiDraws[6].setTexture(&_ennemiTexs[6]);
    _ennemiDraws[6].setOrigin(18, 18);
}

void LevelMaker::initViews()
{
    _viewOptions.reset(sf::FloatRect(0.f, 0.f, _window.getSize().x, _window.getSize().y * (1 - _scrollRatio)));
    _viewOptions.setViewport(sf::FloatRect(0.f, _scrollRatio, 1.f, 1 - _scrollRatio));
    _viewScroll.reset(sf::FloatRect(0.f, 0.f, _window.getSize().x, _window.getSize().y));
    _viewScroll.setViewport(sf::FloatRect(0.f, 0.f, 1.f, _scrollRatio));
    _viewScroll.setCenter(_window.getSize().x / 2, _mapLength - _window.getSize().y / 2);
}

void LevelMaker::initEnnemiButtons()
{
    _ennemiButtons[0].setSize(sf::Vector2f(50, 40));
    _ennemiButtons[0].setTexture(&_ennemiTexs[0]);
    _ennemiButtons[0].setPosition(5.f, 5.f);

    _ennemiButtons[1].setSize(sf::Vector2f(50, 40));
    _ennemiButtons[1].setTexture(&_ennemiTexs[1]);
    _ennemiButtons[1].setPosition(65.f, 5.f);

    _ennemiButtons[2].setSize(sf::Vector2f(50, 40));
    _ennemiButtons[2].setTexture(&_ennemiTexs[2]);
    _ennemiButtons[2].setPosition(125.f, 5.f);

    _ennemiButtons[3].setSize(sf::Vector2f(50, 40));
    _ennemiButtons[3].setTexture(&_ennemiTexs[3]);
    _ennemiButtons[3].setPosition(185.f, 5.f);

    _ennemiButtons[4].setSize(sf::Vector2f(50, 40));
    _ennemiButtons[4].setFillColor(sf::Color::Red);
    _ennemiButtons[4].setTexture(&_ennemiTexs[4]);
    _ennemiButtons[4].setPosition(245.f, 5.f);

    _ennemiButtons[5].setSize(sf::Vector2f(50, 40));
    _ennemiButtons[5].setFillColor(sf::Color::Red);
    _ennemiButtons[5].setTexture(&_ennemiTexs[5]);
    _ennemiButtons[5].setPosition(305.f, 5.f);

    _ennemiButtons[6].setSize(sf::Vector2f(50, 40));
    _ennemiButtons[6].setFillColor(sf::Color::Red);
    _ennemiButtons[6].setTexture(&_ennemiTexs[6]);
    _ennemiButtons[6].setPosition(365.f, 5.f);
}

void LevelMaker::initSettingButtons()
{
    _saveText.setFont(_font);
    _saveText.setString("Save");
    _saveText.setCharacterSize(30);
    _saveText.setFillColor(sf::Color::White);
    _saveText.setPosition(600.f, 5.f);

    _closeText.setFont(_font);
    _closeText.setString("Close");
    _closeText.setCharacterSize(30);
    _closeText.setFillColor(sf::Color::Red);
    _closeText.setPosition(700.f, 5.f);

    _levelName.setFont(_font);
    _levelName.setString("Name: ");
    _levelName.setCharacterSize(18);
    _levelName.setFillColor(sf::Color::White);
    _levelName.setPosition(5.f, 65.f);

    _levelNameInput.setFont(_font);
    _levelNameInput.setCharacterSize(18);
    _levelNameInput.setFillColor(sf::Color::White);
    _levelNameInput.setPosition(70.f, 65.f);

    _infoText.setFont(_font);
    _infoText.setCharacterSize(18);
    _infoText.setFillColor(sf::Color::Red);
    _infoText.setPosition(500.f, 65.f);
}

void LevelMaker::initScroll()
{
    _scrollRTex.create(_mapWidth, _mapLength);
    _scrollRTex.clear(sf::Color::Black);
    drawScale();
    _scrollRTex.display();
    _scrollSprite.setTexture(_scrollTex);
}

void LevelMaker::draw()
{
    if (_window.isOpen())
    {
        _window.clear(sf::Color(126, 126, 126));
        //buttons
        _window.setView(_viewOptions);
        for (const auto &button : _ennemiButtons)
            _window.draw(button);
        _window.draw(_saveText);
        _window.draw(_closeText);
        _window.draw(_levelName);
        _window.draw(_levelNameInput);
        _window.draw(_infoText);
        //scrolling
        _window.setView(_viewScroll);
        _window.draw(_scrollSprite);

        _window.display();
    }
}

void LevelMaker::drawScroll()
{
    _window.setView(_viewScroll);
    _scrollRTex.clear(sf::Color::Black);
    for (int i = 0; i < _ennemies.size(); i++)
    {
        _ennemiDraws[_ennemies[i].id - 1].setPosition(_ennemies[i].xOffSet, _ennemies[i].triggerPos);
        _scrollRTex.draw(_ennemiDraws[_ennemies[i].id - 1]);
    }
    drawScale();
    _scrollRTex.display();
}

void LevelMaker::handleInput()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _window.close();
        else if (event.type == sf::Event::TextEntered)
            handleTextEntered(event.text.unicode);
        else if (event.type == sf::Event::KeyPressed)
            handleKey(event.key.code);
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i windowPos = sf::Mouse::getPosition(_window);
            if (windowPos.y < _window.getSize().y * _scrollRatio)
            {
                _window.setView(_viewScroll);
                handleScrollClick(_window.mapPixelToCoords(windowPos));
            }
            else
            {
                _window.setView(_viewOptions);
                handleOptionsClick(_window.mapPixelToCoords(windowPos));
            }
        }
    }
}

void LevelMaker::handleKey(const sf::Keyboard::Key &key)
{
    if (key == sf::Keyboard::Down)
    {
        _viewScroll.move(0.f, _scrollSpeed);
        if (_viewScroll.getCenter().y > _mapLength - _viewScroll.getSize().y / 2)
        {
            _viewScroll.setCenter(_viewScroll.getCenter().x, _mapLength - _viewScroll.getSize().y / 2);
        }
    }
    else if (key == sf::Keyboard::Up)
    {
        _viewScroll.move(0.f, 0 - _scrollSpeed);
        if (_viewScroll.getCenter().y < _viewScroll.getSize().y / 2)
        {
            _viewScroll.setCenter(_viewScroll.getCenter().x, _viewScroll.getSize().y / 2);
        }
    }
}

void LevelMaker::handleTextEntered(const int &unicode)
{
    if (unicode == '\b')
    {
        if (_levelNameString.size() > 0)
            _levelNameString.erase(_levelNameString.size() - 1, 1);
    }
    else if (unicode < 128)
    {
        _levelNameString += unicode;
    }

    _levelNameInput.setString(_levelNameString);
}

void LevelMaker::handleScrollClick(const sf::Vector2f &scrollPos)
{
    // verify collision
    bool draw = true;
    SpawnDS eToAdd{_currentEnnemi, scrollPos.y, scrollPos.x};
    for (int i = 0; i < _ennemies.size(); i++)
    {
        if (collision(_ennemies[i], eToAdd))
        { // no draw
            draw = false;
            if (contains(_ennemies[i], scrollPos.x, scrollPos.y))
            { // delete
                _ennemies.erase(_ennemies.begin() + i);
                drawScroll();
            }
            break;
        }
    }
    // add ennemi
    if (draw && isInsideMapLimit(eToAdd))
    {
        addEnnemi(eToAdd);
        drawScroll();
    }
}

void LevelMaker::handleOptionsClick(const sf::Vector2f &optionsPos)
{
    for (int i = 0; i < sizeof(_ennemiButtons) / sizeof(_ennemiButtons[0]); i++)
    {
        if (_ennemiButtons[i].getGlobalBounds().contains(optionsPos.x, optionsPos.y))
        {
            _currentEnnemi = i + 1;
        }
    }
    if (_saveText.getGlobalBounds().contains(optionsPos.x, optionsPos.y))
    {
        InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new AddCustomizedLevelPacket(_author, getLevelName(), getSortedList())));
        Controller::state = MAIN_MENU;
        _window.close();
        _save = true;
    }
    else if (_closeText.getGlobalBounds().contains(optionsPos.x, optionsPos.y))
    {
        Controller::state = MAIN_MENU;
        _window.close();
        _close = true;
    }
}

void LevelMaker::addEnnemi(const SpawnDS &e)
{
    _ennemies.push_back(e);
}

bool LevelMaker::collision(const SpawnDS &e1, const SpawnDS &e2) const
{
    return (abs(e1.xOffSet - e2.xOffSet) < abs(_ennemiDraws[e1.id - 1].getSize().x / 2 + _ennemiDraws[e2.id - 1].getSize().x / 2) && abs(e1.triggerPos - e2.triggerPos) < abs(_ennemiDraws[e1.id - 1].getSize().y / 2 + _ennemiDraws[e2.id - 1].getSize().y / 2)); // change y with minTimeInterval
}
bool LevelMaker::contains(const SpawnDS &ennemi, const float &x, const float &y) const
{
    return (abs(ennemi.xOffSet - x) < _ennemiDraws[ennemi.id - 1].getSize().x / 2 && abs(ennemi.triggerPos - y) < _ennemiDraws[ennemi.id - 1].getSize().y / 2);
}

bool LevelMaker::isInsideMapLimit(const SpawnDS &e) const
{
    return (e.xOffSet >= _ennemiDraws[e.id - 1].getSize().x / 2 && e.xOffSet < _mapWidth - (_ennemiDraws[e.id - 1].getSize().x / 2) && e.triggerPos >= _ennemiDraws[e.id - 1].getSize().y / 2 && e.triggerPos < _mapLength - (_ennemiDraws[e.id - 1].getSize().y / 2));
}

std::vector<EnnemyPacket> LevelMaker::getSortedList() const
{
    std::vector<EnnemyPacket> sorted;
    
    for(int i=0; i<_ennemies.size();i++) {
        sorted.push_back(EnnemyPacket(_ennemies[i].id-1, (_mapLength - _ennemies[i].triggerPos)/5, _ennemies[i].xOffSet / 8));
    }
    std::sort(sorted.begin(), sorted.end());
    return sorted;
}

std::string LevelMaker::getLevelName() const
{
    return _levelNameString;
}

void LevelMaker::setInfoText(const std::string &text)
{
    //_infoText.setString(text);
    std::cout << text << std::endl;
}

bool LevelMaker::isSaved() const
{
    return _save;
}

bool LevelMaker::isClosed() const
{
    return _close;
}

void LevelMaker::drawScale()
{
    _window.setView(_viewScroll);
    sf::Text text;
    text.setFont(_font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setOrigin(0.f, 10.f);
    std::string str;

    for (int i = 1; i < _mapLength / 500; i++)
    {
        str = "- " + std::to_string(_mapLength - 500 * i);
        text.setString(str);
        text.setPosition(0.f, 500.f * i);

        _scrollRTex.draw(text);
    }
}