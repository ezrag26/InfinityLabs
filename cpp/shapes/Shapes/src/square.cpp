#include "square.hpp"

namespace ilrd
{
    Square::Square(COLORS color_, const Point& middle_, double side_)
        : Rectangle(color_, middle_, side_, side_)
    {
    }

    void Square::WhoAmI() const { ++m_times_called; }

} // ilrd
