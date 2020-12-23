// puzzle1.cpp

#include <vector>
#include <iostream>

int next(std::vector<int>& memo, int last, int pos)
{
    auto const diff = (-1 == memo[last]) ? 0 : (pos - memo[last]);
    memo[last] = pos;
    return diff;
}

int main()
{
    // starting values
    std::vector<int> const vals{0, 20, 7, 16, 1, 18, 15};

    // simulation history
    std::vector<int> memo(2020, -1);
    for (auto i = 0UL; i < vals.size() - 1; ++i) 
    {
        memo[vals[i]] = static_cast<int>(i + 1);
    }

    auto last = vals.back();
    for (int pos = 7; pos < 2020; ++pos)
    {
        last = next(memo, last, pos);
    }

    std::cout << "2020th number spoken: " << last << std::endl;

    return EXIT_SUCCESS;
}