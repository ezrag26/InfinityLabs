#ifndef FS_734_CIRCLE_HPP
#define FS_734_CIRCLE_HPP

#include "shapes.hpp"

namespace ilrd
{

class Circle : public Shape
{
public:
    explicit Circle(COLORS color_ = COLOR_BLACK, Point p_ = Point(0, 0), int radius_ = 1);

private:
    int m_radius;

    virtual void DrawImpl() const;
    virtual void WhoAmI() const;
};

} // ilrd

#endif /* FS_734_CIRCLE_HPP */
