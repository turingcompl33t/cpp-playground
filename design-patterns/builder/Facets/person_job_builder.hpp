// person_job_builder.hpp

#pragma once

#include <string>

#include "person_builder.hpp"

class PersonJobBuilder : public PersonBuilder
{
    using Self = PersonJobBuilder;

public:

    explicit PersonJobBuilder(Person& person)
        : PersonBuilder{person}
    {}

    Self& at(std::string company_name)
    {
        person.company_name = company_name;
        return *this;
    }

    Self& as_a(std::string position)
    {
        person.position = position;
        return *this;
    }

    Self& earning(int annual_income)
    {
        person.annual_income = annual_income;
        return *this;
    }
};