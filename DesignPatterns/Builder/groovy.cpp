// groovy.cpp
//
// Simple demonstration of the groovy-style builder design pattern. 
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 groovy.cpp

#include <tuple>
#include <string>
#include <vector>
#include <iostream>

struct Tag
{
    using children_t   = std::vector<Tag>;
    using attributes_t = std::vector<std::pair<std::string, std::string>>;

    std::string  name;
    std::string  text;
    children_t   children;
    attributes_t attributes;

    friend std::ostream& operator<<(std::ostream& os, Tag const& tag)
    {
        os << "<" << tag.name;

        for (auto const& att : tag.attributes)
        {
            os << " " << att.first << "=\"" << att.second << "\"";
        }

        if (tag.children.size() == 0 && tag.text.length() == 0)
        {
            os << "/>" << std::endl;
        }
        else
        {
            os << ">" << std::endl;

            if (tag.text.length() > 0)
            {
                os << tag.text << std::endl;
            }

            for (auto const& child : tag.children)
            {
                os << child;
            }

            os << "</" << tag.name << ">" << std::endl;
        }

        return os;
    }

protected:

    Tag(std::string const& name_, std::string const& text_)
        : name{name_}, text{text_}
    {}

    Tag(std::string const& name_, children_t const& children_)
        : name{name_}, children{children_}
    {}
};

struct P : Tag
{
    explicit P(std::string const& text)
        : Tag{"p", text}
    {}

    // NOTE: pretty cool that we can feed init list directly to vector ctor
    P(std::initializer_list<Tag> children)
        : Tag{"p", children}
    {}
};

struct Img : Tag
{
    explicit Img(std::string const& url)
        : Tag{"img", ""}
    {
        attributes.emplace_back(std::make_pair("src", url));
    }
};

int main()
{
    auto tag = 
    P {
        P { "Hello World!" },
        Img { "https://example.com/img.png" }
    };

    std::cout << tag;
}