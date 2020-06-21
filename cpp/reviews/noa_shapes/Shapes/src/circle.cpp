#include "circle.hpp"

namespace ilrd
{

Circle::Circle(COLORS color_, Point p_, int radius_): Shape(color_, p_), m_radius(radius_)
{} 

void Circle::DrawImp() const
{
    /*TODO: cast points to int */
    DrawCircle(GetColor(), GetPosition().GetX(), GetPosition().GetY(), m_radius);
}

void Circle::WhoAmI() const
{
    static int counter = 0;
    ++counter;
} 

} // namespace ilrd