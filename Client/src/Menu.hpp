#ifndef L_TYPE_DRAFT_MENU_HPP
#define L_TYPE_DRAFT_MENU_HPP

#include <memory>
#include <string>
#include "MenuOptions.hpp"
#include "WindowNcurses.hpp"

class Menu {
    std::string label;
    int selected;
    int currentPage, maxPage;
    int x, y;

    std::vector<std::unique_ptr<MenuOptionAbstract>> options;
    std::vector<std::unique_ptr<MenuOptionAbstract>> tempOptions;
    std::string popupMessage;
public:
    virtual ~Menu() noexcept = default ;
    Menu(std::string label, int x, int y)
            : label(label), x(x), y(y), selected(0), currentPage(0), maxPage(0) {};
    void addOption(MenuOptionAbstract*);
    void addTemporaryOption(MenuOptionAbstract*);
    void setPopUp(std::string popUp) { popupMessage = popUp;};
    void execInput(std::vector<int>);
    void draw(std::unique_ptr<WindowAbstract>&) const;
    void reset();


    // client - server
    std::map<std::string, std::string> fetchData() const {
        std::map<std::string, std::string> res;
        for(const std::unique_ptr<MenuOptionAbstract>& option : options)
            res[option->getLabel()] = option->getData();
        
        for(const std::unique_ptr<MenuOptionAbstract>& option : tempOptions)
            res[option->getLabel()] = option->getData();

        return res;
    }
};

#endif //L_TYPE_DRAFT_MENU_HPP
