#include "square.hpp"

namespace ilrd
{

/* TODO: Same thing regarding the Point param that I mentioned in rectangle.cpp */
/* TODO: Also, why does Rectangle take in 2 Points, but Square takes in 1 Point and length?
Square is really just a more specific rectangle, so the two classes should be almost identical, 
and there's no reason for them to receive different types. I would even suggest making Square inherit
from Rectangle and you'll save almost all of the code in this class */
Square::Square(COLORS color_, Point lower_left_, double length_): Shape(color_), m_length(length_)
{
    /* TODO:  Same thing I said in rectangle.cpp */
    double x = lower_left_.GetX() + (m_length / 2);
    double y = lower_left_.GetY() + (m_length / 2);
    SetPosition(Point(x,y));
}

void Square::DrawImp() const
{
    double mid_x = GetPosition().GetX();
    double mid_y = GetPosition().GetY();
    double left_x = mid_x - (m_length / 2);
    double low_y = mid_y - (m_length / 2);
    double high_y = mid_y + (m_length / 2);
    double right_x = mid_x + (m_length / 2);

    Point p1(left_x, low_y);
    Point p2(left_x, high_y);
    Point p3(right_x, high_y);
    Point p4(right_x, low_y);

    p1.Revolve(GetPosition(), GetAngle());
    p2.Revolve(GetPosition(), GetAngle());
    p3.Revolve(GetPosition(), GetAngle());
    p4.Revolve(GetPosition(), GetAngle());

    int x1 = static_cast<int>(p1.GetX());
    int y1 = static_cast<int>(p1.GetY());
    int x2 = static_cast<int>(p2.GetX());
    int y2 = static_cast<int>(p2.GetY());
    int x3 = static_cast<int>(p3.GetX());
    int y3 = static_cast<int>(p3.GetY());
    int x4 = static_cast<int>(p4.GetX());
    int y4 = static_cast<int>(p4.GetY());

    /* same thing about the static const variable for number of points */
    DrawPolygon(GetColor(), 4, x1, y1, x2, y2, x3, y3, x4, y4);
}

void Square::WhoAmI() const
{
    static int counter = 0;
    ++counter;
} 

} // namespace ilrd