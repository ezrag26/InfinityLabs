#include <cmath>    // sqrt, pow
#include "line.hpp"

namespace ilrd
{

Line::Line(COLORS color_, Point p_, double length_): Shape(color_, p_), m_length(length_)
{}

void Line::DrawImp() const
{
    int left_x = GetPosition().GetX() - (m_length / 2);
    int right_x = GetPosition().GetX() + (m_length / 2);
    int y = GetPosition().GetY();

    Point p1(left_x, y);
    Point p2(right_x, y);

    p1.Revolve(GetPosition(), GetAngle());
    p2.Revolve(GetPosition(), GetAngle());

    int x1 = static_cast<int>(p1.GetX());
    int y1 = static_cast<int>(p1.GetY());
    int x2 = static_cast<int>(p2.GetX());
    int y2 = static_cast<int>(p2.GetY());

    /*TODO: Maybe create a static const variable for the number of points instead of hardcoded to 2 */
    DrawPolygon(GetColor(), 2, x1, y1, x2, y2);
}

void Line::WhoAmI() const
{
    static int counter = 0;
    ++counter;
} 

} // namespace ilrd
