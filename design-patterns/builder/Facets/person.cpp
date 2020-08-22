// person.cpp

#include <string>

#include "person.hpp"
#include "person_builder.hpp"

PersonBuilder Person::create()
{
    return PersonBuilder{};
}
