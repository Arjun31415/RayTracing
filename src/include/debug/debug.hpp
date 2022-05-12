#pragma once
#include <cstring>
#include <iostream>
#include <sstream>

inline namespace Debug
{
template <class T1, class T2>

std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p);

template <typename C,
          typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
          typename std::enable_if<!std::is_same<C, std::string>::value>::type
              * = nullptr>
std::ostream &operator<<(std::ostream &os, const C &container);
#define debugging
#ifdef debugging
#define debug(...)                                                             \
    std::cerr << "\e[91m" << __func__ << ":" << __LINE__ << "\t";              \
    __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1> void __f(const char *name, Arg1 &&arg1)
{
    std::cerr << name << " : " << arg1 << "\e[39m" << '\n';
}
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&...args)
{
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " : " << arg1 << " | ";
    __f(comma + 1, args...);
}
#else
#define debug(...) ;
#endif
} // namespace Debug
