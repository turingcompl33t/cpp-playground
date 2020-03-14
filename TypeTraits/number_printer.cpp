// number_printer.cpp

#include <iostream>
#include <type_traits>

template <typename T>
void NumberPrinterHelper(T t, std::true_type)
{
    std::cout << t << " is integral" << std::endl;
}

template <typename T>
void NumberPrinterHelper(T t, std::false_type)
{
    std::cout << t << " is not integral" << std::endl;
}

template <typename T>
void NumberPrinter(T t)
{
    NumberPrinterHelper(t, typename std::is_integral<T>::type());
}

int main()
{
    NumberPrinter(1729);
    NumberPrinter(3.14);
}