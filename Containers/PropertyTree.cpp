// PropertyTree.cpp
// Demo of basic properties and usage of boost::property_tree::ptree.
//
// Build
// cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Boost /I c:\Dev\Catch2 PropertyTree.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

TEST_CASE("boost::property_tree::ptree stores tree data")
{
    using namespace boost::property_tree;
    
    ptree p{};
    p.put("name", "finfisher");
    p.put("year", 2014);
    p.put("features.process", "LSASS");
    p.put("features.driver", "mssoundx.sys");
    p.put("features.arch", 32);

    REQUIRE(p.get_child("year").get_value<int>() == 2014);

    auto const file_name = "rootkits.json";
    write_json(file_name, p);

    ptree copy{};
    read_json(file_name, copy);

    REQUIRE(copy == p);
}