// stdlib_impl.hpp

#include <algorithm>

template <typename Comparer>
struct equals
{
    template <typename Iter1, typename Iter2>
    bool operator()(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) const
    {
        return std::equal(begin1, end1, begin2, end2, Comparer());
    }
};

template <typename Comparer>
struct contains
{
    template <typename Iter1, typename Iter2>
    bool operator()(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) const
    {
        return std::distance(begin2, end2) == 0
            || std::search(begin1, end1, begin2, end2, Comparer()) != end1;
    }
};

template <typename Comparer>
struct starts_with
{
    template <typename Iter1, typename Iter2>
    bool operator()(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) const
    {
        const auto first_nonequal = std::mismatch(begin1, end1, begin2, end2, Comparer());
        return first_nonequal.second == end2;
    }
};

template <typename Comparer>
struct ends_with
{
    template <typename Iter1, typename Iter2>
    bool operator()(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) const
    {
        const auto dist1 = std::distance(begin1, end1);
        const auto dist2 = std::distance(begin2, end2);

        if (dist2 > dist1)
            return false;

        const auto suffix_begin = std::next(begin1, dist1 - dist2);
        return std::equal(suffix_begin, end1, begin2, end2, Comparer());
    }
};