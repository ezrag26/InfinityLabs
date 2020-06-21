#include "rectangle.hpp"


namespace ilrd
{

/*TODO: Why not allow the Point params to be const Point& */
Rectangle::Rectangle(COLORS color_, Point lower_left_, Point upper_right): Shape(color_)
{
    /* TODO: If you look at point.hpp, 2 Points can be added, and you can use the / operator on a point.
    You can save all this code and leave to Point's API to take care of it by doing: ((lower_left_ + upper_right) / 2), 
    and send this to Shape's ctor in the initialization list instead of using SetPosition() */
    m_height = upper_right.GetY() - lower_left_.GetY();
    m_width = upper_right.GetX() - lower_left_.GetX();
    
    double x = (lower_left_.GetX() + upper_right.GetX()) / 2;
    double y = (lower_left_.GetY() + upper_right.GetY()) / 2;
    SetPosition(Point(x,y));
}

void Rectangle::DrawImp() const
{
    double mid_x = GetPosition().GetX();
    double mid_y = GetPosition().GetY();
    double left_x = mid_x - (m_width / 2);
    double low_y = mid_y - (m_height / 2);
    double high_y = mid_y + (m_height / 2);
    double right_x = mid_x + (m_width / 2);

    Point p1(left_x, low_y);
    Point p2(left_x, high_y);
    Point p3(right_x, high_y);
    Point p4(right_x, low_y);

    p1.Revolve(GetPosition(), GetAngle());
    p2.Revolve(GetPosition(), GetAngle());
    p3.Revolve(GetPosition(), GetAngle());
    p4.Revolve(GetPosition(), GetAngle());

    int x1 = static_cast<int>(p1.GetX());
    int y1 = static_cast<int>(p1.GetY());
    int x2 = static_cast<int>(p2.GetX());
    int y2 = static_cast<int>(p2.GetY());
    int x3 = static_cast<int>(p3.GetX());
    int y3 = static_cast<int>(p3.GetY());
    int x4 = static_cast<int>(p4.GetX());
    int y4 = static_cast<int>(p4.GetY());

    /*TODO: Maybe create a static const variable for the number of points instead of hardcoded to 4 */
    DrawPolygon(GetColor(), 4, x1, y1, x2, y2, x3, y3, x4, y4);
}

void Rectangle::WhoAmI() const
{
    static int counter = 0;
    ++counter;
} 

} // namespace ilrd