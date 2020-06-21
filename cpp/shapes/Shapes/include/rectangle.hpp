#ifndef FS_734_RECTANGLE_HPP
#define FS_734_RECTANGLE_HPP

#include <cmath>

#include "shapes.hpp"
namespace ilrd
{

class Rectangle : public Shape
{
public:
    explicit Rectangle(COLORS color_ = COLOR_BLACK, const Point& middle_ = Point(150, 150), double length_ = 20, double width_ = 10);
    virtual ~Rectangle();
private:
    double m_length;
    double m_width;

    virtual void DrawImpl() const;
    virtual void WhoAmI() const;

    static const int POINTS = 4;
};

} // ilrd

#endif /* FS_734_RECTANGLE_HPP */
