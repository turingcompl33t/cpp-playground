// test.cpp

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <random>
#include <thread>
#include <cstdlib>

#include "tatas_ex.hpp"

// the number of resources that will be acquired atomically in each request
constexpr static auto const RESOURCES_PER_REQUEST = 4ul;

// the total number of requests processed by each thread
constexpr static auto const N_REQUESTS = 100ul;

// the number of threads utilized in the test
constexpr static auto const N_THREADS = 2ul;

static bitset_t generate_request(
    std::mt19937&                                      gen, 
    std::uniform_int_distribution<unsigned long long>& dist)
{
    bitset_t request{};
    for (auto i = 0ul; i < RESOURCES_PER_REQUEST; ++i)
    {
        request |= static_cast<bitset_t>((1 << dist(gen)));
    }

    return request;
}

static void generate_requests(std::vector<bitset_t>& requests)
{
    std::mt19937 gen{1};
    std::uniform_int_distribution<unsigned long long> 
        dist{0, (sizeof(bitset_t)*8) - 1};

    for (auto i = 0ul; i < N_REQUESTS; ++i)
    {
        requests.emplace_back(generate_request(gen, dist));
    }
}

static void initialize_resources(std::vector<std::size_t>& resources)
{
    for (auto i = 0ul; i < sizeof(bitset_t)*8; ++i)
    {
        resources.push_back(0);
    }
}

static std::vector<std::size_t*> get_resources_for_request(
    bitset_t const&           request, 
    std::vector<std::size_t>& resources)
{
    std::vector<std::size_t*> subset{};
    for (auto i = 0ul; i < sizeof(bitset_t)*8; ++i)
    {
        auto const is_set = (request >> i) & 1;
        if (is_set)
        {
            subset.push_back(&resources[i]);
        }
    }

    return subset;
}

static bool validate_request(
    bitset_t const&           request, 
    std::vector<std::size_t>& resources)
{   
    auto const subset = get_resources_for_request(request, resources);
    if (subset.size() == 0)
    {
        return true;
    }

    auto const& value = *subset.front();
    return std::all_of(
        std::begin(subset), 
        std::end(subset), 
        [value](std::size_t* r){ return (*r == value); });
}

static void worker(
    tatas_ex_lock&           lock, 
    std::vector<bitset_t>&   requests,
    std::vector<std::size_t> resources)
{
    for (auto const& req : requests)
    {
        lock.lock(req);

        for (auto* res : get_resources_for_request(req, resources))
        {
            ++(*res);
        }

        lock.unlock(req);
    }
}

TEST_CASE("extended tatas lock")
{
    // initialize the resources container
    std::vector<std::size_t> resources{};
    initialize_resources(resources);

    // generate resources requests
    std::vector<bitset_t> requests{};
    generate_requests(requests);
    
    tatas_ex_lock lock{};

    // launch workers that will each process every request
    std::vector<std::thread> threads{};
    for (auto i = 0ul; i < N_THREADS; ++i)
    {
        threads.emplace_back(
            worker, 
            std::ref(lock), 
            std::ref(requests), 
            std::ref(resources));
    }

    // wait for everyone to finish
    for (auto& t : threads)
    {
        t.join();
    }

    // check for correctness
    for (auto const& r : requests)
    {
        REQUIRE(validate_request(r, resources));
    }

    REQUIRE(true);
}