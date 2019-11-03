## Timing in C++

What tools do we have at our disposal in C++ to profile our code?

### Measuring Execution Time

The support for measuring execution time in the C++ standard library is far more robust than that provided by the C standard library. The `<chrono>` header from the standard library includes a number of useful and easy to use functions for timing the execution of programs or portions thereof. 

A useful `Timer` class that can simply be dropped in to measure the execution time of a function (or the execution time spent in some arbitrary scope). The constructor and destructor take care of management of the timer. 

```C++
class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
public:
    Timer() 
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> duration = end - start;
        float ms = duration.count() * 1000.0f;

        std::cout << "elapsed time: " << ms << std::endl;
    }
};
```