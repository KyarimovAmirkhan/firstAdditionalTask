#include "SimpleRNG.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    SimpleRNG generator(5, 0.2, 1);
    generator.reset(0.4);

    std::vector<double> results;
    std::copy(generator.begin(), generator.end(0.5), std::back_inserter(results));

    generator.reset(0);
    for (auto value : generator)
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;

    return 0;
}
