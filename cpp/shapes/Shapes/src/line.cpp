#include <iostream>

#include "line.hpp"

namespace ilrd
{
    double Line::RIGHT_ANGLE = 90.0;

    Line::Line(COLORS color_, const Point& midpoint_, double length_)
        : Shape(color_, midpoint_, RIGHT_ANGLE)
        , m_length(length_)
    {
    }

    void Line::DrawImpl() const
    {
        WhoAmI();

        double x = GetPosition().GetX();
        double y = GetPosition().GetY();
        
        double delta = m_length / 2;

        Point p1(x - delta, y);
        Point p2(x + delta, y);

        p1.Revolve(GetPosition(), GetAngle());
        p2.Revolve(GetPosition(), GetAngle());

        DrawPolygon(GetColor(), POINTS, (int)p1.GetX(), (int)p1.GetY(),
                                        (int)p2.GetX(), (int)p2.GetY());

    }

    void Line::WhoAmI() const { ++m_times_called; }

} // ilrd
