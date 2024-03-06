#ifndef L_TYPE_DRAFT_MENUOPTIONS_HPP
#define L_TYPE_DRAFT_MENUOPTIONS_HPP

#include <vector>
#include <string>
#include <memory>
#include "WindowNcurses.hpp"

class Interface;
class MenuOptionAbstract {
protected:
    std::string label;
    int x, y;
    int _page;
public:
    virtual ~MenuOptionAbstract() noexcept = default ;
    MenuOptionAbstract(int page, int x, int y, std::string label) : label(label), x(x), y(y), _page(page) {}
    std::string getLabel() const { return label;}
    int getPage() const { return _page; }
    virtual void exec(std::vector<int>) = 0;
    virtual void draw(std::unique_ptr<WindowAbstract>&, int, bool) const;

    virtual std::string getData() const { return "NA"; }
};
class DummyOption : public MenuOptionAbstract {
public:
    virtual ~DummyOption() noexcept = default ;
    DummyOption(int page, int x, int y, std::string label) : MenuOptionAbstract(page, x, y, label) {}
    void exec(std::vector<int>) override {};
};
class TickOption : public MenuOptionAbstract {
    bool tickedOn;
public:
    virtual ~TickOption() noexcept = default ;
    TickOption(int page, int x, int y, std::string label, bool on) : MenuOptionAbstract(page, x, y, label), tickedOn(on) {}
    void exec(std::vector<int>) override;
    void draw(std::unique_ptr<WindowAbstract>&, int, bool) const override;

    std::string getData() const override { return std::to_string(tickedOn); }
};
class NumericalOption : public MenuOptionAbstract {
    float value;
    float maxValue;
    float step;
public:
    virtual ~NumericalOption() noexcept = default ;
    NumericalOption(int page, int x, int y, std::string label, float maxValue, float step, float value) : MenuOptionAbstract(page, x, y, label), value(value), maxValue(maxValue), step(step) {}
    void increase();
    void decrease();
    void exec(std::vector<int>) override;
    void draw(std::unique_ptr<WindowAbstract>&, int, bool) const override;
    std::string getData() const override { return std::to_string(value); }
};
class NewMenuOption : public MenuOptionAbstract {
    std::string newMenu;
    std::string* activeMenu;
public:
    virtual ~NewMenuOption() noexcept = default ;
    NewMenuOption(int page, int x, int y, std::string label, std::string newMenu, std::string* activeMenu) : MenuOptionAbstract(page, x, y, label), newMenu(newMenu) {
        this->activeMenu = activeMenu;
    }
    void exec(std::vector<int>) override;
};
class TextOption : public MenuOptionAbstract {
    std::string value;
public:
    virtual ~TextOption() noexcept = default ;
    TextOption(int page, int x, int y, std::string label, std::string value) : MenuOptionAbstract(page, x, y, label), value(value) {}
    void exec(std::vector<int>) override;
    void draw(std::unique_ptr<WindowAbstract>&, int, bool) const override;

    std::string getData() const override { return value; }
};
class QuitOption : public MenuOptionAbstract {
    bool* status;
public:
  virtual ~QuitOption() noexcept = default ;
    QuitOption(int page, int x, int y, std::string label, bool* status) : MenuOptionAbstract(page, x, y, label), status(status) {}
    void exec(std::vector<int>) override;
};
class LeveleditorOption : public MenuOptionAbstract {
    bool* status;
public:
  virtual ~LeveleditorOption() noexcept = default ;
    LeveleditorOption(int page, int x, int y, std::string label, bool* status) : MenuOptionAbstract(page, x, y, label), status(status) {}
    void exec(std::vector<int>) override;
};
class PlayOption : public MenuOptionAbstract {
    bool* status;
    std::string _user;
public:
  virtual ~PlayOption() noexcept = default ;
    PlayOption(int page, int x, int y, std::string label, bool* status) : MenuOptionAbstract(page, x, y, label), status(status) {}
    void exec(std::vector<int>) override;
};

class SubmitOption : public MenuOptionAbstract {
public:
    static Interface* _interface;
    virtual ~SubmitOption()  noexcept = default ;
    SubmitOption(int page, int x, int y, std::string label) : MenuOptionAbstract(page, x, y, label) {}
    static void setInterfacePtr(Interface* interface);
};
class LoginOption : public SubmitOption {
    bool _isGuest;
public:
    virtual ~LoginOption() noexcept = default ;
    LoginOption(int page, int x, int y, std::string label, bool isGuest = false) : SubmitOption(page, x, y, label), _isGuest(isGuest) {}
    void exec(std::vector<int>) override;
};
class SignupOption : public SubmitOption {
    bool _isGuest;
public:
    virtual ~SignupOption() noexcept = default ;
    SignupOption(int page, int x, int y, std::string label, bool isGuest = false) : SubmitOption(page, x, y, label), _isGuest(isGuest) {}
    void exec(std::vector<int>) override;
};
class FriendListOption : public SubmitOption {
public:
    virtual ~FriendListOption() noexcept = default ;
    FriendListOption(int page, int x, int y, std::string label) : SubmitOption(page, x, y, label) {}
    void exec(std::vector<int>) override;
};
class ScoreBoardOption : public SubmitOption {
public:
    virtual ~ScoreBoardOption() noexcept = default ;
    ScoreBoardOption(int page, int x, int y, std::string label) : SubmitOption(page, x, y, label) {}
    void exec(std::vector<int>) override;
};
class AddFriendSubmit : public SubmitOption {
public:
    virtual ~AddFriendSubmit() noexcept = default ;
    AddFriendSubmit(int page, int x, int y, std::string label) : SubmitOption(page, x, y, label) {}
    void exec(std::vector<int>) override;
};
class RemoveFriendSubmit : public SubmitOption {
public:
    virtual ~RemoveFriendSubmit() noexcept = default ;
    RemoveFriendSubmit(int page, int x, int y, std::string label) : SubmitOption(page, x, y, label) {}
    void exec(std::vector<int>) override;
};
class LevelBrowserOption : public SubmitOption {
public:
    virtual ~LevelBrowserOption() noexcept = default ;
    LevelBrowserOption(int page, int x, int y, std::string label) : SubmitOption(page, x, y, label) {}
    void exec(std::vector<int>) override;
};
class LikeLevelOption : public SubmitOption {
    std::string _levelName;
    bool _liked;
public:
    virtual ~LikeLevelOption() noexcept = default ;
    LikeLevelOption(int page, int x, int y, std::string label, std::string levelName, bool liked) : SubmitOption(page, x, y, label), _levelName(levelName), _liked(liked) {}
    void exec(std::vector<int>) override;
};
class LevelChoiceOrGuestLoginOption : public SubmitOption {
    std::string* activeMenu;
public:
    virtual ~LevelChoiceOrGuestLoginOption() noexcept = default ;
    LevelChoiceOrGuestLoginOption(int page, int x, int y, std::string label, std::string* activeMenu) : SubmitOption(page, x, y, label), activeMenu(activeMenu) {}
    void exec(std::vector<int>) override;
};
class PlayLevel : public SubmitOption {
    std::string _levelName;
public:
    virtual ~PlayLevel() noexcept = default ;
    PlayLevel(int page, int x, int y, std::string label, std::string levelName) : SubmitOption(page, x, y, label),_levelName(levelName) {}
    void exec(std::vector<int>) override;
};

#endif
