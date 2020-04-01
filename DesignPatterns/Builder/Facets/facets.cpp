// facets.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 facets.cpp

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "person.hpp"
#include "person_builder.hpp"
#include "person_address_builder.hpp"
#include "person_job_builder.hpp"

int main()
{
    Person p = Person::create()
        .lives().at("123 London Road").with_postcode("12345").in("Amherst")
        .works().at("Google").as_a("Software Developer").earning(100000);

    std::cout << p;
}