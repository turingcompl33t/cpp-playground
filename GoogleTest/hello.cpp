// hello.cpp
//
// Google Test hello world.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /MTd /I %CPP_WORKSPACE%\_Deps\GoogleTest\googletest\include hello.cpp /link /LIBPATH:%CPP_WORKSPACE%\_Deps\GoogleTest\build\lib gtestd.lib

#include "gtest/gtest.h"

long factorial(long n)
{
    return n <= 1 ? 1 : factorial(n - 1) * n; 
}

TEST(FactorialTest, ComputesCorrectly)
{
    EXPECT_EQ(factorial(0), 1);
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(2), 2);
    EXPECT_EQ(factorial(3), 6);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}