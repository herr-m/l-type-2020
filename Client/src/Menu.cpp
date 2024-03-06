#include "Menu.hpp"
#include "MenuOptions.hpp"
#include <string>

void Menu::addOption(MenuOptionAbstract* option) {
    options.emplace_back(option);
}
void Menu::addTemporaryOption(MenuOptionAbstract* option) {
    if(option->getPage() > maxPage) maxPage = option->getPage();
    tempOptions.emplace_back(option);
}

#include <iostream>
void Menu::execInput(std::vector<int> keys) {
    for(int key : keys) {
        switch(key) {
            case 73: // Up
                --selected; break;
            case 74: // Down
                ++selected; break;
            default: {
                if(selected > options.size()-1)
                    tempOptions[selected - options.size()]->exec(keys);
                else
                    options[selected]->exec(keys);

                break;
            }
        }
    }

    if(selected < 0) selected = options.size() + tempOptions.size() - 1;
    else if(selected > options.size() + tempOptions.size() - 1) selected = 0;

    if(selected > options.size()-1)
        currentPage = tempOptions[selected - options.size()]->getPage();
    else
        currentPage = options[selected]->getPage();
}

void Menu::draw(std::unique_ptr<WindowAbstract>& window) const {
    window->drawText(label, x, y, false);
    for(const std::unique_ptr<MenuOptionAbstract>& option : options)
        option->draw(window, currentPage, false);

    if(!tempOptions.empty())
        for(const std::unique_ptr<MenuOptionAbstract>& option : tempOptions)
            option->draw(window, currentPage, false);

    if(selected > options.size()-1)
        tempOptions[selected - options.size()]->draw(window, currentPage, true);
    else
        options[selected]->draw(window, currentPage, true);

    window->drawText(popupMessage, x, y+2);
}

void Menu::reset() {
    tempOptions.clear();
    setPopUp("");
}
