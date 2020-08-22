// person.hpp

#pragma once

#include <string>
#include <ostream>

class PersonBuilder;

class Person
{
    // address
    std::string street_address;
    std::string post_code;
    std::string city;

    // employment
    std::string company_name;
    std::string position;
    int annual_income{0};
    
    Person() {}

public:
    static PersonBuilder create();

    Person(Person&& other) = default;
    Person& operator=(Person&& rhs) = default;

    friend std::ostream& operator<<(std::ostream& stream, Person const& p)
    {
        stream 
            << "Street Address: " << p.street_address << '\n'
            << "Post Code: " << p.post_code << '\n'
            << "City: " << p.city << '\n' 
            << "Company Name: " << p.company_name << '\n'
            << "Position: " << p.position << '\n'
            << "Annual Income: " << p.annual_income << '\n';

        return stream;
    }

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};