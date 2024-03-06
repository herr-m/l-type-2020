#include "InputHandler.hpp"

void InputHandler::update() {
    lastKeys.clear();
    std::copy(pressedKeys.begin(), pressedKeys.end(), back_inserter(lastKeys));
    pressedKeys.clear();

    for(sf::Keyboard::Key key : listenedKeys){
        if(sf::Keyboard::isKeyPressed(key)) {pressedKeys.push_back(key);}
    }
}

bool InputHandler::isKeyPressed(sf::Keyboard::Key key) const {
    return std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end();
}

bool InputHandler::keyJustPressed(sf::Keyboard::Key key) const {
    return std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end() && 
            std::find(lastKeys.begin(), lastKeys.end(), key) == lastKeys.end();
}

bool InputHandler::keyJustReleased(sf::Keyboard::Key key) const {
    return std::find(pressedKeys.begin(), pressedKeys.end(), key) == pressedKeys.end() && 
            std::find(lastKeys.begin(), lastKeys.end(), key) != lastKeys.end();
}

std::vector<sf::Keyboard::Key> InputHandler::getPressedKeys() const {
    return pressedKeys;
}

std::vector<sf::Keyboard::Key> InputHandler::getJustPressedKeys() const {
    std::vector<sf::Keyboard::Key> res;
    for(sf::Keyboard::Key key : listenedKeys)
        if(keyJustPressed(key)) res.push_back(key);

    return res;
}

std::vector<sf::Keyboard::Key> InputHandler::getJustReleasedKeys() const {
    std::vector<sf::Keyboard::Key> res;
    for(sf::Keyboard::Key key : listenedKeys)
        if(keyJustReleased(key)) res.push_back(key);

    return res;
}