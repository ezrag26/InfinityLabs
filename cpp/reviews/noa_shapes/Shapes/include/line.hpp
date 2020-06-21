#include "shapes.hpp"

namespace ilrd
{

class Line : public Shape
{
public:
    explicit Line(COLORS color_, Point p_, double length_);

private:
    void WhoAmI() const; 
    void DrawImp() const;
    double m_length;
};

} // namespace ilrd

