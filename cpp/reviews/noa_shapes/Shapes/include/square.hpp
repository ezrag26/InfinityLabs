#include "shapes.hpp"

namespace ilrd
{

class Square : public Shape
{
public:
    explicit Square(COLORS color_, Point lower_left_, double length_);

private:
    void WhoAmI() const; 
    void DrawImp() const;
    double m_length;
};

} // namespace ilrd
