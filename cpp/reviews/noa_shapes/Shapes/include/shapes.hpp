#ifndef __ILRD_8384_SHAPES_HPP__
#define __ILRD_8384_SHAPES_HPP__

#include "point.hpp"
#include "glut_utils.h"

namespace ilrd
{

class Shape
{
public:
    explicit Shape(
        COLORS color_ = COLOR_BLACK, 
        const Point& p_ = Point(0, 0),
        double angle_ = 0);
    virtual ~Shape();

    /* TODO: For inline functions, you should not put them in the function declaration, 
    but only for the function definition */
    inline const Point& GetPosition() const;
    inline Shape& SetPosition(const Point& point_);
    inline COLORS GetColor() const;
    inline Shape& SetColor(COLORS color_);
    inline double GetAngle() const;
    inline Shape& SetAngle(double angle_);
    Shape& Rotate(double angle_);
    Shape& Revolve(const Point& point_, double angle_);
    void Draw() const;

private:
    virtual void WhoAmI() const = 0; // Increment counter of call to Draw.
    virtual void DrawImp() const = 0;
    Point m_pos;
    COLORS m_color;
    double m_angle;
};


inline const Point& Shape::GetPosition() const
{
    return (m_pos);
}

inline Shape& Shape::SetPosition(const Point& point_)
{
    m_pos = point_;

    return (*this);
}

inline COLORS Shape::GetColor() const
{
    return (m_color);
}

inline Shape& Shape::SetColor(COLORS color_)
{
    m_color = color_;
    return (*this);
}

inline double Shape::GetAngle() const
{
    return (m_angle);
}

inline Shape& Shape::SetAngle(double angle_)
{
    m_angle = angle_;
    return (*this);
}

} // ilrd

#endif // ILRD_8384_Shape_HPP