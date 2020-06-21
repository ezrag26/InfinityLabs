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
    virtual ~Square() = default;
private:
    double m_side;
    
    virtual void DrawImpl() const;
    virtual void WhoAmI() const;
    
    static const int POINTS = 4;
};

} // ilrd

#endif /* FS_734_SQUARE_HPP */
