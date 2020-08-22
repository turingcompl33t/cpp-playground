// VectorVsDeque.cpp
// Quick + dirty test of vector vs deque performance when
// removing the first element of the container.

#include <vector>
#include <deque>
#include <chrono>
#include <memory>
#include <iostream>

template<class T> 
void pop_front(std::deque<T>& v)
{
	v.pop_front();
}

template<class T> 
void pop_front(std::vector<T>& v)
{
	v.erase(v.begin());
}

template<class V> 
void test(V&& v, int N, int M)
{
	for (int i = 0; i < M; ++i)
	{
		v.push_back(std::make_shared<int>());
	}

	auto tp1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < N; ++i)
	{
		auto w = v.front();
		pop_front(v);
		v.push_back(w);
	}

	auto tp2 = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count() << " ms\n";
}

void test_with_params(int N, int M)
{
    std::cout << "N = " << N << ", M = " << M << '\n';
	std::cout << "\tvector: "; test( std::vector<std::shared_ptr<int>>(), N, M );
	std::cout << "\tdeque:  "; test( std::deque<std::shared_ptr<int>>(), N, M );
}

int main()
{
	const int N = 1000000;

    for (int M = 1; M <= 10000; M *= 10)
    {
        test_with_params(N, M);
    }
}