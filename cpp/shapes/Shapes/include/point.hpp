#ifndef SHAPES_POINT
#define SHAPES_POINT

#include <iosfwd>

namespace ilrd
{

class Point
{
public:
    explicit Point();
    explicit Point(double x, double y);
    //~Point() = default;
    //Point(const Point&) = default;
    //Point& operator=(const Point&) = default;


    // move the point to given coordinate
    Point& Move(double xNewLocation, double yNewLocation);

    Point& Revolve(const Point& pivot, double angle);

    Point& operator+=(const Point& other);
    Point& operator-=(const Point& other);
    Point& operator/=(double factor);
    Point& operator*=(double factor);

    inline const double& GetX() const;
    inline const double& GetY() const;

private:
    double m_x;
    double m_y;
};

Point operator+(const Point& point1, const Point& point2);
Point operator-(const Point& point1, const Point& point2);
Point operator*(const Point& point1, double factor);
Point operator/(const Point& point1, double factor);
bool operator!=(const Point& point1, const Point& point2);
bool operator==(const Point& point1, const Point& point2);

std::ostream& operator<<(std::ostream& os, const Point& point);


// add the values of steps to each point coordinate
inline void Step(Point* pointPtr, double xDelta, double yDelta)
{
    pointPtr->Move(pointPtr->GetX() + xDelta, pointPtr->GetY() + yDelta);
}

////////////////////////////////////////////////////////////////////////////////
///   inline functions implementation   ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

const double& Point::GetX() const
{
    return m_x;
}

const double& Point::GetY() const
{
    return m_y;
}

} //namespae ilrd

#endif // !SHAPES_POINT
