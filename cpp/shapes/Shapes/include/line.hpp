#ifndef FS_734_LINE_HPP
#define FS_734_LINE_HPP

#include <cmath>

#include "shapes.hpp"

namespace ilrd
{

class Line : public Shape
{
public:
    explicit Line(COLORS color_ = COLOR_BLACK, const Point& vertex_ = Point(0, 0), double length_ = 20);

private:
    double m_length;

    virtual void DrawImpl() const;
    virtual void WhoAmI() const;
    
    static const int POINTS = 2;
    static double RIGHT_ANGLE;
};

} // ilrd

#endif /* FS_734_LINE_HPP */
