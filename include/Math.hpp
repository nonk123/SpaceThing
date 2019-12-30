#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

namespace SpaceThing {
    template<typename T>
    T Pi = std::acos(T(-1));

    template<typename T>
    T Pi2 = Pi<T> * T(2);

    template<typename T>
    T HalfPi = Pi<T> / T(2);

    template<typename T>
    T RadToDeg = T(180) / Pi<T>;

    template<typename T>
    T DegToRad = Pi<T> / T(180);
}

#endif
