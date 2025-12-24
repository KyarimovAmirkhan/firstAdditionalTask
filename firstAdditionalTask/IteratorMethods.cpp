#include "SimpleRNG.h"
#include <cmath>

SimpleRNG::Iterator::Iterator()
: rngPtr(nullptr), epsilon(0.05), isEndFlag(true), cycleFound(false) {}

SimpleRNG::Iterator::Iterator(SimpleRNG* generator, double eps, bool endMarker)
: rngPtr(generator), epsilon(eps), isEndFlag(endMarker), cycleFound(false)
{
    bool notFinished = !isEndFlag;
    bool hasGenerator = rngPtr != nullptr;

    if (notFinished && hasGenerator)
    {
        currentVal = rngPtr->currentState;
        stateHistory.push_back(currentVal);
    }
}

bool SimpleRNG::Iterator::stateInHisory(double state, double eps) const
{
    bool found = false;

    for (size_t i = 0; i < stateHistory.size(); ++i)
    {
        double oldState = stateHistory[i];
        double diff = std::abs(state - oldState);
        bool isClose = diff < eps;

        if (isClose)
        {
            found = true;
            break;
        }
    }
    return found;
}

double SimpleRNG::Iterator::operator*() const
{
    return currentVal;
}

SimpleRNG::Iterator& SimpleRNG::Iterator::operator++()
{
    bool notFinished = !isEndFlag;
    bool hasGenerator = rngPtr != nullptr;

    if (notFinished && hasGenerator)
    {
        double nextVal = rngPtr->next();
        bool alreadySeen = stateInHisory(nextVal, epsilon);

        if (alreadySeen)
        {
            isEndFlag = true;
            cycleFound = true;
        }
        else
        {
            stateHistory.push_back(nextVal);
            currentVal = nextVal;
        }
    }
    return *this;
}

SimpleRNG::Iterator SimpleRNG::Iterator::operator++(int)
{
    Iterator oldState = *this;
    ++(*this);
    return oldState;
}

bool SimpleRNG::Iterator::operator==(const Iterator& other) const
{
    bool bothEnd = isEndFlag && other.isEndFlag;
    if (bothEnd)
    {
        return true;
    }

    bool differentEnd = isEndFlag != other.isEndFlag;
    if (differentEnd)
    {
        return false;
    }

    bool anyCycle = cycleFound || other.cycleFound;
    if (anyCycle)
    {
        return true;
    }

    double valDiff = std::abs(currentVal - other.currentVal);
    bool withinEps = valDiff < epsilon;
    return withinEps;
}

bool SimpleRNG::Iterator::operator!=(const Iterator& other) const
{
    return !(*this == other);
}