#include <SFML/Window.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

class InputHandler {
    std::vector<sf::Keyboard::Key> listenedKeys;
    std::vector<sf::Keyboard::Key> pressedKeys;
    std::vector<sf::Keyboard::Key> lastKeys;
public:
    InputHandler(std::vector<sf::Keyboard::Key> listenedKeys) : listenedKeys(listenedKeys) {}
    virtual ~InputHandler() = default;
    void update();
    bool isKeyPressed(sf::Keyboard::Key) const;
    bool keyJustPressed(sf::Keyboard::Key) const;
    bool keyJustReleased(sf::Keyboard::Key) const;
    std::vector<sf::Keyboard::Key> getPressedKeys() const;
    std::vector<sf::Keyboard::Key> getJustPressedKeys() const;
    std::vector<sf::Keyboard::Key> getJustReleasedKeys() const;
};