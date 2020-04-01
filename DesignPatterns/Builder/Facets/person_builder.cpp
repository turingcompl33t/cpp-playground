// person_builder.cpp

#include "person_builder.hpp"
#include "person_address_builder.hpp"
#include "person_job_builder.hpp"

PersonAddressBuilder PersonBuilder::lives()
{
    return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilder::works()
{
    return PersonJobBuilder{person};
}