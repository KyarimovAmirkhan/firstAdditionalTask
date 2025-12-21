#ifndef SIMPLERNG_H
#define SIMPLERNG_H

#include <vector>

class SimpleRNG
{
private:
    double modulus;
    double multiplier;
    double increment;
    double currentState;
    double initialState;

    class Iterator
    {
    private:
        SimpleRNG* rngPtr;
        double currentVal;
        double epsilon;
        bool isEndFlag;
        bool cycleFound;

        std::vector<double> stateHistory;

        bool stateInHisory(double state, double eps) const;

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = double;
        using difference_type = std::ptrdiff_t;
        using pointer = double*;
        using reference = double&;

        Iterator();
        Iterator(SimpleRNG* generator, double eps = 0.05, bool endMarker = false);

        double operator*() const;
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

public:
    SimpleRNG(double m, double a, double c);

    void reset(double seed);
    void reset();

    double next();

    Iterator begin();
    Iterator end(double eps = 0.05);

    Iterator begin() const;
    Iterator end(double eps = 0.05) const;
};

#endif