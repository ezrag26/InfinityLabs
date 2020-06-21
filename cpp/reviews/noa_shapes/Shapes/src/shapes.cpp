#include "shapes.hpp"


namespace ilrd
{

Shape::Shape(COLORS color_, const Point& p_, double angle_): m_pos(p_), m_color(color_), m_angle(angle_)
{}

Shape::~Shape()
{}


Shape& Shape::Rotate(double angle_)
{
    return (Revolve(m_pos, angle_));
}

void Shape::Draw() const
{
    WhoAmI();
    DrawImp();
}

Shape& Shape::Revolve(const Point& point_, double angle_)
{
    /* TODO: I think this misses the point about what Revolve is supposed to do...
    What you've done here is updated the shapes center and then rotated, but what revolve 
    means is that you want the shape's m_pos to circle --around-- point_ the specified
    amount in angle_, and rotate the shape the same amount */
    SetPosition(point_);
    SetAngle(angle_);

    return (*this);
}

} // namespace ilrd