#include "shapes.hpp"

namespace ilrd
{

class Circle : public Shape
{
public:
    explicit Circle(COLORS color_, Point p_, int radius_);

private:
    void WhoAmI() const; 
    void DrawImp() const;
    int m_radius;
};

} // namespace ilrd
