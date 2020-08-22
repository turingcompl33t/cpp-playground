// HigherOrder.cpp
// Higher-order functions "hello world"

#include <iostream>

int f(int n)
{
    return n * 5;
}

int g()
{
    return 10;
}

template<typename F, typename G>
auto compose(F&& f, G&& g)
{
    return [f = std::forward<F>(f), 
            g = std::forward<G>(g)]()
            {
                return f(g());
            };
}

int main()
{
    auto composition = compose(f, g);

    std::cout << composition() << std::endl;
}