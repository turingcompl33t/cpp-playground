// sort.cpp
// Compile-time integer array sort via TMP.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I %CPP_WORKSPACE%\_Deps\Catch2 sort.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <typeinfo>

// Ints primary template
template <int... Vals> struct Ints {};

// Concat primary template
template <typename Ints1, typename Ints2> struct Concat;

// Concat partial specialization
template <int... Vals1, int... Vals2>
struct Concat<Ints<Vals1...>, Ints<Vals2...>>
{
    typedef Ints<Vals1..., Vals2...> type;
};

// BisectHelper primary template
template <typename Ints1, typename Ints2, bool Done> struct BisectHelper;

// BisectHelper partial specialization
// base case
template <int... Vals1, int... Vals2>
struct BisectHelper<Ints<Vals1...>, Ints<Vals2...>, true>
{
    typedef Ints<Vals1...> first;
    typedef Ints<Vals2...> second;
};

// BisectHelper partial specialization
// recursive case 
template<int... Vals1, int X, int... Vals2>
struct BisectHelper<Ints<Vals1...>, Ints<X, Vals2...>, false>
    : public BisectHelper<Ints<Vals1..., X>, Ints<Vals2...>, (sizeof...(Vals1) + 1 >= sizeof...(Vals2))> {};

// Bisect primary template
template <typename Ints1> struct Bisect;

// Bisect partial specialization
template <int... Vals>
struct Bisect<Ints<Vals...>>
    : public BisectHelper<Ints<>, Ints<Vals...>, sizeof...(Vals) == 0> {};

// Merge primary template
template <typename Ints1, typename Ints2> struct Merge;

// Merge partial specialization
// base case
template <> struct Merge<Ints<>, Ints<>>
{
    typedef Ints<> type;
};

// Merge partial specialization
// recursive case - left empty
template <int A, int... Vals1>
struct Merge<Ints<>, Ints<A, Vals1...>>
{
    typedef Ints<A, Vals1...> type;
};

// Merge partial specialization
// recursive case - right empty 
template <int B, int... Vals2>
struct Merge<Ints<B, Vals2...>, Ints<>>
{
    typedef Ints<B, Vals2...> type;
};

// MergeHelper primary template
template <bool TakeB, typename Ints1, typename Ints2> struct MergeHelper;

// Merge partial specialization
// recursive case - left and right nonempty
template <int A, int... Vals1, int B, int... Vals2>
struct Merge<Ints<A, Vals1...>, Ints<B, Vals2...>>
    : public MergeHelper<(B < A), Ints<A, Vals1...>, Ints<B, Vals2...>> { };

// MergeHelper partial specialization
// TakeB = false
template <int A, int... Vals1, int B, int... Vals2>
struct MergeHelper<false, Ints<A, Vals1...>, Ints<B, Vals2...>>
    : public Concat<
        Ints<A>,
        typename Merge<Ints<Vals1...>, Ints<B, Vals2...>>::type
    > { };

// MergeHelper partial specialization
// TakeB = true
template <int A, int... Vals1, int B, int... Vals2>
struct MergeHelper<true, Ints<A, Vals1...>, Ints<B, Vals2...>>
    : public Concat<
        Ints<B>,
        typename Merge<Ints<A, Vals1...>, Ints<Vals2...>>::type
    > { };

// SortHelper primary template
template <typename Ints1> struct SortHelper;

// SortHelper partial specialization
template <> struct SortHelper<Ints<>>
{
    typedef Ints<> type;
};

// SortHelper partial specialization
template <int A> struct SortHelper<Ints<A>>
{
    typedef Ints<A> type;
};

// SortHelper partial specialization
template <int A, int B, int... Vals>
struct SortHelper<Ints<A, B, Vals...>>
{
private:
    typedef Bisect<Ints<A, B, Vals...>> bisect;

    typedef typename bisect::first unsorted_first;
    typedef typename bisect::second unsorted_second;

    typedef typename SortHelper<unsorted_first>::type sorted_first;
    typedef typename SortHelper<unsorted_second>::type sorted_second;

public:
    typedef typename Merge<sorted_first, sorted_second>::type type;
};

// Sort primary template
template <int... Vals> struct Sort
    : public SortHelper<Ints<Vals...>> {};

TEST_CASE("array is sorted at compile time")
{   
    // NOTE: this is a crappy way to test correctness
    auto s = std::string{typeid(Sort<4, 3, 2, 1, 0>::type).name()};
    auto e = std::string{"struct Ints<0,1,2,3,4>"};  // expected
    
    REQUIRE(s == e);
}