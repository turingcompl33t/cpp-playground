// test.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 /I %CPP_WORKSPACE%\_Deps\Boost test.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "singleton.hpp"

TEST_CASE("SingletonDatabase is a singleton")
{
    auto& db1 = SingletonDatabase::get();
    auto& db2 = SingletonDatabase::get(); 

    REQUIRE(db1.instance_count == 1);
    REQUIRE(db2.instance_count == 1);
}

TEST_CASE("SingletonRecordFinder allows us to find records in SingletonDatabase")
{
    auto finder = SingletonRecordFinder{};

    auto names = std::vector<std::string>{"Shanghai", "Beijing"};

    int total = finder.total_population(names);

    REQUIRE(total == 26317104+20035455); 
}

TEST_CASE("ConfigurableRecordFinder works as expected when tested against dummy database")
{
    auto db = DummyDatabase{};
    auto finder = ConfigurableRecordFinder{db};

    auto names = std::vector<std::string>{"alpha", "beta"};

    auto total = finder.total_population(names);

    REQUIRE(total == 2);
}