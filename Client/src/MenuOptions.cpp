#include "MenuOptions.hpp"
#include "Interface.hpp"
#include "Connection/Packet.hpp"
#include "Controller.hpp"
#include <string>

void MenuOptionAbstract::draw(std::unique_ptr<WindowAbstract>& window, int page, bool selected) const {
    if(_page == page) window->drawText(label, x, y, selected);
}

void TickOption::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) //enter
            tickedOn = !tickedOn;
}
void TickOption::draw(std::unique_ptr<WindowAbstract>& window, int page, bool selected) const {
    if(_page == page) window->drawText(label+(tickedOn?" : on":" : off"), x, y, selected);
}

void NumericalOption::increase() {
    value += step;
    if(value > maxValue)
        value = 0.f;
}
void NumericalOption::decrease() {
    value -= step;
    if(value < 0)
        value = maxValue;
}
void NumericalOption::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 71) // Left
            decrease();
        else if(key == 72) // Right
            increase();
}

void NumericalOption::draw(std::unique_ptr<WindowAbstract>& window, int page, bool selected) const {
    if(_page == page) window->drawText(label+" : "+std::to_string(value), x, y, selected);
}

void NewMenuOption::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) //enter
            *activeMenu = newMenu;
}

void TextOption::exec(std::vector<int> keys) {
    for(int key : keys) {
        if(key >= 0 && key <= 26) { // A - Z
            value += (char)(key + 65);
        }
        else if(key >= 26 && key <= 35) { // 0 - 9
            value += (char)(key + 22);
        }
        else if(key >= 75 && key <= 84) { // 0 - 9 (numpad)
            value += (char)(key - 27);
        }
        else if(key == 59 && value.size() > 0) // Backspace
            value.pop_back();
    }
}
void TextOption::draw(std::unique_ptr<WindowAbstract>& window, int page, bool selected) const {
    if(_page == page) window->drawText(label+" : "+value, x, y, selected);
}

void QuitOption::exec(std::vector<int> keys){
    for(int key : keys)
        if(key == 58) //enter
            Controller::state = QUIT;
            *status = true;
}

void LeveleditorOption::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) //enter
            Controller::state = LEVEL_EDITOR;
            *status = true;
}

void PlayOption::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) //enter
            Controller::state = GAME;
            *status = true;
}

Interface* SubmitOption::_interface = nullptr;
void SubmitOption::setInterfacePtr(Interface* interface) { _interface = interface;  };

void LoginOption::exec(std::vector<int> keys){
    for(int key : keys)
        if(key == 58) { // enter
            std::map<std::string, std::string> creds = _isGuest ? _interface->getMenuData("GUEST_LOGIN") : _interface->getMenuData("LOGIN");
            InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new LoginPacket(creds["Username"], creds["Password"], _isGuest)));
        }
}


void SignupOption::exec(std::vector<int> keys){
    for(int key : keys)
        if(key == 58) { // enter
            std::map<std::string, std::string> creds = _isGuest ? _interface->getMenuData("GUEST_LOGIN") :_interface->getMenuData("LOGIN");
            InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new SignupPacket(creds["Username"], creds["Password"], _isGuest)));
        }
}

void FriendListOption::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) { // enter
            InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new FriendListPacket(_interface->getLoggedUser())));
        }
}

void ScoreBoardOption::exec(std::vector<int> keys) {
   for(int key : keys)
        if(key == 58) { // enter
            InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new Top10QueryPacket()));
        } 
}

void AddFriendSubmit::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) { // enter
            InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new AddFriendPacket(_interface->getLoggedUser(), _interface->getMenuData("ADD_FRIEND")["Username"])));
        } 
}

void RemoveFriendSubmit::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) { // enter
            InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new RemoveFriendPacket(_interface->getLoggedUser(), _interface->getMenuData("REMOVE_FRIEND")["Username"])));
        } 
}

void LevelBrowserOption::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) { // enter
            InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new FetchLevelsPacket()));
        } 
}

void LikeLevelOption::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) { // enter
            InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new AddLikeToLevelPacket(_levelName, _interface->getLoggedUser())));
        } 
}

void LevelChoiceOrGuestLoginOption::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) { // 
            if(_interface->getMenuData("SETTINGS")["Multiplayer"] == "1")
                *activeMenu = "GUEST_LOGIN";
            else
                InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new FetchPlayableLevels()));
        } 
}

void PlayLevel::exec(std::vector<int> keys) {
    for(int key : keys)
        if(key == 58) { // enter
            InterfaceAbstract::connection.send(std::shared_ptr<PacketAbstract>(new CustomizedLevelPacket(_levelName)));
        } 
}