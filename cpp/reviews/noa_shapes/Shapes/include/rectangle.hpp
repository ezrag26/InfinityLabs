#include "shapes.hpp"

namespace ilrd
{

class Rectangle : public Shape
{
public:
    explicit Rectangle(COLORS color_, Point lower_left_, Point upper_right);

private:
    void WhoAmI() const; 
    void DrawImp() const;
    double m_width;
    double m_height;
};

} // namespace ilrd
