#ifndef L_TYPE_DRAFT_WINDOW_HPP
#define L_TYPE_DRAFT_WINDOW_HPP

#include <string>
#include <vector>

class WindowAbstract {
protected:
    int rows, cols;
public:
    // Getters
    virtual int getRows() { return rows; }
    virtual int getCols() { return cols; }
    virtual  ~WindowAbstract() noexcept = default ;
    virtual void drawSprite(unsigned, float, float) = 0;
    virtual void drawText(std::string, float, float, bool = false) = 0;
    virtual void clear() = 0;
    virtual void update() = 0;
    virtual void close() = 0;
};

#endif //L_TYPE_DRAFT_WINDOW_HPP
