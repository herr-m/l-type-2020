#ifndef L_TYPE_DRAFT_INTERFACE_HPP
#define L_TYPE_DRAFT_INTERFACE_HPP

#include "InterfaceAbstract.hpp"
#include "Menu.hpp"
#include <string>
#include <csignal>

class Interface : public InterfaceAbstract {
    std::map<std::string, std::unique_ptr<Menu>> menus;
    std::string* activeMenu;

    std::string _loggedUser;
    std::string _guestUser;

    void handleInput() override;
    void update() override;
    void render() override;
public:
    Interface(WindowAbstract* window);
    virtual ~Interface() = default ;
    void start() override;

    // Getters
    std::map<std::string, std::string> getMenuData(std::string);
    std::string getLoggedUser() { return _loggedUser;}
    std::string getGuestUser() { return _guestUser;}
    
    // Setters
    void setActiveMenu(std::string newMenu) { * activeMenu = newMenu; }
    void setLoggedUser(std::string loggerUser) { _loggedUser = loggerUser;}
    void setGuestUser(std::string guestUser) { _guestUser = guestUser;}
    void addMenuOption(std::string, MenuOptionAbstract*);
    void setPopUp(std::string, std::string);
    void resetMenu(std::string);
    void stop() {ended = true;}
};

#endif //L_TYPE_DRAFT_INTERFACE_HPP
