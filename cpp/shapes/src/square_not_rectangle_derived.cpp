#include "square_not_rectangle_derived.hpp"

namespace ilrd
{
    Square::Square(COLORS color_, const Point& middle_, double side_)
        : Rectangle(color_, middle_, side_, side_)
        , m_side(side_)
    {

    }

    void Square::DrawImpl() const
    {
        WhoAmI();

        double delta = m_side / 2;

        double centerX = GetPosition().GetX();
        double centerY = GetPosition().GetY();
        
        double left_X = centerX - delta;
        double right_X = centerX + delta;

        double top_Y = centerY - delta;
        double bottom_Y = centerY + delta;

        Point p1(left_X, top_Y);
        Point p2(left_X, bottom_Y);
        Point p3(right_X, bottom_Y);
        Point p4(right_X, top_Y);

        p1.Revolve(GetPosition(), GetAngle());
        p2.Revolve(GetPosition(), GetAngle());
        p3.Revolve(GetPosition(), GetAngle());
        p4.Revolve(GetPosition(), GetAngle());

        DrawPolygon(GetColor(), POINTS, (int)p1.GetX(), (int)p1.GetY(),

                                        (int)p2.GetX(), (int)p2.GetY(), 

                                        (int)p3.GetX(), (int)p3.GetY(),

                                        (int)p4.GetX(), (int)p4.GetY());

    }

    void Square::WhoAmI() const
    {
        ++m_times_called;
    }
} // ilrd
