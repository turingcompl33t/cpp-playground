// MsPPL.cpp 
// Demonstration of MS Parallel Patterns Library to perform
// parallel computation of fibonacci sequence
//
// NOTE: my apologies to Sean Parent
//
// compile with: /EHsc

#include <windows.h>
#include <ppl.h>
#include <concurrent_vector.h>

#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace concurrency;
using namespace std;

template <class Function>
__int64 time_call(Function&& f)
{
    __int64 begin = GetTickCount();
    f();
    return GetTickCount() - begin;
}

    // super naive fibonacci implementation
int fibonacci(int n)
{
    if (n < 2)
    {
        return n;
    }

    return fibonacci(n-1) + fibonacci(n-2);
}

int wmain()
{
    __int64 elapsed;

    // an array of Fibonacci numbers to compute
    array<int, 4> a = { 24, 26, 41, 42 };

    // the results of the serial computation
    vector<tuple<int,int>> results1;

    // the results of the parallel computation.
    concurrent_vector<tuple<int,int>> results2;

    // use the for_each algorithm to compute the results serially
    elapsed = time_call([&] 
    {
        for_each (begin(a), end(a), [&](int n) {
            results1.push_back(make_tuple(n, fibonacci(n)));
        });
    });   
    wcout << L"serial time: " << elapsed << L" ms" << endl;
   
    // use the parallel_for_each algorithm to perform the same task
    elapsed = time_call([&] 
    {
        parallel_for_each (begin(a), end(a), [&](int n) {
            results2.push_back(make_tuple(n, fibonacci(n)));
        });

        // sort the concurrent_vector object
        // so that the results match the serial version
        sort(begin(results2), end(results2));
    });   
    wcout << L"parallel time: " << elapsed << L" ms" << endl << endl;

    // print the results
    for_each (begin(results2), end(results2), [](tuple<int,int>& pair) {
        wcout << L"fib(" << get<0>(pair) << L"): " << get<1>(pair) << endl;
    });
}