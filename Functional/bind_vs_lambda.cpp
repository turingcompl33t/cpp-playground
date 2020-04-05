// bind_vs_lambda.cpp
// Quick comparison of using std::bind versus lambdas.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 bind_vs_lambda.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

long multiply(long a, long b)
{
    return a*b;
}

TEST_CASE("std::bind and lambdas can both bind fully-applied free functions")
{
    SECTION("std::bind")
    {
        auto fn = std::bind(multiply, 2, 10);
        REQUIRE(fn() == 20);
    }

    SECTION("lambda")
    {
        auto fn = [](){ return multiply(2, 10); };
        REQUIRE(fn() == 20);
    }
}

TEST_CASE("std::bind and lambdas can both bind partially-applied functions")
{
    SECTION("std::bind")
    {
        auto fn = std::bind(multiply, 2, std::placeholders::_1);
        REQUIRE(fn(10) == 20);
    }

    SECTION("lambda")
    {
        auto fn = [](long b){ return multiply(2, b); };
        REQUIRE(fn(10) == 20);
    }
}

template <typename Callable>
void do_work_and_callback(Callable fn)
{
    // do some heavy work here
    fn();
}

struct AsyncWorkerWithBind
{   
    bool m_completed{false};

    void start_work()
    {
        auto cb = std::bind(&AsyncWorkerWithBind::on_done, this);
        do_work_and_callback(cb);
    }

    void on_done() { m_completed = true; }
    bool done() const noexcept { return m_completed; }
};

struct AsyncWorkerWithLambda
{
    bool m_completed{false};

    void start_work()
    {
        auto cb = [this](){ on_done(); };
        do_work_and_callback(cb);
    }

    void on_done() { m_completed = true; }
    bool done() const noexcept { return m_completed; }
};

TEST_CASE("std::bind and lambdas can both be used to bind member functions")
{
    SECTION("std::bind")
    {
        auto worker = AsyncWorkerWithBind{};
        worker.start_work();
        REQUIRE(worker.done());
    }

    SECTION("lambda")
    {
        auto worker = AsyncWorkerWithLambda{};
        worker.start_work();
        REQUIRE(worker.done());
    }
}