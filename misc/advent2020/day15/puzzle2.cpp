// puzzle2.cpp

#include <vector>
#include <iostream>

constexpr static auto const LIMIT = 30'000'000;

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
    std::vector<int> memo(LIMIT, -1);
    for (auto i = 0UL; i < vals.size() - 1; ++i) 
    {
        memo[vals[i]] = static_cast<int>(i + 1);
    }

    auto last = vals.back();
    for (int pos = 7; pos < LIMIT; ++pos)
    {
        last = next(memo, last, pos);
    }

    std::cout << "30'000'000th number spoken: " << last << std::endl;

    return EXIT_SUCCESS;
}