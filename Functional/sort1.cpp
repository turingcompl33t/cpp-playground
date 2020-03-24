// sort1.cpp
//
// Using a custom function object to sort a collection.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 sort1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <set>
#include <string>

class Person
{
    std::string m_first;
    std::string m_last;
public:
    Person(std::string const& first, std::string const& last)
        : m_first{first}, m_last{last}
    {}

    std::string firstname() const { return m_first; }
    std::string lastname() const { return m_last; }
};

class PersonSort
{
public:
    bool operator()(Person const& p1, Person const& p2) const
    {
        return p1.lastname() < p2.lastname() ||
            (p1.lastname() == p2.lastname() && 
            p1.firstname() < p2.firstname());
    }
};

TEST_CASE("custom sort criterion in form of function object may be used to sort a std::set")
{   
    // here we can construct the set without constructing the function
    // object or specifying ir directly because it is a distinct type;
    // this is perhaps a benefit over the use of a vanilla free function
    auto c = std::set<Person, PersonSort>{};

    c.insert(Person{"john", "doe"});
    c.insert(Person{"alan", "turing"});
    c.insert(Person{"jane", "doe"});

    REQUIRE(c.size() == 3);
    
    auto i = c.begin();
    REQUIRE((*i++).firstname() == "jane");
    REQUIRE((*i++).firstname() == "john");
    REQUIRE((*i++).firstname() == "alan");
}