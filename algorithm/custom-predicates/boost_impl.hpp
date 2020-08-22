// boost_impl.hpp

#include <boost/algorithm/string.hpp>
#include <boost/range/iterator_range_core.hpp>

template <typename Comparer>
struct equals
{
    template <typename Iter1, typename Iter2>
    bool operator()(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) const
    {
        auto r1 = boost::make_iterator_range(begin1, end1);
        auto r2 = boost::make_iterator_range(begin2, end2);

        return boost::equals(r1, r2, Comparer());
    }
};

template <typename Comparer>
struct contains
{
    template <typename Iter1, typename Iter2>
    bool operator()(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) const
    {
        auto r1 = boost::make_iterator_range(begin1, end1);
        auto r2 = boost::make_iterator_range(begin2, end2);

        return boost::contains(r1, r2, Comparer());
    }
};

template <typename Comparer>
struct starts_with
{
    template <typename Iter1, typename Iter2>
    bool operator()(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) const
    {
        auto r1 = boost::make_iterator_range(begin1, end1);
        auto r2 = boost::make_iterator_range(begin2, end2);

        return boost::starts_with(r1, r2, Comparer());
    }
};

template <typename Comparer>
struct ends_with
{
    template <typename Iter1, typename Iter2>
    bool operator()(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2) const
    {
        auto r1 = boost::make_iterator_range(begin1, end1);
        auto r2 = boost::make_iterator_range(begin2, end2);

        return boost::ends_with(r1, r2, Comparer());
    }
};