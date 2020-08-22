// PrettyPrinter.cpp
// Print the contents of any STL container.
//
// Adapted from Stephan T. Lavavej's implementation 
// from the  Channel 9 series "Advanced STL"
// 
// cl /EHsc /nologo /W4 PrettyPrinter.cpp

#include <stddef.h>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

template <typename T> struct is_container_helper {
    template <typename U> static  true_type f(typename U::const_iterator *);
    template <typename U> static false_type f(...);

    typedef decltype(f<T>(0)) type;
};

template <typename T> struct is_container
    : public is_container_helper<T>::type { };

template <typename T, size_t N> struct is_container<T[N]>
    : public true_type { };

template <typename Ch, typename Tr, typename Al>
    struct is_container<basic_string<Ch, Tr, Al>>
    : public false_type { };

struct default_formatter {
    template <typename T> void    prefix(ostream& os, const T&) const { os << "["; }
    template <typename T> void separator(ostream& os, const T&) const { os << ", "; }
    template <typename T> void    suffix(ostream& os, const T&) const { os << "]"; }

    template <typename A, typename B>
        void    prefix(ostream& os, const pair<A, B>&) const { os << "("; }
    template <typename A, typename B>
        void separator(ostream& os, const pair<A, B>&) const { os << ", "; }
    template <typename A, typename B>
        void    suffix(ostream& os, const pair<A, B>&) const { os << ")"; }

    template <typename... Types>
        void    prefix(ostream& os, const tuple<Types...>&) const { os << "("; }
    template <typename... Types>
        void separator(ostream& os, const tuple<Types...>&) const { os << ", "; }
    template <typename... Types>
        void    suffix(ostream& os, const tuple<Types...>&) const { os << ")"; }

    template <typename K, typename C, typename A>
        void    prefix(ostream& os, const set<K, C, A>&) const { os << "{"; }
    template <typename K, typename C, typename A>
        void separator(ostream& os, const set<K, C, A>&) const { os << ", "; }
    template <typename K, typename C, typename A>
        void    suffix(ostream& os, const set<K, C, A>&) const { os << "}"; }

    template <typename T> void element(ostream& os, const T& t) const {
        os << t;
    }

    template <typename Ch, typename Tr, typename Al>
        void element(ostream& os, const basic_string<Ch, Tr, Al>& s) const {

        os << "\"" << s << "\"";
    }
};


template <typename T> void print(ostream& os, const T& t);

template <typename T, typename Fmt>
    void print(ostream& os, const T& t, const Fmt& fmt);
template <typename A, typename B, typename Fmt>
    void print(ostream& os, const pair<A, B>& p, const Fmt& fmt);
template <typename... Types, typename Fmt>
    void print(ostream& os, const tuple<Types...>& t, const Fmt& fmt);

template <typename Tuple, typename Fmt, size_t I>
    void print_tuple_helper(ostream& os, const Tuple& t, const Fmt& fmt,
        integral_constant<size_t, I>);
template <typename Tuple, typename Fmt>
    void print_tuple_helper(ostream& os, const Tuple& t, const Fmt& fmt,
        integral_constant<size_t, 1>);
template <typename Tuple, typename Fmt>
    void print_tuple_helper(ostream& os, const Tuple& t, const Fmt& fmt,
        integral_constant<size_t, 0>);

template <typename C, typename Fmt>
    void print_container_helper(ostream& os, const C& c, true_type, const Fmt& fmt);
template <typename T, typename Fmt>
    void print_container_helper(ostream& os, const T& t, false_type, const Fmt& fmt);

template <typename T> void print(ostream& os, const T& t) {
    print(os, t, default_formatter());
}

template <typename T, typename Fmt>
    void print(ostream& os, const T& t, const Fmt& fmt) {

    print_container_helper(os, t, typename is_container<T>::type(), fmt);
}

template <typename A, typename B, typename Fmt>
    void print(ostream& os, const pair<A, B>& p, const Fmt& fmt) {

    fmt.prefix(os, p);
    print(os, p.first, fmt);
    fmt.separator(os, p);
    print(os, p.second, fmt);
    fmt.suffix(os, p);
}

template <typename... Types, typename Fmt>
    void print(ostream& os, const tuple<Types...>& t, const Fmt& fmt) {

    const size_t N = tuple_size<tuple<Types...>>::value;
    fmt.prefix(os, t);
    print_tuple_helper(os, t, fmt, integral_constant<size_t, N>());
    fmt.suffix(os, t);
}


template <typename Tuple, typename Fmt, size_t I>
    void print_tuple_helper(ostream& os, const Tuple& t, const Fmt& fmt,
        integral_constant<size_t, I>) {

    const size_t N = tuple_size<Tuple>::value;
    print(os, get<N - I>(t), fmt);
    fmt.separator(os, t);
    print_tuple_helper(os, t, fmt, integral_constant<size_t, I - 1>());
}

template <typename Tuple, typename Fmt>
    void print_tuple_helper(ostream& os, const Tuple& t, const Fmt& fmt,
        integral_constant<size_t, 1>) {

    const size_t N = tuple_size<Tuple>::value;
    print(os, get<N - 1>(t), fmt);
}

template <typename Tuple, typename Fmt>
    void print_tuple_helper(ostream&, const Tuple&, const Fmt&,
        integral_constant<size_t, 0>) { }

template <typename C, typename Fmt>
    void print_container_helper(ostream& os, const C& c, true_type, const Fmt& fmt) {

    fmt.prefix(os, c);

    auto i = begin(c);
    auto e = end(c);

    if (i != e) {
        for (;;) {
            print(os, *i, fmt);

            if (++i != e) {
                fmt.separator(os, c);
            } else {
                break;
            }
        }
    }

    fmt.suffix(os, c);
}

