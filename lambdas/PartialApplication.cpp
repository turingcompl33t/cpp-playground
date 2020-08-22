// PartialApplication.cpp
// Imitating Haskell's partial application facilities.

#include <vector>
#include <iostream>
#include <algorithm>

struct PredicateEquals
{
    PredicateEquals(int base) : m_Base(base) {}
    auto operator()(int test) -> bool
    {
        return test == m_Base;
    }

private:
    int m_Base;
};

auto make_predicate_equals_lambda(int n)
{
    return [base = n](int test) -> bool 
    { 
        return test == base; 
    };
}

auto make_predicate_equals_struct(int n)
{
    return PredicateEquals(n);
}

void test_lambda()
{
    std::cout << "\n*** Testing Lambda ***" << std::endl;

    auto pred_eq_two = make_predicate_equals_lambda(2);
    auto pred_eq_five = make_predicate_equals_lambda(5);

    std::vector<int> v {1, 2, 2, 4, 5, 5, 5};

    auto r1 = std::count_if(v.begin(), v.end(), pred_eq_two);
    auto r2 = std::count_if(v.begin(), v.end(), pred_eq_five);

    std::cout << "Vector contents: ";
    for (int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "# elements satisfying predicate (==2): " << r1 << std::endl;
    std::cout << "# elements satisfying predicate (==5): " << r2 << std::endl;
}

void test_struct()
{
    std::cout << "\n*** Testing Struct ***" << std::endl;

    auto pred_eq_two = make_predicate_equals_struct(2);
    auto pred_eq_five = make_predicate_equals_struct(5);

    std::vector<int> v {1, 2, 2, 4, 5, 5, 5};

    auto r1 = std::count_if(v.begin(), v.end(), pred_eq_two);
    auto r2 = std::count_if(v.begin(), v.end(), pred_eq_five);

    std::cout << "Vector contents: ";
    for (int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "# elements satisfying predicate (==2): " << r1 << std::endl;
    std::cout << "# elements satisfying predicate (==5): " << r2 << std::endl;
}

int main()
{
    test_lambda();
    test_struct();
}