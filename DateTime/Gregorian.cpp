// Gregorian.cpp
// Demo of boost::gregorian calendar utility.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Boost /I c:\Dev\Catch Gregorian.cpp /link /LIBPATH:C:\Dev\Boost\stage\lib

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>

TEST_CASE("boost::gregorian::date supports basic calendar functions")
{
    boost::gregorian::date d{1986, 9, 15};

    REQUIRE(d.year() == 1986);
    REQUIRE(d.month() == 9);
    REQUIRE(d.day() == 15);
    REQUIRE(d.day_of_year() == 258);
    REQUIRE(d.day_of_week() == boost::date_time::Monday);
}

TEST_CASE("boost::gregorian::date supports construction from string")
{
    auto d = boost::gregorian::from_string("1986/9/15");

    REQUIRE(d.year() == 1986);
    REQUIRE(d.month() == 9);
    REQUIRE(d.day() == 15);
    REQUIRE(d.day_of_year() == 258);
    REQUIRE(d.day_of_week() == boost::date_time::Monday);
}

TEST_CASE("Invalid boost::gregorian::date dates throw exceptions")
{
    using boost::gregorian::date;
    using boost::gregorian::bad_day_of_month;

    REQUIRE_THROWS_AS(date(1986, 9, 32), bad_day_of_month);
}

TEST_CASE("Default constructed boost::gregorian::date is not a date")
{
    boost::gregorian::date d{};

    REQUIRE(d.is_not_a_date());
}

TEST_CASE("boost::gregorian::date supports calendar arithmetic")
{
    boost::gregorian::date d1{1986, 9, 15};
    boost::gregorian::date d2{2019, 8, 1};

    auto duration = d2 - d1;
    REQUIRE(duration.days() == 12008);
}

TEST_CASE("date and date_duration support addition")
{
    boost::gregorian::date d1{1986, 9, 15};
    boost::gregorian::date_duration duration{12008};

    auto d2 = d1 + duration;
    REQUIRE(d2 == boost::gregorian::from_string("2019/8/1"));
}

TEST_CASE("boost::gregorian::date supports date periods")
{
    boost::gregorian::date d1{1986, 9, 15};
    boost::gregorian::date d2{2019, 8, 1};

    boost::gregorian::date_period period{d1, d2};

    boost::gregorian::date contained{1987, 1, 1};
    boost::gregorian::date not_contained{2019, 9, 1};

    REQUIRE(period.contains(contained));
    REQUIRE_FALSE(period.contains(not_contained));
}