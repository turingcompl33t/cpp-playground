// singleton.hpp

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>

class Database
{
public:
    virtual int get_population(std::string const& name) = 0;
};

class SingletonDatabase : public Database
{
    std::map<std::string, int> cities;

    // private constructor
    SingletonDatabase()
    {
        auto ifs = std::ifstream{"cities.txt"};

        auto city = std::string{};
        auto pop = std::string{};

        while (std::getline(ifs, city))
        {
            std::getline(ifs, pop);
            int converted = boost::lexical_cast<int>(pop);

            cities[city] = converted;
        }

        ++instance_count;
    }

public:
    static int instance_count;

    // non-copyable
    SingletonDatabase(SingletonDatabase const&)            = delete;
    SingletonDatabase& operator=(SingletonDatabase const&) = delete;

    // static method that returns reference to single instance
    static SingletonDatabase& get()
    {
        static SingletonDatabase db{};
        return db;
    }

    int get_population(std::string const& name) override
    {
        return cities[name];
    }
};

int SingletonDatabase::instance_count = 0;

class DummyDatabase : public Database
{
    std::map<std::string, int> cities;

public:

    DummyDatabase()
    {
        cities["alpha"] = 1;
        cities["beta"]  = 1;
        cities["gamma"] = 1;
    }

    int get_population(std::string const& name) override
    {
        return cities[name];
    }
};

struct SingletonRecordFinder
{
    int total_population(std::vector<std::string> const& names)
    {
        auto result = int{};
        for (auto const& name: names)
        {
            result += SingletonDatabase::get().get_population(name);
        }

        return result;
    }
};

struct ConfigurableRecordFinder
{
    Database& db;

    explicit ConfigurableRecordFinder(Database& db_)
        :db{db_}
    {}

    int total_population(std::vector<std::string> const& names)
    {
        auto result = int{};
        for (auto const& name : names)
        {
            result += db.get_population(name);
        }

        return result;
    }
};