#ifndef _FS_734_COMPLEX_IMPL_HPP_
#define _FS_734_COMPLEX_IMPL_HPP_

#include <cmath>    // fabs
#include <iostream> // iostream, ostream

#include "complex.hpp"

namespace ilrd
{

static const double EPSILON = 0.0000001f; // for operator==()

Complex::Complex(double real_, double imag_)
    : m_real(real_)
    , m_imag(imag_) {}

inline Complex& Complex::operator+=(const Complex& comp_)
{
    m_real += comp_.m_real;
    m_imag += comp_.m_imag;

    return *this;
}

inline Complex& Complex::operator-=(const Complex& comp_)
{
    m_real -= comp_.m_real;
    m_imag -= comp_.m_imag;

    return *this;
}

inline Complex& Complex::operator*=(const Complex& comp_)
{
    // complex number multiplication -> (a + bi)*(A + Bi) -> a*A + aBi + bAi + bB(i^2)
    // i^2 = -1

    double real = m_real * comp_.m_real;
    double left_imag = m_imag * comp_.m_real;
    double right_imag = m_real * comp_.m_imag;
    double i_2 = m_imag * comp_.m_imag;
    
    m_real = real - i_2;
    m_imag = left_imag + right_imag;

    return *this;
}

inline Complex& Complex::operator/=(const Complex& comp_)
{
    (void)comp_; // unused
    m_real = 7;
    m_imag = 7;

    return *this;
}

inline void Complex::SetReal(const double real_) { m_real = real_; }

inline void Complex::SetImaginary(const double imag_) { m_imag = imag_; }

inline double Complex::GetReal() const { return m_real; }

inline double Complex::GetImaginary() const { return m_imag; }

inline const Complex operator+(const Complex& comp1_, const Complex& comp2_)
{
    return Complex(comp1_) += comp2_;
}

inline const Complex operator-(const Complex& comp1_, const Complex& comp2_)
{
    return Complex(comp1_) -= comp2_;
}

inline const Complex operator*(const Complex& comp1_, const Complex& comp2_)
{
    return Complex(comp1_) *= comp2_;
}

inline const Complex operator/(const Complex& comp1_, const Complex& comp2_)
{
    // Complex conjugate(comp2_.GetReal, comp2_.GetImaginary * -1);
    // Complex numerator = comp1_ * conjugate;
    // Complex denomenator = comp2_.GetReal() * comp2_.GetReal() + comp2_.GetImaginary() * comp2_.GetImaginary();

    return Complex(comp1_) /= comp2_;
}

inline bool operator==(const Complex& comp1_, const Complex& comp2_)
{
    // both reals are the same and both imaginaries are the same
    return (fabs(comp1_.GetReal() - comp2_.GetReal()) < EPSILON &&
            fabs(comp1_.GetImaginary() - comp2_.GetImaginary()) < EPSILON);
}

inline bool operator!=(const Complex& comp1_, const Complex& comp2_)
{
    return !(comp1_ == comp2_);
}

inline std::ostream& operator<<(std::ostream& os_, const Complex& comp_)
{
    double imag = comp_.GetImaginary();
    
    os_ << comp_.GetReal();
    
    // for asthetic purposes
    if (imag >= 0) os_ << " + " << imag;
    else os_ << " - " << -imag;
    
    os_ << "i";

    return os_; // return ostream so we can chain calls to operator<<
}

inline std::istream& operator>>(std::istream& is_, Complex& comp_)
{
    double real;
    double imag;

    is_ >> real; // get real number
    is_ >> imag; // get imaginary number

    comp_.SetReal(real);
    comp_.SetImaginary(imag);
    
    return is_;
}

} // ilrd

#endif // _FS_734_COMPLEX_IMPL_HPP_
