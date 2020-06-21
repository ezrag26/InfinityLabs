#include "circle.hpp"

namespace ilrd
{
    Circle::Circle(COLORS color_, Point p_, int radius_)
        : Shape(color_, p_)
        , m_radius(radius_)
    {
    }

    void Circle::DrawImpl() const
    {
        WhoAmI();
        DrawCircle(GetColor(), (int)GetPosition().GetX(), (int)GetPosition().GetY(), m_radius);
    }

    void Circle::WhoAmI() const { ++m_times_called; }
    
} // ilrd
