#ifndef FS_734_SQUARE_HPP
#define FS_734_SQUARE_HPP

#include <cmath>

#include "rectangle.hpp"

namespace ilrd
{

class Square : public Rectangle
{
public:
    explicit Square(COLORS color_ = COLOR_BLACK, const Point& middle_ = Point(150, 150), double side_ = 20);

private:
    virtual void WhoAmI() const;
};

} // ilrd

#endif /* FS_734_SQUARE_HPP */
