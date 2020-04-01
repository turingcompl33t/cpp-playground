// builder.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 builder.cpp

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

struct HtmlElement
{
    std::string              name;
    std::string              text;
    std::vector<HtmlElement> elements;

    std::size_t const indent_size = 2;

    HtmlElement(){}
    HtmlElement(std::string const& name_, std::string const& text_)
        : name{name_}, text{text_}
    {}

    std::string str(int indent = 0) const
    {
        auto oss = std::ostringstream{};
        auto i = std::string(indent_size*indent, ' ');

        oss << i << "<" << name << ">" << std::endl;

        if (text.size() > 0)
        {
            oss << std::string(indent_size*(indent+1), ' ') << text << std::endl;
        }

        for (auto const& e : elements)
        {
            oss << e.str(indent + 1);
        }

        oss << i << "</" << name << ">" << std::endl;

        return oss.str();
    }
};

struct HtmlBuilder
{
    HtmlElement root;

    HtmlBuilder(std::string root_name)
    {
        root.name = root_name;
    }

    void add_child(std::string name, std::string text)
    {
        auto e = HtmlElement{name, text};
        root.elements.emplace_back(e);
    }

    std::string str() const
    {
        return root.str();
    }
};

int main()
{
    auto builder = HtmlBuilder{"ul"};
    builder.add_child("li", "hello");
    builder.add_child("li", "world");

    std::cout << builder.str();
}