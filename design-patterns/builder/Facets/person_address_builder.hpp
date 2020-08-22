// person_address_builder.hpp

#pragma once

#include <string>

#include "person_builder.hpp"

class PersonAddressBuilder : public PersonBuilder
{
    using Self = PersonAddressBuilder;

public:

    explicit PersonAddressBuilder(Person& person)
        : PersonBuilder{person}
    {}

    Self& at(std::string street_address)
    {
        person.street_address = street_address;
        return *this;
    }

    Self& with_postcode(std::string post_code)
    {
        person.post_code = post_code;
        return *this;
    }

    Self& in(std::string city)
    {
        person.city = city;
        return *this;
    }
};