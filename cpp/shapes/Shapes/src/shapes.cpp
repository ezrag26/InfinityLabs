#include <cmath>
#include "shapes.hpp"

namespace ilrd
{
    double Shape::full_circle_radians = 6.28319f;

    Shape::Shape(COLORS color_, const Point& pos_ , double angle_)
        : m_color(color_)
        , m_pos(pos_)
        , m_angle(angle_)
    {
    }
    
    Shape::~Shape() {}

    void Shape::Draw() const { DrawImpl(); }
    
    double Shape::UpdateAngle(double current, double to_add)
    {
        // to perform % operation on doubles
        return fmod(current + to_add, full_circle_radians);
    }

    Shape& Shape::Rotate(double angle_)
    {
        return SetAngle(UpdateAngle(m_angle, angle_));
        // return *this;
    }

    Shape& Shape::Revolve(const Point& point_, double angle_)
    {
        m_pos.Revolve(point_, angle_);

        return SetAngle(UpdateAngle(m_angle, angle_));

        // return *this;
    }

} // ilrd
