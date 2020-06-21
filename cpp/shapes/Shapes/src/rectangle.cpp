#include "rectangle.hpp"

namespace ilrd
{
    Rectangle::Rectangle(COLORS color_, const Point& middle_, double length_, double width_)
        : Shape(color_, middle_)
        , m_length(length_)
        , m_width(width_)
    {

    }

    Rectangle::~Rectangle() {}
    
    void Rectangle::DrawImpl() const
    {
        WhoAmI();

        double x = GetPosition().GetX();
        double y = GetPosition().GetY();

        double xDelta = m_length / 2;
        double yDelta = m_width / 2;
        
        double left_X = x - xDelta;
        double right_X = x + xDelta;
        double top_Y = y - yDelta;
        double bottom_Y = y + yDelta;

        Point top_left(left_X, top_Y);
        Point bottom_left(left_X, bottom_Y);
        Point bottom_right(right_X, bottom_Y);
        Point top_right(right_X, top_Y);

        top_left.Revolve(GetPosition(), GetAngle());
        bottom_left.Revolve(GetPosition(), GetAngle());
        bottom_right.Revolve(GetPosition(), GetAngle());
        top_right.Revolve(GetPosition(), GetAngle());

        DrawPolygon(GetColor(), POINTS, (int)top_left.GetX(), (int)top_left.GetY(),
                                        (int)bottom_left.GetX(), (int)bottom_left.GetY(), 
                                        (int)bottom_right.GetX(), (int)bottom_right.GetY(),
                                        (int)top_right.GetX(), (int)top_right.GetY());

    }

    void Rectangle::WhoAmI() const { ++m_times_called; }

} // ilrd
