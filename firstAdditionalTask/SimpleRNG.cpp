#include "SimpleRNG.h"
#include <cmath>
#include <stdexcept>

SimpleRNG::SimpleRNG(double m, double a, double c)
: modulus(m), multiplier(a), increment(c), currentState(0), initialState(0)
{
    if (m <= 1)
    {
        throw std::invalid_argument("m должно быть больше 1");
    }

    if (a <= 0 || a >= 1)
    {
        throw std::invalid_argument("c должно быть между 0 и 1 (не включая)");
    }

    if (c <= 0 || c >= m)
    {
        throw std::invalid_argument("c должно быть между 0 и m (не включая)");
    }
}

void SimpleRNG::reset(double seed)
{
    initialState = seed;
    currentState = seed;
}

void SimpleRNG::reset()
{
    currentState = initialState;
}

double SimpleRNG::next()
{
    double calcResult = multiplier * currentState + increment;
    double modResult = std::fmod(calcResult, modulus);
    currentState = modResult;
    return currentState;
}

SimpleRNG::Iterator SimpleRNG::begin()
{
    return Iterator(this);
}

SimpleRNG::Iterator SimpleRNG::end(double eps)
{
    return Iterator(nullptr, eps, true);
}

SimpleRNG::Iterator SimpleRNG::begin() const
{
    return const_cast<SimpleRNG*>(this)->begin();
}

SimpleRNG::Iterator SimpleRNG::end(double eps) const
{
    return const_cast<SimpleRNG*>(this)->end(eps);
}