#ifndef FS_734_SHAPES_HPP
#define FS_734_SHAPES_HPP

#include "glut_utils.h"
#include "point.hpp"
#include <iostream>

namespace ilrd
{

class Shape
{
public:
    explicit Shape(COLORS color_ = COLOR_BLACK, const Point& pos_ = Point(0, 0), double angle_ = 0.0);
    virtual ~Shape();
    void Draw() const;

    Shape& Rotate(double angle_);
    Shape& Revolve(const Point& point, double angle_);

    const Point& GetPosition() const;
    Shape& SetPosition(const Point& pos_);

    COLORS GetColor() const;
    Shape& SetColor(COLORS color_);

    double GetAngle() const;
    Shape& SetAngle(double angle_);

protected:
    mutable int m_times_called;

private:
    COLORS m_color;
    Point m_pos;
    double m_angle;
    
    virtual void DrawImpl() const = 0;
    virtual void WhoAmI() const = 0;
    
    static double full_circle_radians;
    static double UpdateAngle(double current, double to_add);
};

inline const Point& Shape::GetPosition() const { return m_pos; }

inline Shape& Shape::SetPosition(const Point& pos_)
{ 
    m_pos = pos_;

    return *this;
}

inline COLORS Shape::GetColor() const { return m_color; }

inline Shape& Shape::SetColor(COLORS color_)
{
    m_color = color_;

    return *this;
}

inline double Shape::GetAngle() const { return m_angle; }

inline Shape& Shape::SetAngle(double angle_)
{
    m_angle = angle_;

    return *this;
}

} // ilrd

#endif /* FS_734_SHAPES_HPP */
