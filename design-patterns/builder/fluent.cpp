// fluent.cpp
//
// Simple demo of the fluent-style builder design pattern.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 fluent.cpp

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

struct HtmlBuilder;

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

    static HtmlBuilder build(std::string root_name);
};

struct HtmlBuilder
{
    HtmlElement root;

    HtmlBuilder(std::string root_name)
    {
        root.name = root_name;
    }

    HtmlBuilder& add_child(std::string name, std::string text)
    {
        auto e = HtmlElement{name, text};
        root.elements.emplace_back(e);

        return *this;
    }

    std::string str() const
    {
        return root.str();
    }

    operator HtmlElement() { return root; }
};

HtmlBuilder HtmlElement::build(std::string root_name)
{
    return HtmlBuilder{root_name};
}

int main()
{
    // construct the builder directly
    auto builder = HtmlBuilder{"ul"};
    builder.add_child("li", "hello")
        .add_child("li", "world");

    std::cout << "First Method:\n" 
        << builder.str();

    // use static method of the element to obtain builder instance
    auto e = HtmlElement::build("ul")
        .add_child("li", "hello")
        .add_child("li", "world");

    std::cout << "Second Method:\n"
        << e.str();
}