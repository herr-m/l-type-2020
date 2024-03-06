#include "Interface.hpp"
#include "Menu.hpp"
#include "MenuOptions.hpp"

Interface::Interface(WindowAbstract* window) : InterfaceAbstract(window, new InputHandler(std::vector<sf::Keyboard::Key>({
        sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Enter,
        sf::Keyboard::A, sf::Keyboard::B, sf::Keyboard::C, sf::Keyboard::D, sf::Keyboard::E, sf::Keyboard::F,
        sf::Keyboard::G, sf::Keyboard::H, sf::Keyboard::I, sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L,
        sf::Keyboard::M, sf::Keyboard::N, sf::Keyboard::O, sf::Keyboard::P, sf::Keyboard::Q, sf::Keyboard::R,
        sf::Keyboard::S, sf::Keyboard::T, sf::Keyboard::U, sf::Keyboard::V, sf::Keyboard::W, sf::Keyboard::X,
        sf::Keyboard::Y, sf::Keyboard::Z, sf::Keyboard::Num0, sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3,
        sf::Keyboard::Num4, sf::Keyboard::Num5, sf::Keyboard::Num6, sf::Keyboard::Num7, sf::Keyboard::Num8, sf::Keyboard::Num9,
        sf::Keyboard::Numpad0, sf::Keyboard::Numpad1, sf::Keyboard::Numpad2, sf::Keyboard::Numpad3, sf::Keyboard::Numpad4, sf::Keyboard::Numpad5,
        sf::Keyboard::Numpad6, sf::Keyboard::Numpad7, sf::Keyboard::Numpad8, sf::Keyboard::Numpad9, sf::Keyboard::LShift, sf::Keyboard::RShift,
        sf::Keyboard::Escape, sf::Keyboard::Backspace, sf::Keyboard::PageDown, sf::Keyboard::PageUp
    }))), activeMenu(new std::string("START")) {
    connection.setInterfacePtr(this);
    
    // Start screen
    menus["START"] = std::make_unique<Menu>("", 50, 20);
    menus["START"]->addOption(new NewMenuOption(0, 50, 22, "START", "LOGIN", activeMenu));

    // Login screen
    menus["LOGIN"] = std::make_unique<Menu>("AUTHENTICATION", 50, 20);
    menus["LOGIN"]->addOption(new TextOption(0, 50, 25, "Username", ""));
    menus["LOGIN"]->addOption(new TextOption(0, 50, 30, "Password", ""));
    menus["LOGIN"]->addOption(new LoginOption(0, 50, 40, "Login"));
    menus["LOGIN"]->addOption(new SignupOption(0, 50, 45, "Signup"));
    menus["LOGIN"]->addOption(new QuitOption(0, 50, 50, "Quit", &ended));

    // Guest login screen
    menus["GUEST_LOGIN"] = std::make_unique<Menu>("GUEST AUTHENTICATION", 50, 20);
    menus["GUEST_LOGIN"]->addOption(new TextOption(0, 50, 25, "Username", ""));
    menus["GUEST_LOGIN"]->addOption(new TextOption(0, 50, 30, "Password", ""));
    menus["GUEST_LOGIN"]->addOption(new LoginOption(0, 50, 40, "Login", true));
    menus["GUEST_LOGIN"]->addOption(new SignupOption(0, 50, 45, "Signup", true));
    menus["GUEST_LOGIN"]->addOption(new NewMenuOption(0, 50, 50, "Back", "SETTINGS", activeMenu));

    // Main menu
    menus["MAIN"] = std::make_unique<Menu>("MAIN MENU", 50, 20);
    menus["MAIN"]->addOption(new NewMenuOption(0, 50, 25, "Play", "SETTINGS", activeMenu));
    menus["MAIN"]->addOption(new NewMenuOption(0, 50, 30, "Social", "SOCIAL", activeMenu));
    menus["MAIN"]->addOption(new ScoreBoardOption(0, 50, 35, "Scoreboard"));
    menus["MAIN"]->addOption(new LeveleditorOption(0, 50, 40, "Level Editor", &ended));
    menus["MAIN"]->addOption(new LevelBrowserOption(0, 50, 45, "Level Browser"));
    menus["MAIN"]->addOption(new QuitOption(0, 50, 55, "Quit", &ended));
    
    // Settings menu
    menus["SETTINGS"] = std::make_unique<Menu>("SETTINGS", 50, 20);
    menus["SETTINGS"]->addOption(new TickOption(0, 50, 30, "Multiplayer", false));
    menus["SETTINGS"]->addOption(new NumericalOption(0, 50, 35, "Damage", 3.f, 1.f, 1.f));
    menus["SETTINGS"]->addOption(new TickOption(0, 50, 40, "Friendly-fire", false));
    menus["SETTINGS"]->addOption(new NumericalOption(0, 50, 45, "Power-up chance", 100.f, 5.f, 50.f));
    menus["SETTINGS"]->addOption(new LevelChoiceOrGuestLoginOption(0, 50, 55, "Play", activeMenu));
    menus["SETTINGS"]->addOption(new NewMenuOption(0, 50, 65, "Back", "MAIN", activeMenu));

    // Level browser
    menus["LEVEL_CHOICE"] = std::make_unique<Menu>("LEVELS", 50, 20);
    menus["LEVEL_CHOICE"]->addOption(new NewMenuOption(0, 50, 25, "Back", "SETTINGS", activeMenu));

    // Social Menu
    menus["SOCIAL"] = std::make_unique<Menu>("SOCIAL MENU", 50, 20);
    menus["SOCIAL"]->addOption(new NewMenuOption(0, 50, 25, "Back", "MAIN", activeMenu));
    menus["SOCIAL"]->addOption(new FriendListOption(0, 50, 35, "Friendlist"));
    menus["SOCIAL"]->addOption(new NewMenuOption(0, 50, 40, "Add friend", "ADD_FRIEND", activeMenu));
    menus["SOCIAL"]->addOption(new NewMenuOption(0, 50, 45, "Remove friend", "REMOVE_FRIEND", activeMenu));

    menus["ADD_FRIEND"] = std::make_unique<Menu>("ADD FRIEND", 50, 20);
    menus["ADD_FRIEND"]->addOption(new TextOption(0, 50, 25, "Username", ""));
    menus["ADD_FRIEND"]->addOption(new AddFriendSubmit(0, 50, 30, "Submit"));
    menus["ADD_FRIEND"]->addOption(new NewMenuOption(0, 50, 40, "Back", "SOCIAL", activeMenu));

    menus["REMOVE_FRIEND"] = std::make_unique<Menu>("REMOVE FRIEND", 50, 20);
    menus["REMOVE_FRIEND"]->addOption(new TextOption(0, 50, 25, "Username", ""));
    menus["REMOVE_FRIEND"]->addOption(new RemoveFriendSubmit(0, 50, 30, "Submit"));
    menus["REMOVE_FRIEND"]->addOption(new NewMenuOption(0, 50, 40, "Back", "SOCIAL", activeMenu));

    menus["FRIENDLIST"] = std::make_unique<Menu>("FRIENDLIST", 50, 20);
    menus["FRIENDLIST"]->addOption(new NewMenuOption(0, 50, 25, "Back", "SOCIAL", activeMenu));

    // Scoreboard
    menus["SCOREBOARD"] = std::make_unique<Menu>("SCOREBOARD", 50, 20);
    menus["SCOREBOARD"]->addOption(new NewMenuOption(0, 50, 25, "Back", "MAIN", activeMenu));

    // Level browser
    menus["LEVEL_BROWSER"] = std::make_unique<Menu>("LEVELS", 50, 20);
    menus["LEVEL_BROWSER"]->addOption(new NewMenuOption(0, 50, 25, "Back", "MAIN", activeMenu));
}

std::map<std::string, std::string> Interface::getMenuData(std::string menu){
    return menus[menu]->fetchData();
}

void Interface::handleInput() {
    inputHandler->update();
    std::vector<int> keyCodes;
    for(sf::Keyboard::Key key : inputHandler->getJustPressedKeys()) {
        keyCodes.push_back(key);
    }
    menus[*activeMenu]->execInput(keyCodes);
}

void Interface::update() {
    handleInput();

    // Update BG
    updateStars();
}

void Interface::render() {
    window->clear();

    // BG
    drawStars();

    window->drawSprite(2, 50, 10); // draw logo

    menus[*activeMenu]->draw(window);
    window->update();
}

void Interface::start() {
    ended = false;
    clock.restart().asSeconds();
    while(!ended) {
        dt = clock.restart().asSeconds();
        update();
        render();
    }
}

void Interface::addMenuOption(std::string menu, MenuOptionAbstract* option) {
    menus[menu]->addTemporaryOption(option);
}

void Interface::setPopUp(std::string menu, std::string message) {
    menus[menu]->setPopUp(message);
}

void Interface::resetMenu(std::string menu) {
    menus[menu]->reset();
}