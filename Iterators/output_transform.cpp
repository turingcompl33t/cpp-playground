// output_transform.hpp
// A "smart" iterator.

#include <cstdlib>
#include <iterator>

template <typename Iterator, typename Transform>
class output_transform_iterator
{
    Iterator  m_iterator;
    Transform m_transform;

public:
    using iterator_category = std::output_iterator_tag;

    explicit output_transform_iterator(
        Iterator iterator,
        Transform transform) 
        : m_iterator{ iterator }
        , m_transform{ transform }
    {}

    output_transform_iterator& operator++()
    {
        ++m_iterator;
        return *this;
    }

    output_transform_iterator& operator++(int)
    {
        ++*this;
        return *this;
    }

    output_transform_iterator& operator*()
    {
        return *this;
    }

    template <typename T>
    output_transform_iterator& operator=(T const& value)
    {
        *m_iterator = m_transform(value);
        return *this;
    }
};

template <typename Transform>
class output_transformer
{
    Transform m_transform;

public:
    explicit output_transformer(Transform transform)
        : m_transform{ transform }
    {}

    template <typename Iterator>
    output_transform_iterator<Iterator, Transform>
    operator()(Iterator iterator) const
    {
        return output_transform_iterator<Iterator, Transform>(iterator, m_transform);
    }
};

template <typename Transform>
output_transformer<Transform>
make_output_transformer(Transform transform)
{
    return output_transformer<Transform>(transform);
}

int main()
{
    return EXIT_SUCCESS;
}