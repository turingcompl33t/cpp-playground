// Monitor.cpp
// Generic monitor class.

#include <mutex>
#include <thread>
#include <vector>
#include <future>
#include <string>
#include <iostream>

template <typename T>
class Monitor
{
private:
    T t;
    std::mutex m;
public:
    Monitor(T t_ = T{})
        : t{t_} {}

    template<typename F>
    auto operator()(F f) -> decltype(f(t))
    {
        std::lock_guard<std::mutex> _{m};
        return f(t);
    }
};

int main()
{
    Monitor<std::ostream&> sync_cout{std::cout};

    sync_cout([](std::ostream& cout) {
        cout << "START HERE" << '\n';
    });

    std::vector<std::future<void>> v;

    for (int i = 0; i < 5; ++i)
    {
        v.push_back(std::async(std::launch::async, [&,i]() {
            
            sync_cout([=](std::ostream& cout) {
                cout << "Hello #1 from thread: " << std::to_string(i) << '\n';
            });

            sync_cout([=](std::ostream& cout) {
                cout << "Hello #2 from thread: " << std::to_string(i) << '\n';
            });
        }));
    }

    // join all the threads
    for (auto& f : v)
    {
        f.wait();
    }

    sync_cout([](std::ostream& cout) {
        cout << "ALL DONE" << std::endl;
    });
}