template <typename T, typename Fmt>
    void print_container_helper(ostream& os, const T& t, false_type, const Fmt& fmt) {

    fmt.element(os, t);
}

template <typename T> void print_line(ostream& os, const T& t) {
    print(os, t);
    os << endl;
}

template <typename T, typename Fmt>
    void print_line(ostream& os, const T& t, const Fmt& fmt) {

    print(os, t, fmt);
    os << endl;
}

struct special_formatter {
    template <typename T> void    prefix(ostream& os, const T& t) const {
        default_formatter().prefix(os, t);
    }
    template <typename T> void separator(ostream& os, const T& t) const {
        default_formatter().separator(os, t);
    }
    template <typename T> void    suffix(ostream& os, const T& t) const {
        default_formatter().suffix(os, t);
    }
    template <typename T> void   element(ostream& os, const T& t) const {
        default_formatter().element(os, t);
    }

    template <typename K, typename C, typename A>
        void prefix(ostream& os, const set<K, C, A>& s) const {

        os << "[" << s.size() << "]{";
    }

    template <typename T, typename A>
        void    prefix(ostream& os, const forward_list<T, A>&) const { os << "<"; }
    template <typename T, typename A>
        void separator(ostream& os, const forward_list<T, A>&) const { os << "->"; }
    template <typename T, typename A>
        void    suffix(ostream& os, const forward_list<T, A>&) const { os << ">"; }

    template <typename Ch, typename Tr, typename Al>
        void element(ostream& os, const basic_string<Ch, Tr, Al>& s) const {

        os << s;
    }
};


int main() {
    cout << "Empty vector: ";
    print_line(cout, vector<int>());

    cout << "Empty    set: ";
    print_line(cout, set<int>());

    cout << "Empty  tuple: ";
    print_line(cout, tuple<>());

    cout << "One-element vector: ";
    print_line(cout, vector<int>(1, 1701));

    {
        cout << "One-element    set: ";
        set<int> s;
        s.insert(1729);
        print_line(cout, s);
    }

    {
        cout << "One-element  array: ";
        const int a[] = { 2048 };
        print_line(cout, a);
    }

    cout << "One-element  tuple: ";
    print_line(cout, tuple<int>(4096));

    {
        cout << "Multi-element vector: ";
        vector<int> v;
        v.push_back(11);
        v.push_back(22);
        v.push_back(33);
        print_line(cout, v);
    }

    {
        cout << "Multi-element    set: ";
        set<int> s;
        s.insert(111);
        s.insert(777);
        s.insert(222);
        s.insert(999);
        print_line(cout, s);
    }

    {
        cout << "Multi-element  array: ";
        const int a[] = { 100, 200, 300, 400, 500 };
        print_line(cout, a);
    }

    cout << "  Two-element   pair: ";
    print_line(cout, make_pair(123, 456));

    cout << "Multi-element  tuple: ";
    print_line(cout, make_tuple(10, 20, 30, 40));

    cout << "          Empty string: ";
    print_line(cout, string(""));

    cout << "  One-character string: ";
    print_line(cout, string("x"));

    cout << "Multi-character string: ";
    print_line(cout, string("meow"));

    cout << "--" << endl;

    {
        cout << "vector<string>: ";
        vector<string> v;
        v.push_back("cute");
        v.push_back("fluffy");
        v.push_back("kittens");
        print_line(cout, v);
    }

    {
        cout << "vector<vector<int>>: ";
        vector<vector<int>> v;
        for (int i = 0; i < 3; ++i) {
            vector<int> temp;

            for (int j = 0; j < 4; ++j) {
                temp.push_back((i + 1) * 10 + j);
            }

            v.push_back(temp);
        }
        print_line(cout, v);

        cout << "map<string, vector<int>>: ";
        map<string, vector<int>> m;
        m["abc"] = v[0];
        m["def"] = v[1];
        m["ghi"] = v[2];
        print_line(cout, m);
    }

    {
        cout << "Multi-dimensional array: ";
        const int aa[3][5] = {
            { 71, 72, 73, 74, 75 },
            { 81, 82, 83, 84, 85 },
            { 91, 92, 93, 94, 95 }
        };
        print_line(cout, aa);
    }

    {
        cout << "vector<tuple<int, string, int>>: ";
        vector<tuple<int, string, int>> v;
        v.push_back(make_tuple(1, "ten", 100));
        v.push_back(make_tuple(2, "twenty", 200));
        v.push_back(make_tuple(3, "thirty", 300));
        print_line(cout, v);
    }

    cout << endl << "*** special_formatter: ***" << endl;

    {
        vector<set<string>> v(3);
        v[0].insert("the");
        v[0].insert("wrath");
        v[0].insert("of");
        v[0].insert("khan");
        v[1].insert("the");
        v[1].insert("voyage");
        v[1].insert("home");
        v[2].insert("the");
        v[2].insert("undiscovered");
        v[2].insert("country");
        print_line(cout, v, special_formatter());
    }

    {
        set<pair<int, int>> s;
        s.insert(make_pair(11, 22));
        s.insert(make_pair(33, 44));
        s.insert(make_pair(55, 66));
        print_line(cout, s, special_formatter());
    }

    {
        forward_list<int> fl;
        fl.push_front(123);
        fl.push_front(456);
        fl.push_front(789);
        print_line(cout, fl, special_formatter());
    }
}
